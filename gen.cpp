#pragma GCC optimize ("Ofast")
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i=(a); i<(b); i++)
#define FORD(i, a, b) for (int i=(a); i>(b); i--)
#define PPC(x) __builtin_popcount(x)
#define MSB(x) (63 - __builtin_clzll(x))
#define SZ(x) ((int)(x).size())
#define HASK(S, x) (S.find(x) != S.end())
#define pb push_back
#define ALL(x) (x).begin(), (x).end()
#define ARG(x, i) (get<i>(x))
#define ithBit(m, i) ((m) >> (i) & 1)
#define ft first
#define sd second
#define kw(a) ((a) * (a))
#ifdef DEBUG
#include "debug.h"
#else
#define dbg(...) 0
#endif
using namespace std; 
template <typename T1, typename T2> inline void remin(T1& a, T2 b) { a = min(a, (T1)b);	}
template <typename T1, typename T2> inline void remax(T1& a, T2 b) { a = max(a, (T1)b);	}

const int maxN = 1 << 23;

char T[maxN];

int los(int a, int b)
{
	return rand() % (b-a) + a;
}

string F[maxN];

int main(int argc, char** argv)
{
	int t = 1;
	//scanf ("%d", &t);
	srand(atoi(argv[1]));
	
	F[0] = "a", F[1] = "ab";
	//FOR(i, 2, 40)
		//F[i] = F[i-1] + F[i-2];
		
	int s = 32;
	//printf("%s\n", F[s].c_str());
	
	//fprintf(stderr, "%d\n", F[s].size());
	
	int n = 8300000, q = 32;
	FOR(i, 0, n)
		T[i] = 'a' + los(0, 26);
	//n = F[s].size();
	printf("%s\n%d\n", T, q);
	//printf("%d\n", q);
	while (q--)
	{
		int a = los(0, n), b = los(0, n);
		if (a > b)
			swap(a, b);
		FOR(i, a, b+1)
			printf("%c", T[i]);
		printf("\n");
	}
	
	return 0;
}

