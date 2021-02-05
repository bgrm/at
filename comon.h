#ifndef __CMN__
#define __CMN__

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <vector>
#include <queue>
using namespace std;
using namespace chrono;

const int maxN = 1 << 23;

#define MEASURE(expr, log)							\
auto start = high_resolution_clock::now();			\
expr;												\
tim = high_resolution_clock::now() - start;			\
fprintf(stderr, "%s took %Lfs\n", log, tim.count());

#define TEST(call)									\
long double s = 0; int q; scanf ("%d", &q);			\
for (int i=0; i<q; i++) {							\
	vector <int> inds; scanf ("%s", P);				\
	MEASURE(inds = call(P, strlen(P)), "\tquery")	\
	sort(inds.begin(), inds.end());					\
	for (int i : inds) printf("%d ", i);			\
	printf("\n");	s += tim.count();				\
}													\
fprintf(stderr, "average query time: %Lfs\n\n", s / q);

namespace SuffixArray
{
	extern bool cmp(int i, int j);
	extern void brut(int n, int* T, int* res);
	extern int cntSort(int n, int* T, int k);
	extern inline bool differ(int* T, int i, int j);
	extern inline int newInd(int i, int p);
	extern void calcRanks(int* sa, int n, int d);
	extern bool cmpMerge(int i, int j);
	extern void ks(int n, int* T, int* res);
	extern void run(char* Tin, int n, int* sa, int* lcp, int* ranks);
}

struct RMQ
{
	vector<int> v; int n;
	static const int b = 30; // block size
	vector<int> mask, t; // mask and sparse table

	int op(int x, int y);
	int lsb(int x);
	int msb_index(int x);
	int small(int r, int size);
	void init(const vector<int>& v_);
	int query(int l, int r);
};

#endif //__CMN__
