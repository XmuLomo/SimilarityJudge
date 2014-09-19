#include "ReportMaker.h"

ReportMaker::ReportMaker(vector<CmpString *>& set,vector<vector<float>>& pct)
{
	this->set = set;
	this->pct = pct;
	sampleSize = set.size();
}

string ReportMaker::findLevel(string levelString)
{
	string ret="";

	for(int i=0;i<sampleSize;i++)
	{
		for(int j=0;j<sampleSize;j++)
		{
			if(CmpString::JudgePct(pct[i][j]) ==levelString)
			{
				CString tmp;
				string work1 = set[i]->getName();
				string work2 = set[j]->getName();
				tmp.Format("%s �� %s �����ƶ�Ϊ %f \n",work1.c_str(),work2.c_str(),pct[i][j]);
				ret.append(tmp);
			}
		}
	}
	return ret;
}

string ReportMaker::createPctTable()
{
	CString tmp ;
	string ret;
	for(int i=0;i<set.size();i++)
	{
		for(int j=0;j<set.size();j++)
		{
			CString tmp;
			
			if(pct[i][j]!=0)
				tmp.Format("%.2f ",pct[i][j]);
			else
			tmp.Format("     ");
			ret.append(tmp);
		}
		ret.append("\n");
	}
	return ret;
}

string ReportMaker::createDoubtList()
{
	string ret="";
	string tmp;
	
	tmp = findLevel("һģһ��");
	if(tmp!="")
	{
		ret.append(" # һģһ�� # \n (pct = 1.2)\n");
		ret.append("     "+tmp);
	}

	tmp = findLevel("������ȫ����");
	if(tmp!="")
	{
		ret.append(" # ������ȫ���� # \n (1.2>= pct >= 1.15)\n");
		ret.append("     "+tmp);
	}

	tmp = findLevel("�ǳ�����");
	if(tmp!="")
	{
		ret.append(" # �ǳ����� # \n (1.15>= pct >= 1.0 )\n");
		ret.append("     "+tmp);
	}

	tmp = findLevel("�Ƚ�����");
	if(tmp!="")
	{
		ret.append(" # �Ƚ����� # \n (1.0>= pct >= 0.95 ) \n");
		ret.append("     "+tmp);
	}

	tmp = findLevel("����С��������");
	if(tmp!="")
	{
		ret.append(" # ����С�������� # \n (0.95>= pct >= 0.88) \n");
		ret.append("     "+tmp);
	}

	return ret;
}

bool ReportMaker::createReport()
{
	report.clear();
	
	report.append("\n------------   ������ͳ�ƽ��(�ܱ�)   ------------\n");
	report.append(createPctTable()); 
	
	report.append("---------    ������ҵ�����뻳������   ---------\n\n");
	report.append(createDoubtList());

	return true;
}

string ReportMaker::getReport()
{
	return report;
}