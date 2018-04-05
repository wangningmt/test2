#include<iostream>
#include <string>
#include<cstdio>
#include<stdlib.h>
using namespace std;
# define Maxsize 100
struct Node    // �Ա����ʽ�洢�������
{
    char data;
    int parent;
    int lchild;
    int rchild;
};
typedef enum PointerTag{Link,Thread};       //Link==0:ָ�룻Thread==1,������
struct TreeNode                             // �Զ�������洢�������
{
    char data;
    TreeNode *l;
    TreeNode *r;
	PointerTag LTag,RTag;

};

// �������ı�ת��Ϊ������

int creattable(Node table[])
{
    int n, k, i, j;
    cout << "���������(<20): ";
    cin >> n;
    if (n > 0)
    {
        cout << "��������Ϣ��˫�ױ��(��һ��������������Ϣ��A -1 ):" << endl;
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
// ����ת��Ϊ��������
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
// ���ʽ��

void Visit(TreeNode *p)
{
    cout<<p->data<<" ";
}

// ���������,�ݹ�
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
//����ǵݹ����
void Preorder1 (TreeNode *root)
{
	TreeNode *q,*S[Maxsize];           //�������Ľ��ջ
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
//����ǵݹ����������
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
		while(q!=NULL)           //�����������µĽ�㣻
		{
			S[++top]=q;
			q=q->l ;
		}
		q=S[top--];
		Visit(q);
		q=q->r ;                  //�������أ�
	}
}
//����ǵݹ����������
void lastorder(TreeNode *root)
{
	TreeNode *p,*q,*S[Maxsize];
	int top;
	if(root==NULL)
		return;
	top=-1;
	p=root;
	q=NULL;                              //��������δ����������ѷ��ʽ��qΪ�գ�
	while(!(p==NULL && top==-1))
	{
		while(p!=NULL)
		{
			S[++top]=p;
			p=p->l ;                   //����������
		}
		p=S[top--];                   //��ջ��
		if(q!=p->r)
		{
			S[++top]=p;              //�ٽ�ջ
			p=p->r;                  //ת������
			q=NULL;                  //��������δ����������ѷ��ʽ��qΪ��
		}
		else
		{
			Visit(p);
			q=p;
			p=NULL;
		}
	}
}
//����������������
void InThreading(TreeNode *root)
{
	TreeNode *p,*pre;
	p=root;
	pre=NULL;
	if(p==NULL)
		return;
		InThreading(p->l);    //��������������
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
		InThreading(p->r);        //������������

}
void MENU()
//�������˵�
{
	printf("               -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf("               ��               ���������              ��\n");
	printf("               ��                                       ��\n");
	printf("               ��        1.��˫�ױ�ʾ��������           ��\n");
	printf("               ��        2.����ת���ɶ�����             ��\n");
	printf("               ��        3.������������ǵݹ����       ��\n");
	printf("               ��        4.������������ǵݹ����       ��\n");
	printf("               ��        5.�������ĺ���ǵݹ����       ��\n");
	printf("               ��        6.������������������           ��\n");
	printf("               ��        7.�˳�����                     ��\n");
	printf("               ��                                       ��\n");
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
		cout<<"��������Ҫѡ��Ĳ���:"<<endl;
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
					printf("\n\n�˳�\n\n");
					exit(0);
					break;
				}
		}
		system("pause");
	    system("cls");
	}

    return 0;

}

