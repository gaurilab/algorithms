#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

typedef vector<int> vi;
/*

*/
void tswap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}
int partition(vi &A, int s, int t) {
	int x  = A[s];
	int i = s + 1;
	int j = t;
	while (i <= j) {
		if (A[i] <= x) { ++i;}
		else if (A[j] > x){ --j;}
		else {	int temp = A[j];
	A[j] = A[i];
	A[i] = temp;}
	
	}
	tswap(A[i-1], A[s]);
	
	return i-1;
}
int randomised_partition(vi &A, int s, int t, int k)
{
	if (s == t ) {
		printf("s:%d, t:%d ,A[%d]:%d\n", s, t, s,A[s]);
		return s;
	}
	int i= s + random() %(t-s +1);
	
	assert(i >= s &&  i <= t);
	tswap(A[i], A[s]);
	printf("s:%d, t:%d ,i:%d ,A[%d]:%d\n", s, t, i, s,A[s]);
	int q = partition(A, s, t);
	printf("s:%d, t:%d ,i:%d ,A[%d]:%d q:%d k:%d\n", s, t, i, s,A[s],q,k);
	if (k == q) return q;
	if (k < q) { return randomised_partition(A,s,q-1,k);}
	return randomised_partition(A,q+1,t,k);

}

int main()
{
	vi A;
	for (int i=1; i<=10; ++i) A.push_back(i); // 1 2 3 4 5 6 7 8 9

	std::random_shuffle ( A.begin(), A.end() );
	
	for(int k = 0 ; k <A.size() ;++k ) {
		for (int i=0; i<A.size(); ++i) {printf("%d ", A[i]);} printf("\n");
		printf("%d - %d\n", k,A[randomised_partition(A, 0, A.size() - 1, k)]);
			std::random_shuffle (A.begin(), A.end());
	}

 	return 0;
}

