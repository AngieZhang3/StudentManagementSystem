#pragma once
#include <iostream>
#include <fstream>
#include "CVector.h"
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
typedef struct Student student;
typedef struct Course course;
typedef struct Record record;
#define SID_SIZE 9
#define SNAME_SIZE 55
#define CID_SIZE 8
#define COU_SIZE 88
#define SID_LEN 8
#define CID_LEN 6
/*
此类用于读写文件和处理原始数据
原始数据为：
1. 随机生成的学生姓名文件(10w 姓名，txt格式）
2. 课程文件(1000 课程，txt格式）

*/
struct Student 
{
	char m_szId[SID_SIZE];
	char m_szName[SNAME_SIZE];
};

struct Course
{
	char m_szId[CID_SIZE];
	char m_szName[COU_SIZE];
};

struct Record
{
	char m_szStuId[SID_SIZE];
	char m_szCourseId[CID_SIZE];
	int m_grade; 
};


class FileHandler
{
public:
/*读取txt文件， 随机生成ID
* 将txt文件里读取的名称加到学生/课程结构体的szName里
* 将id添加到szId里
	写入新的文件：学生表ID_Name和课程表ID_Course*/
	void CreateStuList(const char* inputFilePath, const char* outputFilePath, int nCount);
	void CreateCourseList(const char* inputFilePath, const char* outputFilePath, int nCount);

	/*创建100w选课记录: 学生ID，课程ID，成绩
		从学生表和课程表中随机选取学生ID和课程ID
		一个学生添加十个课程
		随机创建成绩
	   组成记录结构体
		写入选课记录文件
	*/
	void CreateRecord(const char* stuFilePath, const char* courseFilePath, const char* outFilePath);
									
};

