#include <iostream>  
#include <queue>  
#include <vector>  
using namespace std;  
const int N=405;  
struct rec  
{  
    int v,w;  
};  
vector<rec> edge[N*N];  
int n,st,ed;  
__int64 dis[N*N];  
bool vis[N*N];  
struct cmp  
{  
    bool operator()(int a,int b)  
    {   
        return dis[a]>dis[b];  
    }   
};  
void Dijkstra()  
{  

	//master
    priority_queue<int,vector<int>,cmp> Q;  
    memset(dis,-1,sizeof(dis));  
    memset(vis,0,sizeof(vis));  
    int i,u,v;  
    Q.push(st);  
    dis[st]=0;  
    while(!Q.empty())  
    {  
        u=Q.top();  
        Q.pop();  
        vis[u]=0;  
        if(u==ed)  
            break;  
        for(i=0;i<edge[u].size();i++)  
        {  
            v=edge[u][i].v;  
            if(dis[v]==-1 || dis[v]>dis[u]+edge[u][i].w)  
            {  
                dis[v]=dis[u]+edge[u][i].w;  
                if(!vis[v])  
                {  
                    vis[v]=1;  
                    Q.push(v);  
                }  
            }  
        }  
    }  
}  