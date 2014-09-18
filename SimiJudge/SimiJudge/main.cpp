#include "CmpString.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int readFile(vector<CmpString *>& set)
{
	CmpStrCreator factory;
	fstream file;
	file.open(("datalist.txt"),ios::in);


	if(!file)
	{
		cerr<<"datalist.txt not found"<<endl;
	}
	string fn;

	while(file>>fn)
	{
		CmpString *add;
		add=factory.createCmpString(fn);  //���ļ�����������ʵ�����������𷵻�ʵ�����õ��ࡣ
		if(!add)
		{
			continue;
		}
		set.push_back(add);
	}
	return set.size();
}

int main()
{
	CmpStrCreator fact;
	vector<CmpString *> set;
	
	cout<<"---------  ��ҵ���ƶȷ�������  ---------"<<endl;
	cout<<"1. ���ڶ�ȡ����������"<<endl;

	cout<<"��ȡ���� "<<readFile(set)<<"���ļ�"<<endl;

	float maxpercent=-100;
	int posi,posj;
	vector<vector<float>> pct;

	pct.resize(set.size());
	for(int i=0;i<set.size();i++)
		pct[i].resize(set.size());

	cout<<"2. ��ʼ�����С�����������"<<endl;
	
	for(int i=0;i<set.size();i++)
	{
		for(int j=i+1;j<set.size();j++)
		{
			float percent = set[i]->CalcSimilar(*(set[j]));
			pct[i][j]=percent;
		}
	}

	cout<<"\n------------   ������ͳ�ƽ��   ------------"<<endl;
	for(int i=0;i<set.size();i++)
	{
		for(int j=0;j<set.size();j++)
		{
			if(pct[i][j]!=0)
			printf("%.2f ",pct[i][j]);
			else
			printf("     ");
		}
		printf("\n");
	}

	cout<<"---------    ������ҵ�����뻳������   ---------"<<endl;
	for(int i=0;i<set.size();i++)
		for(int j=0;j<set.size();j++)
		{
			if(pct[i][j]>=0.9)
			{
				float percent=pct[i][j];
				cout<<set[i]->getName()<<" �� "<<set[j]->getName()<<" ���ƶ� "<<pct[i][j]<<"  "<<JudgePct(percent)<<endl;
			}
		}
	
		//��󽻸��������մ����Ķ���
		for(int i=0;i<set.size();i++)
		fact.CmpRecovery(set[i]);

		system("pause");
	return 0;
}
