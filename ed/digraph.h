#define maxV 1024 
#define VIS 1
#define N_VIS 0

struct node{
  Vertex w;
  struct node *next;
};

typedef struct node *link;

struct digraph{
  int V;
  int A;
  link *adj;
};

typedef struct digraph *Digraph;

link NEW(Vertex w, link next);
Digraph DIGRAPHinit();
void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w);
void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w);
void DIGRAPHshow(Digraph G);
int DIGRAPHpath(Digraph G, Vertex s, Vertex t);

static int lbl[maxV];
static Vertex parnt[maxV];
