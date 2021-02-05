#include "comon.h"

namespace SuffixArray
{
	int temp[maxN], inds[maxN], C[maxN], M[maxN * 4], *R, *P;
}

bool SuffixArray::cmp(int i, int j)
{
	while (P[i] == P[j]) i++, j++;
	return P[i] < P[j];
}

void SuffixArray::brut(int n, int* T, int* res)
{
	iota(res, res + n, 0);	P = T;
	sort(res, res + n, cmp);
}

int SuffixArray::cntSort(int n, int* T, int k)
{
	int m = 0;
	if (k == 0)
	{
		for (int i=0; i<n; i+=3)	temp[m++] = i;
		for (int i=1; i<n; i+=3)	temp[m++] = i;
	}
	else for (int i=2; i<n; i+=3)	temp[m++] = i;
	for(int j=2-k; j>-1; j--)
	{
		for (int i=0; i<m; i++)
		{
			int ind = temp[i];
			int v = j & k ? R[ind + 1] : T[ind + j];
			C[v]++;
		}
		for (int i = 1; C[i-1] != m; i++)	C[i] += C[i-1];
		for(int i=m-1; i>-1; i--)
		{
			int ind = temp[i];
			int v = j & k ? R[ind + 1] : T[ind + j];
			inds[--C[v]] = ind;
		}
		fill(C, C + n+1, 0);
		if (j != 0)	copy(inds, inds + m, temp);
	}
	return m;
}

inline bool SuffixArray::differ(int* T, int i, int j)
{	return T[i+2]^T[j+2] | T[i+1]^T[j+1] | T[i]^T[j];	}

inline int SuffixArray::newInd(int i, int p)
{	return i / 3 + i % 3 * p;	}

void SuffixArray::calcRanks(int* sa, int n, int d=0)
{	for(int i=0; i<n; i++)	R[sa[i]] = i+d;	}

bool SuffixArray::cmpMerge(int i, int j)
{
	for (; true; i++, j++)
	{
		if (P[i] != P[j])				return P[i] < P[j];
		if (i % 3 != 2 and j % 3 != 2)	return R[i] < R[j];
	}
}

void SuffixArray::ks(int n, int* T, int* res)
{
	if (n < 6)
	{	brut(n, T, res);	return;	}
	int m = cntSort(n, T, 0), p = (n + 2)/3 + 1, ctr = 2;
	int *A = T + n+2, *S = res + n/3;
	A[p-1] = 1, A[m+1] = A[m+2] = 0;
	for (int i=0; i<m; i++)
	{
		if (i != 0 and differ(T, inds[i-1], inds[i]))	ctr++;
		A[newInd(inds[i], p)] = ctr;
	}
	ks(m + 1, A, S - 1);
	for (int i=0; i<m; i++)
		S[i] = S[i] < p ? S[i] * 3 : (S[i] - p) * 3 + 1;
	calcRanks(S, m, 1); 		R[n] = 0;
	int k = cntSort(n, T, 1);	P = T;
	merge(S, S+m, inds, inds+k, res, cmpMerge);
}

void SuffixArray::run(char* Tin, int n, int* sa, int* lcp, int* ranks)
{											
	R = ranks;
	for (int i=0; i<n; i++)	M[i] = (int)Tin[i] + 1;
	M[n] = M[n+1] = 0;
	n < 256 ? brut(n, M, sa) : ks(n, M, sa);
	calcRanks(sa, n);
	for (int i=0, q=0; i<n; i++)
	{
		if (R[i] == n - 1)	continue;
		int j = sa[R[i] + 1];
		while (M[i + q] == M[j + q])	q++;
		lcp[R[i]] = q;
		if (q != 0)	q--;
	}
}
