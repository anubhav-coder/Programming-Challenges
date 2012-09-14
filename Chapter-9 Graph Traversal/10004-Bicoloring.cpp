#include<iostream>
#include <queue>
#include <stack>
using namespace std;
#define MAXV 1000
#define uncolored -1
#define BLACK 0
#define WHITE 1
struct edgenode
{
    int y;
    int weight;
    edgenode *next;
};
struct graph
{
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
};
class Graph
{

    public:
     bool processed[MAXV+1];
     int color[MAXV+1];
    bool discovered[MAXV+1];
    int parent[MAXV+1];
    bool clos;
        Graph(graph *g, bool directed);
        void insert_edge(graph *g,int x,int y,bool directed);
        void read_graph(graph *g, bool directed,int ,int );
        void print_graph(graph *g);
        void initialize_search(graph *g);
        void process_vertex_early(int v)
        {
            //cout<<"Vertex started: "<<v<<endl;
        }
        int complement(int color)
        {
            if(color==WHITE)
                return BLACK;
            else
                return WHITE;
        }
        void process_edge(int x,int y)
        {
            if(color[x]==color[y])
            {
                cout<<"NOT BICOLORABLE\n";
                clos=true;
                //cout<<"edge processed: "<<x<<" ,"<<y<<" ->"<<color[x]<<" ,"<<color[y]<<endl;
            }
            color[y]=complement(color[x]);
            //cout<<"edge processed: "<<x<<" ,"<<y<<" ->"<<color[x]<<" ,"<<color[y]<<endl;
        }
        void process_vertex_lately(int v)
        {
            //cout<<"Vertex ended: "<<v<<endl;
        }
        void bicolor(graph *g);
        void bfs(graph *g,int start);
        void find_path(int start, int end);
    protected:
    private:
};
Graph::Graph(graph *g, bool directed)
{
    int i;
    g->nvertices=0;
    g->nedges=0;
    g->directed=directed;
    for(i=0;i<=MAXV;i++)
    {
        g->degree[i]=0;
        g->edges[i]=NULL;
    }
}
void Graph::insert_edge(graph *g,int x,int y,bool directed)
{
    edgenode *p=new edgenode;
    p->weight=0;
    p->y=y;
    p->next=g->edges[x];
    g->edges[x]=p;
    g->degree[x]++;
    if(directed==false)
        insert_edge(g,y,x,true);
    else
        g->nedges++;
}
void Graph::read_graph(graph *g,bool directed,int vert, int edge)
{
    int i;
    int m;
    int x,y;
    //Graph(g,directed);
    g->nvertices=vert;
    m=edge;
    for(i=1;i<=m;i++)
    {
        cin>>x>>y;
        insert_edge(g,x,y,directed);
    }

}
void Graph::initialize_search(graph *g)
{
    for(int i=0;i<=g->nvertices-1;i++)
    {
        processed[i]=discovered[i]=false;
        parent[i]=-1;
    }
    clos=false;
}
void Graph::bfs(graph *g, int start)
{
    if(clos==true)
        return;
    queue<int> q;
    int v;
    int y;
    edgenode *p;
    q.push(start);
    discovered[start]=true;
    while(!q.empty())
    {
        v=q.front();
        q.pop();
        process_vertex_early(v);
        processed[v]=true;
        p=g->edges[v];
        while(p!=NULL)
        {
            y=p->y;
            if((!processed[y]) || g->directed)
                process_edge(v,y);
            if(!discovered[y])
            {
                q.push(y);
                discovered[y]=true;
                parent[y]=v;
                process_edge(v,y);
            }
            if(clos==true)
                return;
               // cout<<v<<"--"<<y<<endl;
            p=p->next;
        }
       // cout<<color[v]<<"--"<<color[y]<<endl;
    }
    process_vertex_lately(v);
}
void Graph::bicolor(graph *g)
{
    for(int i=0;i<g->nvertices;i++)
    {
        color[i]=-1;
    }
    for(int i=0;i<g->nvertices-1;i++)
    {
        if(discovered[i]==false)
        {
           // cout<<"WTF"<<i<<endl;
            color[i]=WHITE;
            bfs(g,i);
        }
        if(clos==true)
            return;
    }
    cout<<"BICOLORABLE\n";
}
int main()
{
    int vert,edge;
    graph *g = new graph;
    cin>>vert;
    while(vert!=0)
    {
        cin>>edge;
        Graph G = Graph(g,false);
        G.read_graph(g,false,vert,edge);
        G.initialize_search(g);
        G.bicolor(g);
        cin>>vert;
    }
    return 0;
}
