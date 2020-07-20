//
// Created by 万北宸 on 2020/7/2.
//

#ifndef METRO2_COMPUTATIONBETWEENSETS_H
#define METRO2_COMPUTATIONBETWEENSETS_H
#include <string>
#include <iostream>
using namespace std;
class Path;
struct Node1
{
    int data;
    Node1 *next;
};

class Line
{
public:
    Line();
    ~Line();
    void Insert(int i,int x);
    void Bubb();
    friend void Transfer(Path &Path);
    friend Line *Intersect(Line *A,Line *B);
    int IsEmpty();
    void Printlist();
private:
    Node1*first;
};

Line::Line()
{
    Node1*p=new Node1;
    first=p;
    first->next=NULL;
}

void Line::Insert(int i,int x)
{
    Node1*p;
    p=first;
    int count=0;
    while(p!=NULL&&count<i-1)
    {
        p=p->next;
        count++;
    }
    if(p==NULL)
    {
        cout<<"位置";
        exit(-1);
    }
    else{
        Node1*s=new Node1;
        s->data=x;
        s->next=p->next;
        p->next=s;
    }
}

Line::~Line()
{
    Node1 *q=new Node1;
    while(first!=NULL)
    {
        q=first;
        first=first->next;
        delete q;
    }
    //cout<<"XXX"<<endl;
}

void Line::Bubb()           //起泡法排序
{
    if(first->next==NULL)return;
    Node1 *p=first->next;
    Node1 *pre=NULL;
    while(p->next!=pre)
    {
        while(p->next!=pre)
        {
            if(p->data>p->next->data)
            {
                int temp=p->data;
                p->data=p->next->data;
                p->next->data=temp;
            }
            p=p->next;
        }
        pre=p;
        p=first->next;
    }
}

int Line::IsEmpty()
{
    if(first->next==NULL)
        return 1;
    else return 0;
}

void Line::Printlist()
{
    if(first->next==NULL)
    {
        cout<<"the set is empty"<<endl;
        return;
    }
    Node1*p;
    p=first->next;
    while(p!=NULL)
    {
        cout<<(p->data)<<" ";
        p=p->next;
    }
}


Line *Intersect(Line *A,Line *B)
{
      A->Bubb();
    B->Bubb();
    Line *List=new Line;
    Node1*p,*q;
    p=A->first->next;
    q=B->first->next;
    while(p!=NULL&&q!=NULL)
    {
        if(p->data<q->data)
            p=p->next;
        else if(p->data>q->data)
            q=q->next;
        else
        {
            List->Insert(1,p->data);
            p=p->next;
            q=q->next;
        }
    }
    List->Bubb();
    return List;
}

#endif //METRO2_COMPUTATIONBETWEENSETS_H
