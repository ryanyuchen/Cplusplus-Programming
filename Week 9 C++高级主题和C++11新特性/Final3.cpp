#include <iostream>
using namespace std;

int sqr(int n) {
    return n * n;
}
int sum(int base[], int size, int(*pf)(const int)){
	int sumtotal = 0;
	for(int j = 0; j < size; j++){
		sumtotal += pf(base[j]);
	}
	return sumtotal;
}

int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << sum(a, n, sqr) << endl;
    }

	system("pause");
    return 0;
}