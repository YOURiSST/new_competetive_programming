// todo: remove std::string&& -> std::string cause we don't want to lose neither of
//       hash(str) && hash(std::move(str)) cases!

#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

template <typename Cont>
int Size(const Cont& cont) {
  return static_cast<int>(cont.size());
}

auto PrefFunc(const std::string& str1, const std::string& str2) {
  auto cur_str = str1 + "#" + str2;
  int len = cur_str.size();
  std::vector<int> pref(len, 0);
  for (int i = 1; i < len; i++) {
    int cur = pref[i - 1];
    while (cur_str[i] != cur_str[cur] && cur > 0) {
      cur = pref[cur - 1];
    }
    if (cur_str[i] == cur_str[cur]) {
      pref[i] = cur + 1;
    }
  }
  return pref;
}

class PolyHash {
 private:
  static const size_t kMaxLen = 1000 * 1000 * 5;
  std::string str_;
  int64_t mod_;
  int64_t power_;
  std::shared_ptr<std::vector<int64_t>> power_powers_;
  std::vector<int64_t> hash_;

  void FillPowers() {
    GetPower(0) = 1;
    for (size_t i = 1; i < kMaxLen; ++i) {
      GetPower(i) = (GetPower(i - 1) * power_) % mod_;
    }
  }

  void FillHash() {
    hash_.resize(str_.size() + 1, 0ll);
    for (size_t i = 1; i < str_.size() + 1; ++i) {
      int64_t to_add = (str_[i - 1] - 'a') * GetPower(i - 1) % mod_;
      hash_[i] = (hash_[i - 1] + to_add) % mod_;
    };
  };

 public:
  static bool IsPrime(int64_t to_check) {
    if (to_check % 2 == 0 || to_check % 3 == 0 || to_check % 5 == 0) {
      return false;
    }
    for (int64_t divisor = 7; divisor * divisor <= to_check; ++divisor) {
      if (to_check % divisor == 0) {
        return false;
      }
    }
    return true;
  }
  static int64_t Generate() {
    std::mt19937_64 random_gen(
        std::chrono::steady_clock::now().time_since_epoch().count());
    int64_t mod = 1e9 + random_gen() % 200000;
    while (!IsPrime(mod)) {
      ++mod;
    }
    return mod;
  }

  PolyHash(std::string&& str, int64_t power = 52)
      : str_(std::move(str)),
        mod_(Generate()),
        power_(power),
        power_powers_(new std::vector<int64_t>(kMaxLen, 1)) {
    FillPowers();
    FillHash();
  }

  PolyHash(std::string&& str, int mod, int64_t power = 52)
      : str_(std::move(str)),
        mod_(mod),
        power_(power),
        power_powers_(new std::vector<int64_t>(kMaxLen, 1)) {
    FillPowers();
    FillHash();
  }

  PolyHash(std::string&& str, int mod,
           std::shared_ptr<std::vector<int64_t>> other_powers,
           int64_t power = 54)
      : str_(std::move(str)),
        mod_(mod),
        power_(power),
        power_powers_(other_powers) {
    FillHash();
  }

  int64_t GetPower() const { return power_; }

  std::string& GetStr() { return str_; }

  const std::string& GetStr() const { return str_; }

  std::vector<int64_t>& GetPowers() { return *power_powers_; }

  const std::vector<int64_t>& GetPowers() const { return *power_powers_; }

  size_t Size() const { return str_.size(); }

  int64_t& GetPower(size_t index) { return GetPowers()[index]; }

  const int64_t& GetPower(size_t index) const { return GetPowers()[index]; }

  const int64_t& GetMod() const { return mod_; }

  int64_t GetHash(size_t left, size_t right) const {
    return (hash_[right] - hash_[left] + mod_) % mod_;
  }

  int64_t GetNormalizedHash(size_t left, size_t right) const {
    size_t power = kMaxLen - left - 1;
    int64_t not_normalized = (hash_[right] - hash_[left] + mod_) % mod_;
    return not_normalized * GetPower(power) % mod_;
  }

  std::shared_ptr<std::vector<int64_t>> GetPowersPointer() {
    return power_powers_;
  }
};
