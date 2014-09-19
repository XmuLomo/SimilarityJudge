#pragma once
#define _AFXDLL

#include "CmpString.h"
#include <vector>

#include <afx.h>

using namespace std;

class ReportMaker
{
private:
	vector<CmpString *> set;
	vector<vector<float>> pct;
	int sampleSize;

	string report;

	/*���������ʵı��*/
	string createPctTable();
	/*���ɻ����б���*/
	string createDoubtList();
	
	/*�ҳ�set�е����н��ΪlevelString����*/
	string findLevel(string levelString);

public:
	ReportMaker(vector<CmpString *>& set,vector<vector<float>>& pct);
	
	/*���ɽ������*/
	bool createReport();
	/*���ؽ������*/
	string getReport();

};