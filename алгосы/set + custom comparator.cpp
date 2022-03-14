auto cmp = [](pii a, pii b) { return a.sc < b.sc; };

multiset<pii, decltype(cmp)> we(cmp);