#define _AFXDLL

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <afx.h>

#include "CmpString.h"
#include "ReportMaker.h"

using namespace std;

/*��ȡ��ǰĿ¼�µ������ļ�*/
int readFile(vector<CmpString *>& set)
{
	CmpStrCreator factory;
    CFileFind finder;

    BOOL bWorking = finder.FindFile(_T("*.*"));
  
	while(bWorking)
	{
		string fn;
		bWorking = finder.FindNextFile();
		fn=(LPCTSTR)finder.GetFileName();
		if(fn=="."||fn=="..")
		{
			continue;
		}
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

void ToFile(string report)
{
	fstream file("report.txt",ios::out);

	if(!file)
	{
		cerr<<"can not open file for writting"<<endl;
	}
	file<<report;

	file.close();
}

void createReport(vector<CmpString *>& set,vector<vector<float>>& pct)
{
	string OutputInfo;
	ReportMaker mk(set,pct);
	if(mk.createReport())
	{
		OutputInfo=mk.getReport();
	}
	cout<<OutputInfo<<endl;
	ToFile(OutputInfo);
}

//�ж������� ���pct��
void JudegeSimilarity(vector<CmpString *>& allWorks,vector<vector<float>>& pct)
{
	for(int i=0;i<allWorks.size();i++)
	{
		for(int j=i+1;j<allWorks.size();j++)
		{
			float percent = allWorks[i]->CalcSimilar(*(allWorks[j]));
			pct[i][j]=percent;
		}
	}
}

int main()
{
	CmpStrCreator fact;
	vector<CmpString *> allWorks;  //ÿ��������Ӧһ��CmpString �� ��������е�����

	
	cout<<"---------  ��ҵ���ƶȷ�������  ---------"<<endl;
	cout<<"1. ���ڶ�ȡ����������"<<endl;
	cout<<"��ȡ���� "<<readFile(allWorks)<<"���ļ�"<<endl;

	float maxpercent=-100;
	int posi,posj;

	vector<vector<float>> pct; //��Ž��

	pct.resize(allWorks.size());
	for(int i=0;i<allWorks.size();i++)
		pct[i].resize(allWorks.size());

	cout<<"2. ��ʼ�����С�����������"<<endl;
	
	JudegeSimilarity(allWorks,pct); //��������֮��������ƶ� �浽pct��

	createReport(allWorks,pct); // ���������������ļ�

	//��󽻸��������մ����Ķ���
	for(int i=0;i<allWorks.size();i++)
	fact.CmpRecovery(allWorks[i]);

	system("pause");

	return 0;
}
