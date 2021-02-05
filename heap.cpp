#include "comon.h"

struct Node
{
	Node *fat, *bro, *son;	//	ojciec, prawy brat, pierwszy syn
	Node *dual, *link; // węzeł w drzewie dualnym, link do max-prefixu (tylko w pierwotnym drzewie)
	int in, out, idx;
	char let;
	
	Node* getSon(char c)
	{
		for (Node* v = son; v; v = v->bro)
			if (v->let == c)
				return v;
		return NULL;
	}
	
	bool ancOf(Node* pred)
	{
		return in <= pred->in and pred->out <= out;
	}
	
	void adopt(Node* s, char a)
	{
		s->fat = this;
		s->bro = son;
		son = s; // s dodwany jako pierwszy syn
		s->let = a;
	}
	
	void print(int d)
	{
		for (int i=0; i<d; i++)	
			printf("   ");
		printf("%c [%d, %d] %d  (lind %d)\n", let, in, out, idx, link->idx);
		for (Node* u = son; u; u = u->bro)
			u->print(d+1);
	}
};

vector <int> mpt; // pusty

struct APHeap
{
	Node MEM[maxN * 2], *root;
	Node* N[maxN];
	int vis[maxN];	
	
	Node* newNode()
	{
		static int s = 0;
		Node* a = MEM + (s++);
		Node* b = MEM + (s++);
		a->dual = b;
		b->dual = a;
		return a;
	}
	
	Node* maxAugPref(Node* v, char a, Node** last)
	{
		*last = v;
		while (!v->dual->getSon(a))
			*last = v, v = v->fat;
		v = v->dual->getSon(a);
		return v->dual;
	}
	
	void dfs(Node* v)
	{
		static int inCtr = 0;
		v->in = inCtr++;
		for (Node* u = v->son; u; u = u->bro)
			dfs(u);
		v->out = inCtr;
	}
	
	void init(char* T, int n)
	{
		Node* v = root = newNode();
		for (int i=n-1; i>=0; i--)
		{
			if (!root->getSon(T[i]))
			{
				v = newNode();
				root->adopt(v, T[i]);
				root->dual->adopt(v->dual, T[i]);
			}
		
			else
			{
				Node* last;
				v = maxAugPref(v, T[i], &last);
				v->adopt(newNode(), last->let);
				v = v->son;
				last->dual->adopt(v->dual, T[i]);
			}
			
			N[i] = v;
			v->idx = i;
		}
		dfs(root);
		v = root;
		for (int i=n-1; i>=0; i--)
		{
			v = maxAugPref(v, T[i], &v);
			N[i]->link = v;
		}
		root->link = root;
	}
	
	vector <int> query(char* P, int n)
	{
		int depth, offset = 0;
		static int visCtr = 0;
		vector <int> ret;
		do
		{
			Node* v = root;
			depth = 0;
			for (int i=0; i<n; i++)
			{
				Node* s = v->getSon(P[i]);
				if (!s)
					break;
				v = s;
				depth++;
			}

			visCtr++;
			for (Node* u = v; u != root; u = u->fat)
				if (v->ancOf(u->link))
					offset == 0 ? ret.push_back(u->idx),0 : vis[u->idx] = visCtr;
			if (depth == n and v->son and v != root)
			{
				queue <Node*> Q;
				for (Q.push(v->son); !Q.empty(); Q.pop())
				{
					Node* u = Q.front();
					offset == 0 ? ret.push_back(u->idx),0 : vis[u->idx] = visCtr;
					for (Node* w : {u->son, u->bro})
						if (w)	Q.push(w);
				}
			}
			if (offset != 0)
			{
				int s = 0;
				for (int i : ret)
					if (vis[i + offset] == visCtr)
						ret[s++] = i;
				ret.resize(s);
			}
			P += depth, n -= depth, offset += depth;
		}
		while (depth != 0 and n != 0);
		return ret;
	}
	
	void print() { root->print(0);	}
}H;

char T[maxN], P[maxN];

int main()
{
	duration <long double> tim;
	scanf ("%s", T);
	MEASURE(H.init(T, strlen(T)), "heap init");
	//H.print();
	TEST(H.query);
}

