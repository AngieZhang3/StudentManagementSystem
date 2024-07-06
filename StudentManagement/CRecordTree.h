#pragma once
#include "FileHandler.h"
#include"CBaseTree.h"

/*
实现功能：
1. 新增选课记录(学生ID, 课程ID, 分数)
2. 删除选课记录(学生ID, 课程ID)
3. 更改选课记录(学生ID, 课程ID)
4. 通过学生ID查询该学生选修的课程信息



*/

struct RecordNode
{
	record m_rd;
	CVector<record> m_vctRecord; //用来存储相同ID的选课信息
	int m_nHeight{ 1 };
	RecordNode* m_pp = nullptr; // parent
	RecordNode* m_pl = nullptr; //left child
	RecordNode* m_pr = nullptr; //right child
	RecordNode(const char* szStuId, const char* szCourseId, int grade)
	{
		memcpy(m_rd.m_szStuId, szStuId, sizeof(m_rd.m_szStuId));
		memcpy(m_rd.m_szCourseId, szCourseId, sizeof(m_rd.m_szCourseId));
		memcpy(&(m_rd.m_grade), &grade, sizeof(m_rd.m_grade));
	}

};

class CRecordTree:public CBaseTree<RecordNode>
{
public:
	CRecordTree();
	virtual ~CRecordTree();
	void Clear(); // 删除整棵树
	//学生ID创建的树
    void CreateRdTreeBySId(const char* inputFilePath, CRecordTree& crt);//从选课文件读取并按照学生Id的顺序创建选课树
	bool InsertBySId(const char* szStuId, const char* szCourseId, int grade); //按照学生Id的顺序插入节点,Id相同则把课程Id和成绩存入到subRecord结构体，再存入到Vector里
	bool DeleteBySID(const char* szStuId);  //根据学生id删除节点
	bool DeleteRecord(const char* szSId, const char* szCId); //删除选课记录(学生ID, 课程ID)
	//bool Find(const char* szId) const; //查找id（学生id/课程id）
	RecordNode* FindNodeBySId(const char* szId) const; //通过id查找节点
   bool FindCourse(const char* szStuId) const; //通过学生ID查询课程ID和成绩,并打印
	bool Update(const char* szSId, const char* szCId, int nNewGrade);

	//课程ID创建的树
	void CreateRdTreeByCId(const char* inputFilePath, CRecordTree& crt);  //从选课文件读取并按照课程ID的顺序创建选课树
	bool InsertByCId(const char* szStuId, const char* szCourseId, int grade);  //按照课程ID的顺序插入节点,ID相同则把学生Id和成绩存入到subRecord结构体，再存入到Vector里
	bool DeleteByCId(const char* szCourseId);  //根据课程id删除节点
	RecordNode* FindNodeByCId(const char* szId) const; //通过id查找节点
	bool FindStudent(const char* szCourseId) const; //通过课程ID查找学生 ID和成绩，并打印

	bool IsEmpty() const;  //判断树是否为空
	size_t Size() const;
	void MidLoopPrint();  //中序遍历，打印节点 
	void MidLoopWriteFile(const char* outputFilePath); //中序遍历节点输出到文件
	bool AddLine(const char* szSId, const char* szCId, int grade, const char* outputFilePath); // 将增加的节点加入文件末尾

private:
	/*void AdjustHeight(RecordNode* pNode);
	int GetHeight(RecordNode* pNode);
	void RotateLeft(RecordNode* pNode);
	void RotateRight(RecordNode* pNode);
	void DelLeaf(RecordNode* pDel);
	void DelSingle(RecordNode* pDel);*/
	void DelDouble(RecordNode* pDel);
//private:
//	RecordNode* m_pRoot = nullptr;
//	size_t m_nSize = 0;
};

