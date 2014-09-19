#include "CmpString.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string CmpString::JudgePct(float percent)
{
	string result;
	if(percent<=0.88)
	{
		result="������";
	}
	else if(percent<=0.95)
	{
		result="����С��������";
	}
	else if(percent<=1)
	{
		result="�Ƚ�����";
	}
	else if(percent<=1.15)
	{
		result="�ǳ�����";
	}
	else if(percent<1.2)
	{
		result="������ȫ����";
	}
	else 
	{
		result="һģһ��";
	}
	return result;
}

//��������������ػ����� �����ԽС ����ֵԽ�� 
float DoubtPct(float pecent)
{
	if(pecent<=0.01)
	{
		return 1.2;
	}
	if(pecent<=0.05)
	{
		return 1.15;
	}
	if(pecent<=0.1)
	{
		return 1.1;
	}
	if(pecent<=0.15)
	{
		return 1.05;
	}
	if(pecent<=0.2)
	{
		return 1;
	}
	if(pecent<=0.25)
	{
		return 0.95;
	}
	if(pecent<=0.3)
	{
		return 0.9;
	}
	return 0.8;
}

float CmpString::CalcSimilar(const CmpString& other)
{
	string a=this->CmpStr;
	string b=other.CmpStr;
	float distancePct;     //����������
	int line=a.length(),row=b.length();

	vector<vector<int>>data;
	data.resize(line+1);

	cout<<"\n���ڶ�"<<getName()<<" �� "<<other.fname<<"��Ч������б༭���������������"<<endl;

	for(int i=0;i<line+1;i++)
		data[i].resize(row+1);

	for(int i=0;i<line+1;i++)
		data[i][0]=i;
	for(int i=0;i<row+1;i++)
		data[0][i]=i;

	for(int i=1;i<line+1;i++)
	{
		for(int j=1;j<row+1;j++)
		{
			char sa=a[i-1];
			char sb=b[j-1];
			int cost = !(sa==sb);
			data[i][j]=min(data[i-1][j-1]+cost,min(data[i-1][j]+1,data[i][j-1]+1));
		}
	}
	
	float times = data[line][row];
	int distance=a.length()-b.length();
	int sum=a.length()+b.length();
	distance=abs(distance);
	float percent;

	percent=1-((times-distance)/(sum-distance));
	distancePct=(float)distance/sum;

	cout<<"-------"<<"��"<<getName()<<" �� "<<other.fname<<"�ķ�������  -------"<<endl;

//	cout<<"�ַ���a�ĵ�Ч����ṹ����Ϊ ��" <<a.length()<<endl;
//	cout<<"�ַ���b�ĵ�Ч����ṹ����Ϊ ��" <<b.length()<<endl;
//	cout<<"�ַ���a,b�ĵ�Ч����ṹ����֮��Ϊ ��" <<distance<<"  ��Ӧ 100% ��ȫ���"<<endl;
//	cout<<"�ַ���a,b�ĵ�Ч����ṹ����֮��Ϊ ��" <<sum<<"  ��Ӧ0% �������"<<endl; 
//	cout<<"���ַ���a�޸ĵ��ַ���b��Ҫ�Ĳ���:"<<times<<endl;

	cout<<"�༭���������� "<<percent<<endl;
	cout<<"����� "<<distancePct<<endl;

	float pct2=percent*DoubtPct(distancePct);
	cout<<"��ҵ������ "<<percent*DoubtPct(distancePct)<<endl;

	string result;

	result=JudgePct(pct2);
	
	cout<<"���������"<<endl;
	cout<<result<<endl;

	return pct2;
};

//ɾ��cpp��ע�����
void DelCppNotes(string& source)
{
	string NoteMark="//";
	int posBegin;
	int posEnd;

	//��һ�� ɾ������//��ʽ��ע��
	while(posBegin=source.find(NoteMark))
	{
		if(posBegin == string::npos)
		{
			break;
		}
		int posEnd= source.find('\n',posBegin);
		string::iterator end=source.begin();
		string::iterator beg=source.begin();

		while(posEnd--)
			end++;
		while(posBegin--)
			beg++;
		source.erase(beg,end);
	}
	//�ڶ��� ɾ������/* */ ��ʽ��ע��

	string Mark1="/*";
	string Mark2="*/";
	while(posBegin=source.find(Mark1))
	{
		if(posBegin == string::npos)
		{
			break;
		}
		int posEnd= source.find(Mark2,posBegin);
		string::iterator end=source.begin();
		string::iterator beg=source.begin();

		while(posEnd--)
			end++;
		while(posBegin--)
			beg++;
		end+=2;
		source.erase(beg,end);
	}
}

//ɾ��HTML�е�ע�����
void DelHtmlNotes(string& source)
{
	int posBegin;
	int posEnd;

	//ɾ������<!--   --> ��ʽ��ע��

	string Mark1="<!--";
	string Mark2="-->";
	while(posBegin=source.find(Mark1))
	{
		if(posBegin == string::npos)
		{
			break;
		}
		int posEnd= source.find(Mark2,posBegin);
		string::iterator end=source.begin();
		string::iterator beg=source.begin();

		while(posEnd--)
			end++;
		while(posBegin--)
			beg++;
		end+=2;
		source.erase(beg,end);
	}
}


//ɾ�����лس��ո���
void DelBlank(string& source)
{

		bool flag =false;

		char delSet[4]={'\n',' ','\a','\t'}; //Ҫɾ�����ַ�
		int pos[4];

		for(int i=0;i<4;i++)
		{
			while(true)
			{
				pos[i]=source.find(delSet[i]);
				if(pos[i]==string::npos)break;
				else{source.erase(pos[i],1);}
			}
		}

}

void TxtWork::getCmpStr(string filename)
{
	fstream file;
	string tmp;
	file.open(filename,ios::in);
	fname=filename;
	if(!file)
	{
		cerr<<" can not open "<<filename<<endl;
		return ;

	}

	while(true)
	{
		file>>tmp;
		CmpStr= CmpStr + tmp;
		if(file.eof())
			break;
	}
}

void CppWork::getCmpStr(string filename)
{
	fstream file;
	file.open(filename,ios::in);
	fname=filename;
	if(!file)
	{
		cerr<<filename<<" can not open "<<filename<<endl;
		return;
	}

	while(true)
	{
		char ch=file.get() ;
		CmpStr= CmpStr + ch;
		if(file.eof())
			break;
	}

	DelCppNotes(CmpStr);  //ɾ������ע��
	
	DelBlank(CmpStr);     //ɾ�����пհ׸�

	file.close();
}

void HtmlWork::getCmpStr(string filename)
{
	fstream file;
	file.open(filename,ios::in);
	fname=filename;
	if(!file)
	{
		cerr<<" can not open "<<filename<<endl;
		return ;
	}

	while(true)
	{
		char ch=file.get() ;

		CmpStr= CmpStr + ch;

		if(file.eof())
			break;
	}

	DelHtmlNotes(CmpStr); 
	
	DelBlank(CmpStr);   

	file.close();
}


//�����ļ����Ʋ��ʽ����
Format JudgeFormat(const string& filename)
{
	if(string::npos!=filename.find(".cpp")||string::npos!=filename.find(".c")){return CPP;}
	if(string::npos!=filename.find(".txt")){return TXT;}
	if(string::npos!=filename.find(".html") || string::npos!=filename.find(".htm")){return HTML;}
	return NO_FOUND;
}

void CmpStrCreator::CmpRecovery(CmpString* rec)
{
	delete(rec);
}


CmpString* CmpStrCreator::createCmpString(const string& filename)
{
	Format fmt=JudgeFormat(filename);
		
	CmpString *ret=NULL;
	
		switch (fmt)
		{
		case CPP:
			ret=new(CppWork);   //�򵥹���ģʽ �� �����ļ�����������ʵ�����ĸ���
		break;
		case TXT:
			ret=new(TxtWork);
		break;
		case HTML:
			ret=new(HtmlWork);
		break;
		case NO_FOUND:
			cerr<<filename<<" the format can not be found"<<endl;
			return NULL;
		default:	
		break;
		}


	ret->getCmpStr(filename);

	return ret;
}
