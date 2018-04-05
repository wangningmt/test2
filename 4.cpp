#include<iostream>
#include <string>
#include<cstdio>
#include<stdlib.h>
using namespace std;
# define Maxsize 100
struct Node    // 以表的形式存储的树结点
{
    char data;
    int parent;
    int lchild;
    int rchild;
};
typedef enum PointerTag{Link,Thread};       //Link==0:指针；Thread==1,线索；
struct TreeNode                             // 以二叉链表存储的树结点
{
    char data;
    TreeNode *l;
    TreeNode *r;
	PointerTag LTag,RTag;

};

// 创建树的表并转化为二叉树

int creattable(Node table[])
{
    int n, k, i, j;
    cout << "输入结点个数(<20): ";
    cin >> n;
    if (n > 0)
    {
        cout << "输入结点信息和双亲编号(第一个请输入根结点信息如A -1 ):" << endl;
        for (i = 0; i < n; i++)
        {
            cin >> table[i].data >> table[i].parent;
            table[i].lchild = table[i].rchild = 0;
        }
        for (i = 0; i < n; i++)
        {
            for (j = 1; j < n; j++)
            {
                if (table[j].parent == i)
                {
                    if (table[i].lchild == 0)
                    {
                       table[i].lchild = j;
                        k = j;
                    }
                    else
                    {
                       table[k].rchild = j;
                        k = j;
                    }
                }
            }
        }
       for (i = 0; i < n; i++)
        {
            cout << table[i].data  << table[i].parent  << table[i].lchild  << table[i].rchild  << endl;
        }
    }
    return n;
}
// 将表转化为二叉链表
void Build(TreeNode *&p, Node node[], int pos, int n)
{
    if (n > 0)
    {
        if (p == 0)
        {
            p = new TreeNode;
            p->l = p->r = 0;
        }
        p->data = node[pos].data;
        if (node[pos].lchild)
            Build(p->l, node, node[pos].lchild, n);
        if (node[pos].rchild)
           Build(p->r, node, node[pos].rchild, n);
    }
}
// 访问结点

void Visit(TreeNode *p)
{
    cout<<p->data<<" ";
}

// 按先序遍历,递归
void Preorder(TreeNode *root)
{
   TreeNode *p = root;
   if (p!= 0)
   {
      Visit(p);
      Preorder(p->l);

      Preorder(p->r);
   }
}
//先序非递归遍历
void Preorder1 (TreeNode *root)
{
	TreeNode *q,*S[Maxsize];           //定义树的结点栈
	int top;
	if(root==NULL)
		return;
	top=-1;
	S[++top]=root;
	while(top>=0)
	{
		q=S[top--];
		Visit(q);
		if(q->r !=NULL)
			S[++top]=q->r ;
		if(q->l!=NULL)
			S[++top]=q->l ;
	}

}
//中序非递归遍历二叉树
void inorder(TreeNode *root)
{
	TreeNode *q,*S[Maxsize];
	int top;
	if(root==NULL)
		return;
	top=-1;
	q=root;
	while(!(q==NULL && top==-1))
	{
		while(q!=NULL)           //搜索到最左下的结点；
		{
			S[++top]=q;
			q=q->l ;
		}
		q=S[top--];
		Visit(q);
		q=q->r ;                  //向右搜素；
	}
}
//后序非递归遍历二叉树
void lastorder(TreeNode *root)
{
	TreeNode *p,*q,*S[Maxsize];
	int top;
	if(root==NULL)
		return;
	top=-1;
	p=root;
	q=NULL;                              //左子树尚未遍历，最近已访问结点q为空；
	while(!(p==NULL && top==-1))
	{
		while(p!=NULL)
		{
			S[++top]=p;
			p=p->l ;                   //向左搜索；
		}
		p=S[top--];                   //退栈；
		if(q!=p->r)
		{
			S[++top]=p;              //再进栈
			p=p->r;                  //转右子树
			q=NULL;                  //右子树尚未遍历，最近已访问结点q为空
		}
		else
		{
			Visit(p);
			q=p;
			p=NULL;
		}
	}
}
//中序线索化二叉树
void InThreading(TreeNode *root)
{
	TreeNode *p,*pre;
	p=root;
	pre=NULL;
	if(p==NULL)
		return;
		InThreading(p->l);    //左子树线索化；
		if(p->l==NULL)
		{
			p->l=pre;
			p->LTag=Thread;

		}
		if(pre!=NULL&&pre->r==NULL)
		{
			pre->r=p;
			pre->RTag=Thread;
		}
		pre=p;
		InThreading(p->r);        //右子树线索化

}
void MENU()
//程序主菜单
{
	printf("               -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf("               §               树与二叉树              §\n");
	printf("               §                                       §\n");
	printf("               §        1.用双亲表示法创建树           §\n");
	printf("               §        2.将树转换成二叉树             §\n");
	printf("               §        3.二叉树的先序非递归遍历       §\n");
	printf("               §        4.二叉树的中序非递归遍历       §\n");
	printf("               §        5.二叉树的后序非递归遍历       §\n");
	printf("               §        6.二叉树的中序线索化           §\n");
	printf("               §        7.退出操作                     §\n");
	printf("               §                                       §\n");
	printf("               -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
}



int main()

{

    Node node[20];
	int n,m;
    TreeNode *root = 0;

	while(1)
	{
		MENU();
		cout<<"请输入你要选择的操作:"<<endl;
		cin>>m;
		switch(m)
		{
		case 1:
			n= creattable(node);
			break;
		case 2:
			Build(root, node, 0, n);
			break;
		case 3:
			Preorder1(root);
			break;
		case 4:
			inorder(root);
			break;
		case 5:
			lastorder(root);
			break;
		case 6:
			InThreading(root);
			break;
		case 7:
				{
					printf("\n\n退出\n\n");
					exit(0);
					break;
				}
		}
		system("pause");
	    system("cls");
	}

    return 0;

}

