#pragma once
#include <iostream>
using namespace std;

/*
��ʾ ���û���ͨ�Ĳ˵�����
*/

class CMenu
{
public:
	CMenu();
	~CMenu();
	//��ʾ�˵�
	void ShowMenu();
	//��ʾ��ɾ�Ĳ�����˵�
	void ShowInsertMenu();
	void ShowFindMenu();
	void ShowDelMenu();
	void ShowUpdateMenu();
	void ExitMenu();
};

