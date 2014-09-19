#pragma once
#define _AFXDLL
#include <string>

using namespace std;

enum Format
{
	CPP,HTML,TXT,NO_FOUND
};

class CmpString
{
protected:
	string CmpStr;
	string fname;

	string OutputInfo;

public:
	float CalcSimilar(const CmpString& other); //����������

	virtual void getCmpStr(string filename)=0;
	string getName(){return fname;};  //����ļ���
	string getCmpStr(){return CmpStr;};//��õ�Ч����

	static string JudgePct(float percent); //����жϽ��

};

class CppWork:public CmpString
{
public:
	void getCmpStr(string filename);
	
};

class TxtWork:public CmpString
{

public:
	void getCmpStr(string filename);
};

class HtmlWork:public CmpString
{
public:
	void getCmpStr(string filename);
};


class CmpStrCreator
{
public:
	CmpString* createCmpString(const string& filename);	
	void CmpRecovery(CmpString* rec); 
};


