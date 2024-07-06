#pragma once
#include <iostream>
using namespace std;

/*
显示 与用户沟通的菜单界面
*/

class CMenu
{
public:
	CMenu();
	~CMenu();
	//显示菜单
	void ShowMenu();
	//显示增删改查二级菜单
	void ShowInsertMenu();
	void ShowFindMenu();
	void ShowDelMenu();
	void ShowUpdateMenu();
	void ExitMenu();
};

