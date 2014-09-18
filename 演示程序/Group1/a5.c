#include<stdio.h>
#include<malloc.h>
#define LEN sizeof(struct student)
struct student
{
	int IDnum;
	char name[18];
	float score;
	struct student *next;
};
struct student *CreateLink(void)                              //��������
{
    struct student *head;
    struct student *p1,*p2;
    int n=0;
    p1=p2=(struct student*)malloc(LEN);
    scanf("%ld %s %f",&p1->IDnum,p1->name,&p1->score);
    head=NULL;
    while(p1->IDnum!=0)
	{
		n=n+1;
        if(n==1) head=p1;
        else p2->next=p1;
        p2=p1;
		p1=(struct student*)malloc(LEN);
		scanf("%ld %s %f",&p1->IDnum,p1->name,&p1->score);
	}
	p2->next=NULL;
	return(head);
}
void PrintLink(struct student *head)                              //�������
{
	struct student *p;
	printf("Now,these students' records(IDnumber,name,score) are:\n");
	p=head;
	if(head!=NULL)
		do 
		{
			printf("%ld %s %5.1f\n",p->IDnum,p->name,p->score);
			p=p->next;
		}while(p!=NULL);
}
void SearchId(struct student *head,int num)               //����ĳ��ѧ�ţ�����������Ϣ                   
{
	int flag=0;
	struct student *p;
	p=head;
    while(p!=NULL)
	{
		if(p->IDnum==num)
		{
			printf("%ld %s %5.1f\n",p->IDnum,p->name,p->score);
			flag=1;
			break;
		}
        p=p->next;
	}
	if(flag==0)printf("THIS MESSAGE IS NOT EXIST!\n");
}
void DeleteLink(struct student *head)                       //ɾ������
{
	printf("ALL THE MESSAGE ARE DELETED!\n");
	free(head);
}
void main()
{
	long int search_num;
	struct student stu;
	struct student *head,*p;
	printf("input records:\n");//��������
    head=CreateLink();
	PrintLink(head);//�������
    printf("input the search number:");//����ĳ��ѧ������Ϣ
	scanf("%ld",&search_num);
	SearchId(head,search_num);
	DeleteLink(head);//ɾ������
}