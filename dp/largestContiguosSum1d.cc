#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main () {


	int n;
	vector<int> A;
	scanf("%d", &n);
	A.assign(n, 0);
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d", &A[i]);
	}
	if (n==0) return 0;

	int rs = A[0];
	int ms = rs;
	int tmp = 0;
	int lo = 0;
	int hi = 0;
	int mlo = 0;
	int mhi = 0;

	for (int k = 1 ; k < n ; ++k) {
		tmp = rs + A[k];
		if (tmp < A[k]) {
			rs = A[k] ; lo = k;
		} else { 
			rs = tmp;
		}

		hi = k;

		if (rs > ms){
			mlo  = lo ; mhi = hi ; ms = rs; }
	}

	printf("Maximum contiguous sum : %d\n", ms);
	printf("Maximum contiguous indices %d: %d\n",mlo, mhi);
	return 0;
}
