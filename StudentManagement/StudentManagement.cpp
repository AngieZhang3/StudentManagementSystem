// StudentManagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CMenu.h"
#include "CMenuHandler.h"
#include <stdio.h>
#include "FileHandler.h"
#include "CStuTree.h"
#include "CCourseTree.h"
#include "CRecordTree.h"
using namespace std;

int main()
{
#if 0
	//FileHandler fh;
		//fh.CreateCourseList("CourseList.txt", "ID_Course.bin", 1000);
		//FileHandler fh1; 
		//fh1.CreateStuList("nameList.txt", "ID_Name.bin", 100000);
		//FileHandler fh2;
	 //   fh2.CreateRecord("ID_Name.bin", "ID_Course.bin", "GradeList.bin");
		//CRecordCIdTree tree6;
		//tree6.CreateRdTreeByCId("GradeList.bin", tree6);

		//tree6.FindStudent("000100");
		//tree6.FindStudent("010100");

		//tree6.FindStudent("000001");
		//tree6.FindStudent("001000");
		////tree6.MidLoopPrint();
		//tree6.MidLoopWriteFile("UpdatedGradeByCourse");

		//CRecordTree tree5;
		//tree5.CreateRdTreeBySId("GradeList.bin", tree5);
		//tree5.InsertBySId("100020", "000100", 85);
		//tree5.InsertBySId("100030", "000200", 95);
		//tree5.InsertBySId("100020", "000300", 70);
		//tree5.InsertBySId("065565", "001000", 85);
		//tree5.InsertBySId("000001", "000002", 85);
		//tree5.DeleteRecord("000001", "000005");
		//tree5.DeleteRecord("000003", "000015");
		//tree5.DeleteRecord("000003", "000025");
		//tree5.DeleteRecord("000001", "000100");
		//tree5.FindCourse("001000");
		//tree5.FindCourse("100020");
		//tree5.FindCourse("065565");
		//tree5.FindCourse("000001");
		//tree5.FindCourse("000003");
		//tree5.Update("100000", "000999", "100001", "000010", 50);
		//tree5.Update("000025", "001000", "100007", "001000", 98);
		//tree5.FindCourse("100000");
		//tree5.FindCourse("000025");
		////tree5.MidLoopPrint();
		//tree5.MidLoopWriteFile("updatedGrade.bin");
		//CCourseTree tree3;
		//tree3.CreateCourseNameTree("ID_Course.bin", tree3);
		//tree3.FindCourseId("欧盟经济");
		//tree3.FindCourseId("中国当代文学");
		//tree3.FindCourseId("遗传学实验");
		//tree3.FindCourseId("投资银行学");
		//CCourseTree tree2;
		//tree2.CreateCourseIdTree("ID_Course.bin", tree2);
		//tree2.FindCouseName("000512");
		//tree2.FindCouseName("000256");
		//tree2.FindCouseName("000100");
		//tree2.Delete("000500");
		//tree2.Delete("000600");
		//tree2.Delete("000700");
		//tree2.Delete("000800");
		//tree2.Insert("001001", "语文");
		//tree2.Insert("001002", "数学");
		//tree2.Update("000503", "001003", "英语");
		//tree2.Update("000033", "001004", "法语");
		//tree2.Update("000103", "001005", "生物");
		//tree2.MidLoopPrint();
		//tree2.MidLoopWriteFile("updatedCourse.bin");

	CStuTree tree;
	// tree.createStuIdTree("ID_Name.bin", tree);
	tree.createStuNameTree("ID_Name.bin", tree);
	/* tree.InsertByName("100001", "张三");

	tree.InsertByName("100002", "添添");
	tree.InsertByName("100003", "王二");
	tree.InsertByName("100004", "美香");
	tree.InsertByName("100005", "王五");
	tree.InsertByName("100006", "赵六");
	tree.InsertByName("100007","李想");
	tree.InsertByName("100008", "小奇迹");
	tree.InsertByName("100009", "添添");
	tree.InsertByName("100010", "美香");
	tree.InsertByName("100011", "许怡瑶");
	tree.InsertByName("100012", "许怡瑶");
	tree.InsertByName("100013", "许怡瑶");
	tree.InsertByName("100014", "许怡瑶");
	tree.InsertByName("100015", "许怡瑶");

	tree.FindStuId("美香");
	tree.FindStuId("许怡瑶");
*/

//tree.FindStuName("065536");
//tree.MidLoopPrint();
//tree.MidLoopWriteFile("studentTree.bin");
/*tree.Update("100001","100007","李想");
tree.Update("065536", "100008", "小奇迹");
tree.Update("000001", "100009", "添添");
tree.Update("999990","100010", "美香");*/
//tree.Delete("100001");
//tree.Delete("100002");
//tree.Delete("100003");
//tree.Delete("100004");
//tree.Delete("100005");
//tree.Delete("100006");
//tree.Delete("100007");
//tree.Delete("100008");
//tree.Delete("100009");


///* CMenuHandler mh;

//CMyString str(" ");
//char digit = '1';
//str.Insert(0, digit);
//cout << str << endl;

//cout << “张三” << endl;
//bool t = (str1 == str3);
//bool t2 = (str1 != str3);
//bool t3 = (str1 > str3);
//bool t4 = (str < str1);
//CMyString str4 = str + str1;
//str += str1;
//cout << t << endl;
//cout << t2 << endl;
//cout << t3 << endl;
//cout << t4 << endl;
//cout << str4 << endl;
//cout << str << endl;
//CMyString str5;
//cin >> str5;
//cout << str5 << endl;
#endif
	 /*1. Initiate original data files:
	  ID_name.bin contains 100,000 students.
	  ID_  course.bin. contains 1000 courses. 
	  GradeList.bin contains grade info. (student ID, course ID and grade)
	 comment out the codes after these files are initiated. */

	/* FileHandler fh;
	 fh.CreateCourseList("CourseList.txt", "ID_Course.bin", 1000);
	 FileHandler fh1; 
	 fh1.CreateStuList("nameList.txt", "ID_Name.bin", 100000);
	FileHandler fh2;
	fh2.CreateRecord("ID_Name.bin", "ID_Course.bin", "GradeList.bin");*/

	// start the main menu
	CMenuHandler cmh;
	cmh.SelectMain();
	system("pause");

	return 0;
}

