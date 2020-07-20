//
// Created by 万北宸 on 2020/7/2.
//

#ifndef METRO2_MGRAPH_H
#define METRO2_MGRAPH_H
#include <iostream>
#include <string>
#include "ComputationBetweenSets.h"
using namespace std;
const int MaxSize=100;
const int MaxNum=100;
struct Station
{
    string stationName;              //站的名字
    Line *line;                      //分别在几号线
};
struct Node2
{
    Station data;
    Node2 *next;
};

class Path
{
public:
    Path();
    ~Path();
    void add(Station x);
    void Clone2(Path *s1);
    friend void Transfer(Path &Path);
private:
    Node2*first;
};
Path::Path()
{
    Node2*p=new Node2;
    first=p;
    first->next=NULL;
}

void Path::Clone2(Path *s1)          //将一个链表赋值给另外一个链表，调用时将this指向的链表赋值给s1指向的链表
{
    Node2 *p;
    Node2 *F;
    F=s1->first;
    p=first->next;
    while(p!=NULL)
    {
        Node2 *s=new Node2;
        F->next=s;
        s->data.stationName=p->data.stationName;
        s->data.line=p->data.line;
        p=p->next;
        F=F->next;
        if(p==NULL)
            s->next=NULL;
    }
}

void Path::add(Station x)            //添加结点x到链表末端
{
    Node2 *p;
    p=first;
    while(p->next!=NULL)
        p=p->next;
    Node2 *s=new Node2;
    s->data.stationName=x.stationName;
    s->data.line=x.line;
    s->next=NULL;
    p->next=s;
}

Path::~Path()
{
    Node2 *q=new Node2;
    while(first!=NULL)
    {
        q=first;
        first=first->next;
        delete q;
    }
    //cout<<"XXX"<<endl;
}

class MGraph
{
public:
    MGraph(Station a[],int *b,int n);
    ~MGraph(){};
    friend void Dijkstra (MGraph G,string S1,string S2, Path *path);
private:
    Station *vertex[MaxSize];               //图的结构中，顶点为指向station结点的指针
    int arc[MaxSize][MaxSize];
    int vertexNum;
};

MGraph::MGraph(Station a[], int *b, int n)
{
    int i,j;
    vertexNum=n;
    for(i=0;i<vertexNum;i++)
    {
        vertex[i]=&a[i];
    }
    for(i=0;i<vertexNum;i++)
        for(j=0;j<vertexNum;j++)
        {
            if(*(b+i*n+j)==1)
                arc[i][j]=1;
            else
                arc[i][j]=MaxNum;               //用INT_MAX会溢出
        }
}

#endif //METRO2_MGRAPH_H
