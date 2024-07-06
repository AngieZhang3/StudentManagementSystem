#include "CMenuHandler.h"
#include <stdlib.h>
CMenuHandler::CMenuHandler()
{
}

CMenuHandler::~CMenuHandler()
{
}

void CMenuHandler::SelectMain()
{
	system("cls");
	char option = '0';
	CMenu menu;
	bool bflag = true;
	while (bflag)
	{
		menu.ShowMenu();
		cout << "请选择想要进行的操作: " << endl;
		cin >> option;
		switch (option)
		{
		case '1':
			menu.ExitMenu();
			if (!(m_cst.IsEmpty())) m_cst.MidLoopWriteFile("ID_Name.bin");
			if (!(m_cct.IsEmpty())) m_cct.MidLoopWriteFile("ID_Course.bin");
			if (!(m_crt.IsEmpty())) m_crt.MidLoopWriteFile("GradeList.bin");
			if (!(m_crit.IsEmpty())) m_crit.MidLoopWriteFile("GradeList.bin");

			break;
		case '2':
			SelectInsert();
			bflag = false;
			break;
		case '3':
			SelectFind();
			bflag = false;
			break;
		case '4':
			SelectDel();
			bflag = false;
			break;
		case '5':
			SelectUpdate();
			bflag = false;
			break;
		default:
			cout << "输入无效，请重新输入" << endl;
			system("cls");
			break;
		}
	}
	return;
}

void CMenuHandler::SelectInsert()
{
	system("cls");
	char option = '0';
	CMenu menu;
	bool bflag = true;
	while (bflag)
	{
		menu.ShowInsertMenu();
		cout << "请选择添加数据的方式: " << endl;
		cin >> option;
		switch (option)
		{
		case '1':
			//插入学生
			InsertNewStudent();
			bflag = false;
			break;
		case '2':
			//插入新课程
			InsertNewCourse();
			bflag = false;
			break;
		case '3':
			//插入选课记录
			InsertNewRecord();
			bflag = false;
			break;
		case '4':
			SelectMain();
			break;
		default:
			cout << "输入无效，请重新输入" << endl;
			system("cls");
			break;
		}
	}
	return;
}

void CMenuHandler::SelectFind()
{
	system("cls");
	char option = '0';
	CMenu menu;
	bool bflag = true;
	while (bflag)
	{
		menu.ShowFindMenu();
		cout << "请选择查询方式: " << endl;
		cin >> option;
		switch (option)
		{
		case '1':
			//通过学生ID查询学生姓名
			FindStuNameById();
			bflag = false;
			break;
		case '2':
			//通过学生姓名查询学生ID
			FindStuIdByName();
			bflag = false;
			break;
		case '3':
			//通过课程ID查询课程名
			FindCourseById();
			bflag = false;
			break;
		case '4':
			//通过课程名查询课程ID
			FindCourseIdByName();
			bflag = false;
			break;
		case '5':
			//通过课程ID查询选修了该课程的学生以及成绩
			FindRecordByCourseId();
			bflag = false;
			break;
		case '6':
			//通过课程ID查询课程名
			FindRecordByStuId();
			bflag = false;
			break;
		case '7':
			FindRecordByCName();
			bflag = false;
			break;
		case '8':
			SelectMain();
			break;
		default:
			cout << "输入无效，请重新输入" << endl;
			system("cls");
			break;
		}
	}
	return;
}

void CMenuHandler::SelectDel()
{
	system("cls");
	char option = '0';
	CMenu menu;
	bool bflag = true;
	while (bflag)
	{
		menu.ShowDelMenu();
		cout << "请选删除数据的方式: " << endl;
		cin >> option;
		switch (option)
		{
		case '1':
			DeleteStudent();
			bflag = false;
			break;
		case '2':
			//删除课程(ID)
			DeleteCourse();
			bflag = false;
			break;
		case '3':
			//删除选课记录(学生ID, 课程ID)
			DeleteRecord();
			bflag = false;
			break;
		case '4':
			SelectMain();
			break;
		default:
			cout << "输入无效，请重新输入" << endl;
			system("cls");
			break;
		}
	}
	return;
}

void CMenuHandler::SelectUpdate()
{
	system("cls");
	char option = '0';
	CMenu menu;
	bool bflag = true;
	while (bflag)
	{
		menu.ShowUpdateMenu();
		cout << "请选择更改数据的方式: " << endl;
		cin >> option;
		switch (option)
		{
		case '1':
			//更改学生(ID)
			EditStudent();
			bflag = false;
			break;
		case '2':
			//更改课程(ID)
			EditCourse();
			bflag = false;
			break;
		case '3':
			//更改选课记录(学生ID, 课程ID)
			EditRecord();
			bflag = false;
			break;
		case'4':
			SelectMain();
			break;
		default:
			cout << "输入无效，请重新输入" << endl;
			system("cls");
			break;
		}
	}
	return;

}


void CMenuHandler::InsertNewStudent()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择新增学生(ID, 名字)" << endl;

	while (bflag)
	{
		char szId[SID_SIZE];
		char szName[SNAME_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入学生姓名 (或输入 'q' 取消)：" << endl;
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > SNAME_SIZE - 1)
			{
				cout << "姓名长度有误，请重新输入： " << endl;
				attempts++;
				continue;
			}

			if (m_cst.IsEmpty())
			{
				m_cst.createStuIdTree("ID_Name.bin", m_cst);
			}

			bool bRet = m_cst.Insert(szId, szName);

			if (bRet)
			{
				cout << "新增学生成功!" << endl;
				m_cst.AddLine(szId, szName, "ID_Name.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "新增学生失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectInsert();
}

void CMenuHandler::InsertNewCourse()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择新增课程(ID, 名字)" << endl;

	while (bflag)
	{
		char szId[CID_SIZE];
		char szName[COU_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入6位课程ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入课程名 (或输入 'q' 取消)：";
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > COU_SIZE - 1)
			{
				cout << "课名长度有误，请重新输入： ";
				attempts++;
				continue;
			}


			if (m_cct.IsEmpty())
			{
				m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			}
			//m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			bool bRet = m_cct.Insert(szId, szName);

			if (bRet)
			{
				cout << "新增课程成功!" << endl;
				m_cct.AddLine(szId, szName, "ID_Course.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "新增课程失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectInsert();
}

void CMenuHandler::InsertNewRecord()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择新增选课记录(学生ID, 课程ID, 分数)" << endl;

	while (bflag)
	{
		char szSId[SID_SIZE];
		char szCId[CID_SIZE];
		int grade;

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szSId;
			if (strcmp(szSId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szSId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入6位数课程ID (或输入 'q' 取消)：";
			cin >> szCId;
			if (strcmp(szCId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szCId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入分数 (或输入 -1 取消)：";
			cin >> grade;
			if (grade == -1)
			{
				bflag = false;
				break;
			}

			if (grade > 1000 || grade <= -2)
			{
				cout << "分数输入错误，请重新输入：" << endl;
				attempts++;
				continue;
			}



			if (!m_crt.IsEmpty())
			{
				m_crt.Clear();
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}
			else
			{
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}
			bool bRet = m_crt.InsertBySId(szSId, szCId, grade);

			if (bRet)
			{
				cout << "新增选课记录成功!" << endl;
				m_crt.AddLine(szSId, szCId, grade, "GradeList.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "新增选课记录失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");

	system("cls");
	SelectInsert();
}

void CMenuHandler::FindStuNameById()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择通过学生ID查询学生姓名" << endl;

	while (bflag)
	{
		char szId[SID_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			if (m_cst.IsEmpty())
			{
				m_cst.createStuIdTree("ID_Name.bin", m_cst);
			}
			//m_cst.createStuIdTree("ID_Name.bin", m_cst);
			bool bRet = m_cst.FindStuName(szId);

			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectFind();

}

void CMenuHandler::FindStuIdByName()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择通过学生姓名查询学生ID" << endl;

	while (bflag)
	{
		char szName[SNAME_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入学生姓名 (或输入 'q' 取消)：" << endl;
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > SNAME_SIZE - 1)
			{
				cout << "姓名长度有误，请重新输入： " << endl;
				attempts++;
				continue;
			}

			if (!m_cstName.IsEmpty())
			{
				m_cstName.Clear();
				m_cstName.createStuNameTree("ID_Name.bin", m_cstName);
			}
			else
			{
				m_cstName.createStuNameTree("ID_Name.bin", m_cstName);
			}
			/*	m_cstName.Clear();
				m_cstName.createStuNameTree("ID_Name.bin", m_cstName);*/
			bool bRet = m_cstName.FindStuId(szName);

			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectFind();

}

void CMenuHandler::FindCourseById()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择通过课程ID查询课程名" << endl;

	while (bflag)
	{
		char szId[CID_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入6位课程ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			if (m_cct.IsEmpty())
			{
				m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			}
			//m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			bool bRet = m_cct.FindCouseName(szId);

			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectFind();
}

void CMenuHandler::FindCourseIdByName()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择通过课程名查询课程ID" << endl;

	while (bflag)
	{
		char szName[COU_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{

			cout << "请输入课程名 (或输入 'q' 取消)：";
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > COU_SIZE - 1)
			{
				cout << "课名长度有误，请重新输入： ";
				attempts++;
				continue;
			}


			if (!m_cctName.IsEmpty())
			{
				m_cctName.Clear();
				m_cctName.CreateCourseNameTree("ID_Course.bin", m_cctName);
			}
			else
			{
				m_cctName.CreateCourseNameTree("ID_Course.bin", m_cctName);
			}



			bool bRet = m_cctName.FindCourseId(szName);

			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectFind();

}

void CMenuHandler::FindRecordByCourseId()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择通过课程ID查询选修了该课程的学生以及成绩" << endl;

	while (bflag)
	{
		char szId[CID_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入6位课程ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			if (!m_crit.IsEmpty())
			{
				m_crit.Clear();
				m_crit.CreateRdTreeByCId("GradeList.bin", m_crit);
			}
			else
			{
				m_crit.CreateRdTreeByCId("GradeList.bin", m_crit);
			}


			bool bRet = m_crit.FindStudent(szId);

			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectFind();
}

void CMenuHandler::FindRecordByStuId()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择通过学生ID查询该学生选修的课程信息" << endl;

	while (bflag)
	{
		char szId[SID_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			if (!m_crt.IsEmpty())
			{
				m_crt.Clear();
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}
			else
			{
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}

			bool bRet = m_crt.FindCourse(szId);

			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectFind();
}

void CMenuHandler::FindRecordByCName()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "通过课程名查询选修了该课程的学生以及成绩 " << endl;

	while (bflag)
	{
		char szName[COU_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{

			cout << "请输入课程名 (或输入 'q' 取消)：";
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > COU_SIZE - 1)
			{
				cout << "课名长度有误，请重新输入： ";
				attempts++;
				continue;
			}

			if (!m_cctName.IsEmpty())
			{
				m_cctName.Clear();
				m_cctName.CreateCourseNameTree("ID_Course.bin", m_cctName);
			}
			else
			{
				m_cctName.CreateCourseNameTree("ID_Course.bin", m_cctName);
			}
			if (!m_crit.IsEmpty())
			{
				m_crit.Clear();
				m_crit.CreateRdTreeByCId("GradeList.bin", m_crit);
			}
			else
			{
				m_crit.CreateRdTreeByCId("GradeList.bin", m_crit);
			}
			CVector<const char*> vct; 
			m_cctName.ReturnCId(szName,vct);
			bool bRet = false;

			for (int i = 0; i < vct.Size(); ++i)
			{
				if (m_crit.FindStudent(vct[i]))
				{
					bRet = true;
				}
			}
			if (bRet)
			{
				cout << "查询成功!" << endl;
				bflag = false;
				break;
			}
			else
			{
				cout << "查询失败!" << endl;
				attempts++;
			}


			if (attempts >= maxAttempts)
			{
				cout << "已达到最大尝试次数，操作取消。" << endl;
				bflag = false;
			}
		}


	}
	system("pause");
	system("cls");
	SelectFind();
}

void CMenuHandler::DeleteStudent()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择删除学生(ID, 名字)" << endl;

	while (bflag)
	{
		char szId[SID_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			if (m_cst.IsEmpty())
			{
				m_cst.createStuIdTree("ID_Name.bin", m_cst);
			}
			//	m_cst.createStuIdTree("ID_Name.bin", m_cst);
			if (m_crt.IsEmpty())
			{
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}
			//	m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			bool bRet1 = m_cst.Delete(szId);
			bool bRet2 = m_crt.DeleteBySID(szId);

			if (bRet1 && bRet2)
			{
				cout << "删除学生成功!" << endl;
				m_cst.MidLoopWriteFile("ID_Name.bin");
				m_crt.MidLoopWriteFile("GradeList.bin");
				bflag = false;
				break;
			}
			else if (!bRet2 || !bRet1)
			{
				cout << "删除失败!" << endl;
				attempts++;
			}

		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectDel();
}

void CMenuHandler::DeleteCourse()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择删除课程(ID, 名字)" << endl;

	while (bflag)
	{
		char szId[CID_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入6位课程ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			if (m_cct.IsEmpty())
			{
				m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			}
			//m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			if (m_crit.IsEmpty())
			{
				m_crit.CreateRdTreeByCId("GradeList.bin", m_crit);
			}
			//m_crit.CreateRdTreeByCId("GradeList.bin", m_crit);
			bool bRet1 = m_cct.Delete(szId);
			bool bRet2 = m_crit.DeleteByCId(szId);

			if (bRet1 && bRet2)
			{
				cout << "删除课程成功!" << endl;
				m_cct.MidLoopWriteFile("ID_Course.bin");
				m_crit.MidLoopWriteFile("GradeList.bin");
				bflag = false;
				break;
			}
			else if (!bRet1)
			{
				cout << "删除课程表失败!" << endl;
				attempts++;
			}
			else if (!bRet2)
			{
				cout << "删除选课记录失败";
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}
	system("pause");
	system("cls");
	SelectDel();
}

void CMenuHandler::DeleteRecord()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择删除选课记录(学生ID, 课程ID)" << endl;

	while (bflag)
	{
		char szSId[SID_SIZE];
		char szCId[CID_SIZE];
		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szSId;
			if (strcmp(szSId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szSId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入6位数课程ID (或输入 'q' 取消)：";
			cin >> szCId;
			if (strcmp(szCId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szCId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			if (!m_crt.IsEmpty())
			{
				m_crt.Clear();
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}
			else
			{
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}

			bool bRet = m_crt.DeleteRecord(szSId, szCId);

			if (bRet)
			{
				cout << "删除选课记录成功!" << endl;
				m_crt.MidLoopWriteFile("GradeList.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "删除选课记录失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");

	system("cls");
	SelectDel();
}

void CMenuHandler::EditStudent()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择更改学生姓名" << endl;

	while (bflag)
	{
		char szId[SID_SIZE];
		char szName[SNAME_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入学生姓名 (或输入 'q' 取消)：";
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > SNAME_SIZE - 1)
			{
				cout << "姓名长度有误，请重新输入： ";
				attempts++;
				continue;
			}

			if (m_cst.IsEmpty())
			{
				m_cst.createStuIdTree("ID_Name.bin", m_cst);
			}
			//	m_cst.createStuIdTree("ID_Name.bin", m_cst);
			bool bRet = m_cst.Update(szId, szName);

			if (bRet)
			{
				cout << "更改学生姓名成功!" << endl;
				m_cst.MidLoopWriteFile("ID_Name.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "更改学生姓名失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectUpdate();
}

void CMenuHandler::EditCourse()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择更改课程名称" << endl;

	while (bflag)
	{
		char szId[CID_SIZE];
		char szName[COU_SIZE];

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入6位课程ID (或输入 'q' 取消)：" << endl;
			cin >> szId;
			if (strcmp(szId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入课程名 (或输入 'q' 取消)：";
			cin >> szName;
			if (strcmp(szName, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szName) == 0 || strlen(szName) > COU_SIZE - 1)
			{
				cout << "课名长度有误，请重新输入： ";
				attempts++;
				continue;
			}


			if (m_cct.IsEmpty())
			{
				m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			}
			//		m_cct.CreateCourseIdTree("ID_Course.bin", m_cct);
			bool bRet = m_cct.Update(szId, szName);

			if (bRet)
			{
				cout << "更改课程名称成功!" << endl;
				m_cct.MidLoopWriteFile("ID_Course.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "更改课程名称失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");
	system("cls");
	SelectUpdate();
}

void CMenuHandler::EditRecord()
{
	const int maxAttempts = 3; // 最大尝试次数
	bool bflag = true;

	cout << "您已选择更改选课分数" << endl;

	while (bflag)
	{
		char szSId[SID_SIZE];
		char szCId[CID_SIZE];
		int grade;

		int attempts = 0;
		while (attempts < maxAttempts)
		{
			cout << "请输入8位数学生ID (或输入 'q' 取消)：" << endl;
			cin >> szSId;
			if (strcmp(szSId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szSId) != SID_LEN)
			{
				cout << "学生ID格式错误！请输入8位数学生ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入6位数课程ID (或输入 'q' 取消)：";
			cin >> szCId;
			if (strcmp(szCId, "q") == 0)
			{
				bflag = false;
				break;
			}

			if (strlen(szCId) != CID_LEN)
			{
				cout << "课程ID格式错误！请输入6位数课程ID：" << endl;
				attempts++;
				continue;
			}

			cout << "请输入分数 (或输入 -1 取消)：";
			cin >> grade;
			if (grade == -1)
			{
				bflag = false;
				break;
			}

			if (grade > 1000 || grade <= -2)
			{
				cout << "分数输入错误，请重新输入：" << endl;
				attempts++;
				continue;
			}

			if (!m_crt.IsEmpty())
			{
				m_crt.Clear();
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}
			else
			{
				m_crt.CreateRdTreeBySId("GradeList.bin", m_crt);
			}

			bool bRet = m_crt.Update(szSId, szCId, grade);

			if (bRet)
			{
				cout << "更改选课分数成功!" << endl;
				m_crt.MidLoopWriteFile("GradeList.bin");
				bflag = false;
				break;
			}
			else
			{
				cout << "新增选课分数失败!" << endl;
				attempts++;
			}
		}

		if (attempts >= maxAttempts)
		{
			cout << "已达到最大尝试次数，操作取消。" << endl;
			bflag = false;
		}
	}

	system("pause");

	system("cls");
	SelectUpdate();
}
