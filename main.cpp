#include <iostream>
#include <fstream>
#include <string>
#include "ComputationBetweenSets.h"
#include "MGraph.h"
using namespace std;
void Dijkstra(MGraph G,string S1,string S2, Path *path1)
{
    int i,j,k,num,v1,v2;
    int n=G.vertexNum;
    Path *path=new Path[n];
    int dist[n],S[n],IsInS[n];
    for(i=0;i<n;i++)
    {
        if(S1==G.vertex[i]->stationName)
        {
            v1=i;                                           //由输入的两个站的名字确定起点以及终点在顶点数组中是第几个，比如A站是第0个
            break;
        }
    }
    for(i=0;i<n;i++)
    {
        if(S2==G.vertex[i]->stationName)
        {
            v2=i;
            break;
        }
    }
    for(i=0;i<n;i++)
    {
        dist[i]=G.arc[v1][i];                               //初始化dist数组,S集合,IsInS集合
        IsInS[i]=0;
        if(dist[i]==1)
        {
            path[i].add(*G.vertex[v1]);
            path[i].add(*G.vertex[i]);                      //初始化path，如果从v1到该点有边,则加入v1和该点到path
        }
    }
    S[0]=v1;                                                //初始化已经找到最短路径的集合S
    dist[v1]=0;                                             //初始化dist矩阵
    num=1;
    while(num<n)
    {
        for(i=0;i<n;i++)                                    //设定k为不在S中的编号最小的顶点的编号
        {
            for(j=0;j<num;j++)
            {
                if(S[j]==i)
                {
                    IsInS[i]=1;                             //某一点在S中则为1，否则为0
                    break;
                }
            }
        }
        for(i=0;i<n;i++)
        {
            if(IsInS[i]==0)                                 //i不在S中，令k初值为i，退出循环
            {
                k=i;
                break;
            }
        }
        for(i=0;i<n;i++)                                    //求得dist最小的顶点的编号为k
        {
            if(IsInS[i]==0&&dist[i]<=dist[k])
                k=i;
        }
        S[num++]=k;                                         //加入k到S
        for(i=0;i<n;i++)                                    //修改path与dist
        {
            if(IsInS[i]==0&&dist[i]>dist[k]+G.arc[k][i])
            {
                dist[i]=dist[k]+G.arc[k][i];
                Path *p;
                p=&path[i];
                path[k].Clone2(p);                          //修改path时先将v1到k赋值过去再添加i结点到末尾
                path[i].add(*G.vertex[i]);
            }
        }
        dist[k]=0;
    }
    path[v2].Clone2(path1);
}
void Transfer(Path &Path)
{
    Node2 *p,*pre;
    p=Path.first->next;
    pre=p;
    cout<<p->data.stationName<<"————————>";
    p=p->next;
    while(p->next!=NULL)
    {
        if(Intersect(pre->data.line,p->next->data.line)->IsEmpty())
        {
            cout<<p->data.stationName<<"（换乘 ";
            Intersect(p->data.line,p->next->data.line)->Printlist();
            cout<<"号线）——————>";
        }
        p=p->next;
        pre=pre->next;
    }
    cout<<p->data.stationName;
    return ;
}
Station *ReadVertex(int n,Line *L)
{
    int i,k,m1,m2;
    ifstream infile("C:\\Users\\万北宸\\CLionProjects\\地铁换乘\\Vertex.txt");
    //ifstream infile("C:\\Users\\万北宸\\CLionProjects\\地铁换乘\\Vertex2.txt");
    if(!infile)
    {
        cout<<"load failed"<<endl<<"请在代码中修改所读取文件的绝对路径";
        exit(-1);
    }
    else
        cout<<"load success"<<endl;
    Station *vertex=new Station[n];
    int *b=new int[n*n];
    for(i=0;i<n;i++)
    {
        infile>>vertex[i].stationName;
        vertex[i].line=&L[i];
        infile>>k;
        for(m1=0;m1<k;m1++)
        {
            infile>>m2;
            vertex[i].line->Insert(1,m2);
        }
    }
    return vertex;
}
int *ReadArc(int n)
{
    int i,j;
    ifstream infile("C:\\Users\\万北宸\\CLionProjects\\地铁换乘\\Arc.txt");
    //ifstream infile("C:\\Users\\万北宸\\CLionProjects\\地铁换乘\\Arc2.txt");
    if(!infile)
    {
        cout<<"load failed"<<endl<<"请在代码中修改所读取文件的绝对路径";
        exit(-1);
    }
    else
        cout<<"load success"<<endl;
    int *b=new int[n*n];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            infile>>*(b+i*n+j);
        }
    return b;
}
int main()
{
    int n;
    string From,To;
    n=80;
    //n=13;
    Station *vertex;
    int *b;
    Line L[n];
    vertex=ReadVertex(n,L);
    b=ReadArc(n);
    MGraph metro(vertex,b,n);                               //从文件读取，构造一个图
    cout<<endl;
    cout<<"请分别输入起点与终点"<<endl;
    cin>>From>>To;
    Path *path=new Path;
    Dijkstra(metro,From,To,path);
    Transfer(*path);
}
