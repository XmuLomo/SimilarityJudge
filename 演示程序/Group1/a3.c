#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct LinkNode
{
	int num;
	char name[20];
	int score;
	struct Link *next;
}LinkNode,*LinkPoint;


/*������������*/
LinkPoint Create()
{
	int num;
	LinkPoint p;
	LinkPoint q1,q2;
	LinkPoint head=(LinkPoint)malloc(sizeof(LinkNode));
	
	if(head==NULL)
		exit(0);

	head->num=-999;
	head->next=NULL;
	
	printf("������ѧ��ѧ��\n");

    while(scanf("%d",&num))
	{
		getchar();
		if(num==0)
		break;
		p=(LinkPoint)malloc(sizeof(LinkNode));
		if(p==NULL)
			exit(0);
		p->num=num;
		printf("������ѧ������ �ɼ�\n");
		scanf("%s %d",p->name,&p->score);


		/*��λ��*/
		q1=head;
		q2=head->next;
		
		while(q2!=NULL)
		{
			if(num > q1->num && num < q2->num)
				break;
			else
			{
				q1=q2;
				q2=q2->next;			
			}
	
		}

	       p->next=q2;
		   q1->next=p;



		printf("������ѧ��ѧ��(����0����)\n");
	}

	return head;
}

void PrintLink(LinkPoint head)
{
	LinkPoint p;
	p=head->next;
	while(p!=NULL)
	{
		printf("ѧ��%-5d ����%-8s �ɼ�%-5d\n",p->num,p->name,p->score);
		p=p->next;
	}
}

/*Ѱ��ѧ��Ϊnum��ѧ�� ��������ָ��*/
LinkPoint SearchId(LinkPoint head,int id)
{
	LinkPoint p;

	p=head->next;
	
	while(p!=NULL)
	{
	   if(p->num==id)
	   {
		 break;
	   }
	   p=p->next;
	}
	if(p==NULL)
	{
		printf("not found!\n");
		return NULL;
	}

	return p;
}


/*��ѧ�Ų��� */
void InsertNode(LinkPoint head,int number, char name[],int score)
{
   LinkPoint p;
   LinkPoint q1,q2;
   int num;

   p=(LinkPoint)malloc(sizeof(LinkNode));
   
   if(p==NULL)
	   exit(0);

   p->num=number;
   strcpy(p->name,name);
   p->score=score;

   /*��λ��*/
		q1=head;
		q2=head->next;
		num = p->num;

		while(q2!=NULL)
		{
			if(num > q1->num && num < q2->num)
				break;
			else
			{
				q1=q2;
				q2=q2->next;			
			}
	
		}
	       p->next=q2;
		   q1->next=p;
}




/*ɾ��ѧ��*/
void DeleteNode(LinkPoint head,int num)
{
	LinkPoint del;
	LinkPoint p;

	del =SearchId(head,num);
	if(del == NULL)
	{
		printf("not found!\n");
		return ;
	}
	p=head;
	while(p->next!=del)
	{
		p=p->next;
	}

	p->next=del->next;
	free(del);
}


/*ɾ����������*/
void DeleteLink(head)
{
	LinkPoint p=head;
    LinkPoint q;

	while(p!=NULL)
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(head);
	printf("ɾ���ɹ���\n");
}



int main()
{  
	int num,score;
	char name[10];
	
    LinkPoint head;
    LinkPoint p;

	head=Create();
	PrintLink(head);

	printf("������ҵ�ѧ��\n");
    scanf("%d",&num);
	p = SearchId(head,num);
	if(p!=NULL)  //�ҵ��ˣ�
	printf("ѧ��%d ����%s �ɼ�%d\n",p->num,p->name,p->score);

	
   printf("����������ѧ�� ���� �ɼ�\n");
   scanf("%d %s %d",&num,name,&score);
   InsertNode(head,num,name,score);
   PrintLink(head);

   
   printf("������ɾ����ѧ��\n");
   scanf("%d",&num);
   DeleteNode(head,num);
   PrintLink(head);


		
	

	return 0;
}
