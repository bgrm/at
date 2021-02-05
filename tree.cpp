#include "comon.h"

struct Node
{
	Node *fat, *bro, *son, *nxt;
	char* lab;						// wskaźnik na etykietę krawędzi
	int dep, len, in, out;			// długości etykiet wierzchołka i krawędzi, czas wejścia i wyjścia
	vector <int> inds;				// indeksy sufiksów kończących się na krawędzi od ojca do this
	
	void adopt(Node* u, char* a, int b)
	{
		u->fat = this;
		u->bro = son;
		u->lab = a;
		u->dep = dep + b;
		u->len = b;
		son = u;
	}
	
	void breakEdge(Node* u, int d, Node* w) // w into this--->u
	{
		adopt(w, u->lab, u->len - d);
		for (Node* x = son; x; x = x->bro) if (x->bro == u)
		{
			x->bro = u->bro;
			u->bro = NULL;
			break;
		}
		w->adopt(u, u->lab + w->len, d);
	}
	
	Node* getSon(char c)
	{
		for (Node* u = son; u; u = u->bro)
			if (*(u->lab) == c)
				return u;
		return NULL;
	}
	
	void print(int d)
	{	
		for (int i=0; i<d; i++)
			printf("   ");
		for (int i=0; i<len; i++)
			printf("%c", lab[i]);
		printf(" %d [%d-%d]  {", dep, in, out);
		for (int i : inds)
			printf("%d,", i);
		printf("} %d\n", nxt ? nxt->dep : -1);
		for (Node* u = son; u; u = u->bro)
			u->print(d+1);
	}
};

struct SuffixTree
{
	Node MEM[maxN * 2], *root;
	int n;
	
	Node* newNode()
	{
		static int s = 0;
		return MEM + (s++);
	}
	
	void dfs(Node* v)
	{
		static int inCtr = 0;
		v->in = inCtr++;
		for (Node* u = v->son; u; u = u->bro)
			dfs(u);
		v->out = inCtr;
	}
	
	void dfsNxt(Node* v)
	{
		static Node* last = NULL;
		for (Node* u : {v->bro, v->son})
			if (u)	dfsNxt(u);
		v->nxt = last;
		if (!v->inds.empty())
			last = v;
	}
	
	void init(char* T, int* S, int* lcp)
	{
		n = strlen(T);
		lcp[n-1] = 0;
		Node* v = root = newNode();
		for (int i=0; i<n; i++)
		{
			if (v == root or v->son)
			{
				v->adopt(newNode(), T + S[i] + v->dep, n - S[i] - v->dep);
				v = v->son;
			}
			else
			{
				v->lab = T + S[i] + v->fat->dep;
				v->dep = n - S[i];
				v->len = v->dep - v->fat->dep;
			}
			
			while (v != root and lcp[i] <= v->fat->dep)
				v = v->fat;
			if (lcp[i] != v->dep)
			{
				v->fat->breakEdge(v, v->dep - lcp[i], newNode());
				v = v->fat;
			}
		}
		v = root;
		for (int i=0; i<n; i++)
		{
			while (v->dep < n - S[i])
				v = v->getSon(T[S[i] + v->dep]);
			v->inds.push_back(S[i]);
			while (v != root and lcp[i] <= v->fat->dep)
				v = v->fat;
		}
		dfs(root);
		dfsNxt(root);
		//root->print(0);
	}
	
	vector <int> query(char* p, int m)
	{
		int len = 0;
		Node* v = root;
		for (; m; m -= len)
		{
			v = v->getSon(*p);
			if (!v)
				return {};
			len = min(v->len, m);
			if (strncmp(p, v->lab, len))
				return {};
			p += len;
		}
		
		auto it = upper_bound(v->inds.rbegin(), v->inds.rend(), n - v->dep + v->len - len);
		vector <int> ret (v->inds.rbegin(), it);
		for (Node* u = v->nxt; u and u->in < v->out; u = u->nxt)
			ret.insert(ret.end(), u->inds.begin(), u->inds.end());
		return ret;
	}
}tree;

char T[maxN], P[maxN];
int S[maxN], LCP[maxN], R[maxN];

int main()
{
	duration <long double> tim;
	scanf ("%s", T);
	SuffixArray::run(T, strlen(T), S, LCP, R);
	MEASURE(tree.init(T, S, LCP), "tree init");
	TEST(tree.query);
}
