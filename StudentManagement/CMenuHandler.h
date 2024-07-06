#pragma once
#include "CMenu.h"
#include "CStuTree.h"
#include "CCourseTree.h"
#include "CCourseTree.h"
#include "CRecordTree.h"
#include "FileHandler.h"
#include "CVector.h"

/*处理和菜单有关的操作*/
class CMenuHandler
{
public:
	CMenuHandler();
	~CMenuHandler();
	
	//选择主菜单选项
	void SelectMain();
	//选择插入菜单选项
	void SelectInsert();
	//选择查询菜单选项
	void SelectFind();
	//选择删除菜单选项
	void SelectDel();
	//选择更改菜单选项
	void SelectUpdate();

	//新增菜单相关函数
	void InsertNewStudent();
	void InsertNewCourse();
	void InsertNewRecord();

	//查询菜单相关函数
	void FindStuNameById(); //通过学生ID查询学生姓名 
	void FindStuIdByName();  //通过学生姓名查询学生ID
	void FindCourseById(); //通过课程ID查询课程名
	void FindCourseIdByName(); //通过课程名查询课程ID
	void FindRecordByCourseId();  //通过课程ID查询选修了该课程的学生以及成绩
	void FindRecordByStuId(); //通过学生ID查询该学生选修的课程信息
	void FindRecordByCName(); //通过课程名查询该课程的学生以及成绩

	//删除菜单相关函数
	void DeleteStudent(); //删除学生(ID) 
	void DeleteCourse(); // 删除课程(ID)
	void DeleteRecord(); //删除选课记录(学生ID, 课程ID)

	//更改菜单相关函数
	void EditStudent(); //更改学生(ID) 
	void EditCourse(); // 更改课程(ID)
	void EditRecord(); // 更改选课记录(学生ID, 课程ID)

private:
	CStuTree m_cst;
	CStuTree m_cstName;
	CCourseTree m_cct;
	CCourseTree m_cctName;
	CRecordTree m_crt;
	CRecordTree m_crit;

};

