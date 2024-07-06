#pragma once
#include "FileHandler.h"
#include "CList.h"
#include"CBaseTree.h"
/*
按照studentID 生成的avl
功能：
(1) 通过学生ID查询学生姓名
(2)通过学生姓名查询学生ID
(3)新增学生(ID, 名字)
(4) 删除学生(ID)
(5) 修改学生（ID, 姓名）
*/

struct StuNode
{
	student m_stu;
	CVector<const char*> m_vctId;  //当以姓名顺序生成avl时，如果姓名相同，则把id放入vector
	int m_nHeight{ 1 };
	StuNode* m_pp = nullptr; // parent
	StuNode* m_pl = nullptr; //left child
	StuNode* m_pr = nullptr; //right child
	StuNode(const char* szId, const char* szName)
	{
		memcpy(m_stu.m_szId, szId, sizeof(m_stu.m_szId));
		memcpy(m_stu.m_szName, szName, sizeof(m_stu.m_szName));
	}

};

class CStuTree : public CBaseTree<StuNode>
{
public:
	CStuTree();
	//CStuTree(const CStuTree& tree);

	//CStuTree(CStuTree&& tree);
	virtual ~CStuTree();
	void Clear(); // 删除整棵树
	//CStuTree& operator=(const CStuTree& tree);

	void createStuIdTree(const char* inputFilePath, CStuTree& sdt);  //从学生文件读取并按照ID的顺序创建学生树
	void createStuNameTree(const char* inputFilePath, CStuTree& sdt); //从学生文件读取并按照姓名的顺序创建学生树
	bool Insert(const char* szId, const char* szName);  //按照ID的顺序插入节点
	bool InsertByName(const char* szId, const char* szName); //按照姓名的顺序插入节点, 姓名相同则把id插入vector
	bool Delete(const char* szId);
	bool Find(const char* szId) const;
	StuNode* FindNode(const char* szId) const;
	bool FindStuName(const char* szId) const; //通过学生ID查询学生姓名,并打印
	bool FindStuId(const char* szName) const; //通过学生姓名查找ID，并打印
	bool Update(const char* szId, const char* szNewName);
	bool IsEmpty() const;  //判断树是否为空
	size_t Size() const;

#if 0
	//递归遍历 
	void Mid();
	void Pre();
	void Post();
	void Layer(); //层序  
#endif // 0


	//迭代遍历
	void MidLoopPrint();  //中序遍历，打印节点 
	//void PreLoop();
	//void PostLoop();
	void MidLoopWriteFile(const char* outputFilePath); //中序遍历节点输出到文件
	bool AddLine(const char* szId, const char* szName, const char* outputFilePath); // 将增加的节点加入文件末尾

private:
	//	void AdjustHeight(StuNode* pNode);
	//	int GetHeight(StuNode* pNode);
	//	void RotateLeft(StuNode* pNode);
	//	void RotateRight(StuNode* pNode);
	//
	//	//void Copy(const CStuTree& set);
	//	//void Mid(Node* pNode);      
	//	//void Pre(Node* pNode);  
	//	//void Post(Node* pNode);
	//	//void Layer(Node* pNode);
	//
	//	void DelLeaf(StuNode* pDel);
	//	void DelSingle(StuNode* pDel);
	void DelDouble(StuNode* pDel);
	//private:
	//	StuNode* m_pRoot = nullptr;
	//	size_t m_nSize = 0;
};



