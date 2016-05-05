#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;
#define MAX 100001


class cmp{
	public:
	cmp(int s):k(s) {}
	size_t k;

	bool operator()(const char * str1, const char * str2) {
		 size_t x = min(strlen(str1),strlen(str2));
		 k = min (k, x);
		return strncmp (str1,  str2, x ) < 0;
	}
};
int tcount(const char * str1, const char * str2) {
	int k = 0;
	while (str1 && str2) {
		if (*str1++ == *str2++) {
            if (*str1 <'a' ||*str1 >'z') {
                break;
            }
			++k;
		} else {
            break;
        }

	}
	return k;
} 

int main()
{
	int t =0;
    scanf("%d",&t);
    t = 1;
	while (t--) {
		int k;
		string S;
		const char *sa[MAX] = {0};
		getline(cin, S);
		scanf("%d", &k);

		for (int i = 0; i < S.size(); ++i) {

			sa[i] = &S[i];
		}
		cmp c(k);
		sort(&sa[0], &sa[S.size()-1], c);

        int ans = 0;
        string result;
		for (int i =0 ; i < S.size() -k +1; ++i) {
			int  t = 0;
			if ((t = tcount(sa[i], sa[i+k-1])) >= k) {
				string tmp(sa[i]);
                if (ans <t) {
                    ans = t;
                    result =tmp.substr(0,t);
                }
			}
		}
        printf("%s\n",result.c_str());
	}

	return 0;

}
