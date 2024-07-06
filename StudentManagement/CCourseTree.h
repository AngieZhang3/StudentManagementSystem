#pragma once
#include "FileHandler.h"
#include "CBaseTree.h"

/*
实现功能：
(1)通过课程ID查询课程名
(2) 通过课程名查询课程ID
(3)新增课程(ID, 名字)
(4)删除课程(ID)
(5)更改课程ID
*/

struct CourseNode
{
	course m_cou;
	CVector<const char*> m_vctId;  //当以课程名生成avl时，如果课名相同，则把id放入vector
	int m_nHeight{ 1 };
	CourseNode* m_pp = nullptr; // parent
	CourseNode* m_pl = nullptr; //left child
	CourseNode* m_pr = nullptr; //right child
	CourseNode(const char* szId, const char* szName)
	{
		memcpy(m_cou.m_szId, szId, sizeof(m_cou.m_szId));
		memcpy(m_cou.m_szName, szName, sizeof(m_cou.m_szName));
	}

};

class CCourseTree:public CBaseTree <CourseNode>
{
public:
	CCourseTree();
	virtual ~CCourseTree();
	void Clear(); // 删除整棵树
	void CreateCourseIdTree(const char* inputFilePath, CCourseTree& sdt);  //从课程文件读取并按照ID的顺序创建课程树
	void CreateCourseNameTree(const char* inputFilePath, CCourseTree& sdt); //从课程文件读取并按照课程名的顺序创建课程树
	bool Insert(const char* szId, const char* szName);  //按照ID的顺序插入节点
	bool InsertByName(const char* szId, const char* szName); //按照课程名的顺序插入节点,课程名相同则把id插入vector
	bool Delete(const char* szId);
	bool Find(const char* szId) const;
	CourseNode* FindNode(const char* szId) const;
	bool FindCouseName(const char* szId) const; //通过课程ID查询课程名,并打印
	bool FindCourseId(const char* szName) const; //通过课程名查找ID，并打印
	bool ReturnCId(const char* szName, CVector<const char*> & vct) const; //通过课程名查找ID,并存储到vector里
	bool Update(const char* szId, const char* szName);
	bool IsEmpty() const;  //判断树是否为空
	size_t Size() const;
	void MidLoopPrint();  //中序遍历，打印节点 
	void MidLoopWriteFile(const char* outputFilePath); //中序遍历节点输出到文件
	bool AddLine(const char* szId, const char* szName, const char* outputFilePath); // 将增加的节点加入文件末尾
private:
//	void AdjustHeight(CourseNode* pNode);
//	int GetHeight(CourseNode* pNode);
//	void RotateLeft(CourseNode* pNode);
//	void RotateRight(CourseNode* pNode);
//	void DelLeaf(CourseNode* pDel);
//	void DelSingle(CourseNode* pDel);

	void DelDouble(CourseNode* pDel);
private:
	//CourseNode* m_pRoot = nullptr;
	//size_t m_nSize = 0;
};

