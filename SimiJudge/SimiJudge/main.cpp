#define _AFXDLL
#include "CmpString.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <afx.h>

using namespace std;


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

/*�������Ա��棬���ұ�����ļ�
* @param set ��ҵ����
* @param pct ������
*/
void createReport(vector<CmpString *>& set,vector<vector<float>>& pct)
{
	string OutputInfo;
	
	OutputInfo.append("\n------------   ������ͳ�ƽ��(�ܱ�)   ------------\n");

	//cout<<"\n------------   ������ͳ�ƽ��   ------------"<<endl;
	for(int i=0;i<set.size();i++)
	{
		for(int j=0;j<set.size();j++)
		{
			CString tmp;
			
			if(pct[i][j]!=0)
				tmp.Format("%.2f ",pct[i][j]);
			else
			tmp.Format("     ");
			OutputInfo.append(tmp);
		}
		OutputInfo.append("\n");
	}

	OutputInfo.append("---------    ������ҵ�����뻳������   ---------\n");
	//cout<<"---------    ������ҵ�����뻳������   ---------"<<endl;
	for(int i=0;i<set.size();i++)
	{
		for(int j=0;j<set.size();j++)
		{
			if(pct[i][j]>=0.9)
			{
				CString tmp;
				float percent=pct[i][j];
				string work1=set[i]->getName();
				string work2=set[j]->getName();
				float simipct=pct[i][j];
				string answer=JudgePct(percent);
				tmp.Format("%s �� %s �����ƶ�Ϊ %f �жϽ��Ϊ %s\n",work1.c_str(),work2.c_str(),simipct,answer.c_str());
	//			cout<<set[i]->getName()<<" �� "<<set[j]->getName()<<" ���ƶ� "<<pct[i][j]<<"  "<<JudgePct(percent)<<endl;
				OutputInfo.append(tmp);
			}
		}
	}
	cout<<OutputInfo<<endl;
	ToFile(OutputInfo);
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
	
	for(int i=0;i<allWorks.size();i++)
	{
		for(int j=i+1;j<allWorks.size();j++)
		{
			float percent = allWorks[i]->CalcSimilar(*(allWorks[j]));
			pct[i][j]=percent;
		}
	}

	createReport(allWorks,pct); // ���������������ļ�

	//��󽻸��������մ����Ķ���
	for(int i=0;i<allWorks.size();i++)
	fact.CmpRecovery(allWorks[i]);

	system("pause");

	return 0;
}
