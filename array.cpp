#include "comon.h"

char T[maxN];
int S[maxN], LCP[maxN], R[maxN], n;
RMQ rmq;

int lcp(int i, int j)
{
	if (i > j)
		swap(i, j);
	return rmq.query(i, j-1);
}

int lowerBound(char* P)
{
	#define EXPAND(i, d) while (d < m and T[S[i] + d] == P[d]) d++
	int m = strlen(P), a = 0, b = n-1, la = 0, lb = 0;
	EXPAND(a, la);
	EXPAND(b, lb);
	int mxInd = la < lb ? b : a;
	int mxLen = max(la, lb);
	if (T[S[b] + lb] < P[lb])
		return n;
	if (P[la] <= T[S[a] + la])
		return 0;
	
	while (b - a > 1)
	{
		int c = (a + b) / 2;
		int s = min({mxLen, m, lcp(c, mxInd)});
		
		if (s == mxLen)
		{
			EXPAND(c, s);
			mxInd = c;
			mxLen = s;
		}
		(T[S[c] + s] < P[s] ? a : b) = c;
	}
	return b;
}

vector <int> matches(char* P, int m)
{
	int a = lowerBound(P);
	P[m-1]++;
	int b = lowerBound(P);
	P[m-1]--;
	return vector <int> (S + a, S + b);		
}

char P[maxN];

int main()
{
	duration <long double> tim;
	scanf ("%s", T);
	n = strlen(T);
	MEASURE(
	(
		SuffixArray::run(T, n, S, LCP, R),
		rmq.init(vector <int> (LCP, LCP + n-1))
	), "array init");
	TEST(matches);
}
