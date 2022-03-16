auto foo = [&] (int x, int y) -> Edge {
	return {a[0] * x * y, 0};
};
	
	
auto foo = [&] (int x, int y) {
	cout << a[0] * x * y;
};