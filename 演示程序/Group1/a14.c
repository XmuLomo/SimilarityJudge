#include<stdio.h>
#include<stdlib.h>
#define LEN sizeof(struct student)
//a)����ѧ�����ݽṹ������ѧ�ţ����ͣ����������ɼ���1�ż��ɣ���
struct student 
{ 
	int num;
	char name[20];
	float score;
	struct student *next;
};
void main()
{
	struct student *creatlink();
	void printlink(struct student *head);
    void searchid(struct student *head,int m);
    struct student *insertnode(struct student *head,struct student *stud);
    struct student *deletenode(struct student *head,int m);
    struct student *sortid(struct student *head);
    void deletelink(struct student *head);
	struct student *head,*stu;
	int m;
    head=creatlink();
	printlink(head);
	printf("input the student id you want\n");
	scanf("%d",&m);
    searchid(head,m);
	printf("\n\nnow it's going to sort it\n\n");
    sortid(head);
	printlink(head);
	printf("then insert a student record\n ");
    stu=(struct student *)malloc(LEN);
    printf("intput the student's id\n");
	scanf("%d",&stu->num);
	printf("input the student's name\n");
	scanf("%s",stu->name);
	printf("input the student's score\n");
	scanf("%f",&stu->score);
    insertnode(head,stu);
    printlink(head);
    printf("now input the student you want to delete\n");
	scanf("%d",&m);
    deletenode(head,m);
    printlink(head);
    deletelink(head);
}
/*b)	��������(CreateLink)��������ѧ�����ݣ�3λ����ÿ����һλ���ݲ���һ�������㡣
�û������ʱ�򣬿ɲ���ѧ�����򣬵��ǲ�������ʱ��Ӧ����ѧ�ŴӴ�С����
���磺���μ������λѧ����ѧ�ŷֱ�Ϊ14,7,29����
��һ�μ���ѧ��Ϊ14��ѧ�����ݣ��ڶ��μ���ѧ��Ϊ7��ѧ�����ݣ�
���ǲ���ʱӦ��ѧ��Ϊ7��ѧ������ѧ��Ϊ14��ѧ��֮ǰ��
�����μ���ѧ��Ϊ29��ѧ�����ݣ�Ӧ�÷������*/
struct student *creatlink()
{
	struct student *head;
	struct student *p1,*p2;
	int n=0;
	p1=p2=(struct student *)malloc(LEN);
	printf("intput the student's id\n");
	scanf("%d",&p1->num);
	printf("input the student's name\n");
	scanf("%s",p1->name);
	printf("input the student's score\n");
	scanf("%f",&p1->score);
	head=NULL;
	while(p1->num!=0)
	{
		n=n+1;
		if(n==1)
			head=p1;
		else
			p2->next=p1;
		p2=p1;
		p1=(struct student *)malloc(LEN);
    	printf("intput the student's id\n");
	    scanf("%d",&p1->num);
	    printf("input the student's name\n");
	    scanf("%s",p1->name);
	    printf("input the student's score\n");
	    scanf("%f",&p1->score);
	}
	p2->next=NULL;
	free(p1);
	return head;
}
//c)	������������(PrintLink)����ӡ����ǰ����ѧ�������ݡ�
void printlink(struct student *head)
{
	struct student *p;
	printf("\nNow,There records are:\n");
	p=head;
	if(head!=NULL)
		do
		{
			printf("%d %s %.2f\n",p->num,p->name,p->score);
			p=p->next;
		}while(p!=NULL);
}
//d)����ѧ�Ų���ĳ��ѧ������(SearchId), ����޴��ˣ�Ӧ�ñ��档
void searchid(struct student *head,int m)
{
	struct student *p;
	int f=1;
	p=head;
	if(head!=NULL)
		do
		{
			if(m==p->num)
			{
			     printf("%d %s %.2f\n",p->num,p->name,p->score);
				 f=0;
				 break;
			}
			p=p->next;
		}while(p!=NULL);
		if(f)
			printf("there isn'n a student have the id of %d\n",m);
}
//h)����ѧ��ѧ�Ŷ������������SortId����ѧ��С��ǰ��ѧ�Ŵ��ں�
struct student *sortid(struct student *head)
{
    struct student *insertnode(struct student *head,struct student *stud);
	struct student *p1,*p2=NULL,*p3,*p4;
	if(head==NULL)
	{
		printf("list null!\n");
		return head;
	}
	p1=head;	
	while(p1!=NULL)
	{
		p4=p2;
	    p2=p1;
	    p1=p1->next;
		if(p1!=NULL)
			if(p2->num>p1->num)
			{
			    p3=p1;
			    p1=p1->next;
			    p2->next=p1;
                p3->next=NULL;
                insertnode(head,p3);
			}
	}
			if(p4->num>p2->num)
			{
			    p3=p2;
                p3->next=NULL;
                insertnode(head,p3);
			}
	return head;
}
//e)����һ���µ�ѧ�����ݣ�InsertNode����Ҫ������λ���ǰ���ѧ���������еġ�
//���룬���ʱ�������ǲ��Ǿʹ������ˣ���������ռ�Ԥ�ȷ����㹻��������һ�����ݣ�
//���������е�����Ҫ��Ӧ���ƶ����������ܴ�
struct student *insertnode(struct student *head,struct student *stud)
{
	struct student *p0,*p1,*p2;
	p1=head;
	p0=stud;
	if(head==NULL)
	{
		head=p0;
		p0->next=NULL;
	}
	else
	{
		while((p0->num>p1->num)&&(p1->next!=NULL))
		{
			p2=p1;
			p1=p1->next;
		}
		if(p0->num<=p1->num)
		{
			if(head==p1)
			{
				head=p0;
				p0->next=p1;
			}
		    else
			    p2->next=p0;
		p0->next=p1;
		}
		else
		{
			p1->next=p0;
			p0->next=NULL;
		}
	}
		return (head);
}
//f)����ѧ��ɾ��һ��ѧ������(DeleteNode)���˺���Ӧ����SearchId����ɾ��ĳ��ѧ����
//�ǵ�Ҫ��free�ͷŸ�ѧ�����ݣ���Ȼ����ڴ�й¶��������ڴ�û�л��գ���
struct student *deletenode(struct student *head,int m)
{
	struct student *p1,*p2;
	if(head==NULL)
	{
		printf("\nlist null!\n");
		return head;
	}
	p1=head;
	while(m!=p1->num&&p1->next!=NULL)
	{
		p2=p1;
		p1=p1->next;
	}
	if(m==p1->num)
	{
		if(p1==head)
			head=p1->next;
		else
			p2->next=p1->next;
		printf("delete:%d\n",m);
	}
	else 
		printf("%d not been found! \n",m);
		return head;
}
//i)	ɾ����������DeleteLink����
void deletelink(struct student *head)
{
	struct student *p1,*p2;
	p1=head;
	while(p1!=NULL)
	{
		p2=p1;
		p1=p1->next;
		free(p2);
	}
	free(p1);
}
	  

		 
	