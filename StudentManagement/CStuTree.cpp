﻿#include "CStuTree.h"
#include "CStack.h"  

CStuTree::CStuTree()
{
}

CStuTree::~CStuTree()
{
	Clear();
}


void CStuTree::Clear()
{
	while (!IsEmpty())
	{
		Delete((m_pRoot->m_stu).m_szId);
	}
}

void CStuTree::createStuIdTree(const char* inputFilePath, CStuTree& sdt)
{
	FILE* inputFile = fopen(inputFilePath, "rb");
	if (inputFile == NULL)
	{
		perror("无法读取inputFile");
		return;
	}
	student stu;
	while (fread(&stu, sizeof(student), 1, inputFile) > 0)
	{
		sdt.Insert(stu.m_szId, stu.m_szName);
	}
	fclose(inputFile);
}

void CStuTree::createStuNameTree(const char* inputFilePath, CStuTree& sdt)
{
	FILE* inputFile = fopen(inputFilePath, "rb");
	if (inputFile == NULL)
	{
		printf("无法读取学生文件");
		return;
	}
	student stu;
	while (fread(&stu, sizeof(student), 1, inputFile) > 0)
	{
		sdt.InsertByName(stu.m_szId, stu.m_szName);
	}
	fclose(inputFile);
}

void CStuTree::MidLoopWriteFile(const char* outputFilePath)
{
	FILE* outputFile = fopen(outputFilePath, "wb");
	if (outputFile == NULL)
	{
		printf("studentTree无法写入学生文件");
		return;
	}

	CStack<StuNode*> stk;
	StuNode* p = m_pRoot;
	//沿着左孩子，一路向下，入栈
	while (true)
	{
		while (p != nullptr)
		{
			stk.Push(p);
			p = p->m_pl;
		}
		//栈为空，则处理完毕
		if (stk.IsEmpty())
		{
			break;
		} 
		//弹栈，输出，转右子树
		p = stk.Top();
		fwrite(&(p->m_stu), sizeof(student), 1, outputFile); //先输出再弹不然拿不到      
		stk.Pop();
		p = p->m_pr;
	}
	fclose(outputFile);
}

bool CStuTree::AddLine(const char* szId, const char* szName, const char* outputFilePath)
{
	FILE* outputFile = fopen(outputFilePath, "ab");
	if (outputFile == NULL)
	{
		printf("StuNode无法写入学生文件");
		return false;
	}
	StuNode *pNode = new StuNode{ szId, szName };
	fwrite(&(pNode->m_stu), sizeof(student), 1, outputFile);
	fclose(outputFile);
	return true;
}

//void CStuTree::AdjustHeight(StuNode* pNode)
//{
//	while (pNode != nullptr)
//	{
//		//取左右子节点高度较大的值，再加1
//		int nLHeight = GetHeight(pNode->m_pl);
//		int nRHeight = GetHeight(pNode->m_pr);
//		pNode->m_nHeight = std::max(nLHeight, nRHeight) + 1;
//
//		//判断是否平衡
//		if (nRHeight - nLHeight > 1)
//		{
//			StuNode* pR = pNode->m_pr;
//			if (GetHeight(pR->m_pl) > GetHeight(pR->m_pr))
//			{
//				/*		Node
//						   \
//							R         先右旋再左旋
//						   /
//						  RL
//				*/
//				RotateRight(pR);
//				RotateLeft(pNode);
//
//			}
//			else
//			{
//				/*		Node
//						  \
//						   R
//							\
//							 RR
//							  */
//							  //GetHeight(pR->m_pl) <= GetHeight(pR->m_pr)  左旋 
//				RotateLeft(pNode);
//			}
//
//		}
//		if (nLHeight - nRHeight > 1)
//		{
//			StuNode* pL = pNode->m_pl;
//			if (GetHeight(pL->m_pl) < GetHeight(pL->m_pr))
//			{
//
//				/*		Node
//					 /
//					L
//					 \
//					 LR
//
//			*/
//				RotateLeft(pL);
//				RotateRight(pNode);
//
//			}
//			else
//			{
//				/*		Node
//						 /
//						L
//					   /
//					  LL
//				*/
//				//GetHeight(pL->m_pl) > = GetHeight(pL->m_pr)  右旋 
//				RotateRight(pNode);
//
//			}
//
//
//
//
//		}
//		//沿着父节点，一路向上
//		pNode = pNode->m_pp;
//	}
//}

//int CStuTree::GetHeight(StuNode* pNode)
//{
//	return pNode == nullptr ? 0 : pNode->m_nHeight;
//}

//void CStuTree::RotateLeft(StuNode* pNode)
//{
//	/*
//				 pp						 pp
//				  |						  |
//				Node					  R
//				   \					/   \
//					\		左旋		  Node   RR
//					 R      ===>		\
//					/ \					RL
//				   RL  RR
//	*/
//	StuNode* pPP = pNode->m_pp;
//	StuNode* pR = pNode->m_pr;
//	StuNode* pRL = pR->m_pl;
//
//	pNode->m_pr = pRL;
//	pNode->m_pp = pR;
//
//	pR->m_pl = pNode;
//	pR->m_pp = pPP;
//
//	pRL != nullptr ? (pRL->m_pp = pNode) : nullptr;
//
//	if (pPP == nullptr)
//	{
//		m_pRoot = pR;
//	}
//	else
//	{
//		//判断R位于PP的左边还是右边
//		pPP->m_pl == pNode ? pPP->m_pl = pR : pPP->m_pr = pR;
//	}
//	pNode->m_nHeight =
//		std::max(GetHeight(pNode->m_pl), GetHeight(pNode->m_pr)) + 1;
//	pR->m_nHeight =
//		std::max(GetHeight(pR->m_pl), GetHeight(pR->m_pr)) + 1;
//
//}

//void CStuTree::RotateRight(StuNode* pNode)
//{
//
//	/*
//				 pp						 pp
//				  |						  |
//				Node					  L
//				/						/   \
//			   /		    右旋		   LL    Node
//			  L             ===>		     /
//			 / \							LR
//			LL  LR
//	*/
//	StuNode* pPP = pNode->m_pp;
//	StuNode* pL = pNode->m_pl;
//	StuNode* pLR = pL->m_pr;
//
//	//Node
//	pNode->m_pl = pLR;
//	pNode->m_pp = pL;
//
//	//L
//	pL->m_pp = pPP;
//	pL->m_pr = pNode;
//
//	//LR
//	pLR != nullptr ? pLR->m_pp = pNode : nullptr;
//
//	if (pPP == nullptr)
//	{
//		m_pRoot = pL;
//	}
//	else
//	{
//		pPP->m_pl == pNode ? pPP->m_pl = pL : pPP->m_pr = pL;
//	}
//
//	//调整高度
//	pNode->m_nHeight =
//		std::max(GetHeight(pNode->m_pl), GetHeight(pNode->m_pr)) + 1;
//	pL->m_nHeight =
//		std::max(GetHeight(pL->m_pl), GetHeight(pL->m_pr)) + 1;
//
//
//}

bool CStuTree::Insert(const char* szId, const char* szName)
{  
	//创建节点
	if (strlen(szId) > SID_LEN || strlen(szName) >  SNAME_SIZE - 1|| strlen(szName) == 0)
	{
		cout << "输入学生信息有误" << endl;
		return false;
	}
	StuNode* pNew = new StuNode{ szId, szName };
	if (pNew == nullptr)
	{
		cout << "创建学生节点失败" << endl;
		return false;
	}

	//是否为空表
	if (IsEmpty())
	{
		m_pRoot = pNew;
		++m_nSize;
		return true;
	}

	//寻找位置
	StuNode* pTarget = m_pRoot;
	while (true)
	{
		if (strcmp(szId, (pTarget->m_stu).m_szId) < 0)
		{
			//是否有左孩子
			if (pTarget->m_pl == nullptr)
			{
				//没有左孩子，存入
				pTarget->m_pl = pNew;
				pNew->m_pp = pTarget;
				++m_nSize;

				//AVL tree:调整高度
				AdjustHeight(pNew);                                    
				return true;
			}
			//转左子树
			pTarget = pTarget->m_pl;

		}
		else if (strcmp(szId, (pTarget->m_stu).m_szId) > 0)
		{
			//是否有右孩子
			if (pTarget->m_pr == nullptr)
			{
				//没有右孩子，存入
				pTarget->m_pr = pNew;
				pNew->m_pp = pTarget;
				++m_nSize;

				//AVL tree:调整高度
				AdjustHeight(pNew);
				return true;
			}
			//转右子树
			pTarget = pTarget->m_pr;
		}
		else
		{
			cout << "学生ID已存在" << endl;
			return false;
		}
	}
		return false;

	}

bool CStuTree::InsertByName(const char* szId, const char* szName)
{
	//创建节点
	if (strlen(szId) > SID_LEN || strlen(szName) > SNAME_SIZE - 1 || strlen(szName) == 0)
	{
		cout << "输入学生信息有误" << endl;
		return false;
	}
	StuNode* pNew = new StuNode{ szId, szName };
	if (pNew == nullptr)
	{
		cout << "创建学生节点失败" << endl;
		return false;
	}

	//是否为空表
	if (IsEmpty())
	{
		m_pRoot = pNew;
		++m_nSize;
		return true;
	}

	//寻找位置
	StuNode* pTarget = m_pRoot;
	while (true)
	{
		if (strcmp(szName, (pTarget->m_stu).m_szName) < 0)
		{
			//是否有左孩子
			if (pTarget->m_pl == nullptr)
			{
				//没有左孩子，存入
				pTarget->m_pl = pNew;
				pNew->m_pp = pTarget;
				++m_nSize;

				//AVL tree:调整高度
				AdjustHeight(pNew);
				return true;
			}
			//转左子树
			pTarget = pTarget->m_pl;

		}
		else if (strcmp(szName, (pTarget->m_stu).m_szName) > 0)
		{
			//是否有右孩子
			if (pTarget->m_pr == nullptr)
			{
				//没有右孩子，存入
				pTarget->m_pr = pNew;
				pNew->m_pp = pTarget;
				++m_nSize;

				//AVL tree:调整高度
				AdjustHeight(pNew);
				return true;
			}
			//转右子树
			pTarget = pTarget->m_pr;
		}
		else
		{
			const char* szNewId = new char[9];
			memcpy(const_cast<char*>(szNewId), szId, 9);
			(pTarget->m_vctId).InsertTail(szNewId);
			return true;
		}
	}
	return false;
}

bool CStuTree::Delete(const char* szId)
{
	//查找指定节点  
	StuNode* pDel = FindNode(szId);
	if (pDel == nullptr)
	{
		return false;
	}

	//判断情况

	//叶子
	if (pDel->m_pl == nullptr && pDel->m_pr == nullptr)
	{
		DelLeaf(pDel);
		return true;
	}

	//单分支
	if (pDel->m_pl == nullptr || pDel->m_pr == nullptr)
	{
		DelSingle(pDel);
		return true;
	}

	//双分支
	DelDouble(pDel);
	return true;

}

bool CStuTree::Find(const char* szId) const
{
	return FindNode(szId) != nullptr;

}

bool CStuTree::Update(const char* szId, const char* szNewName)
{
	StuNode* pUpdate = FindNode(szId);
	if (pUpdate == nullptr)
	{
		cout << "学生ID不存在" << endl;
		return false;
	}

	if (Delete(szId) && Insert(szId, szNewName))
	{
		return true;
	}
	return false;
}

bool CStuTree::FindStuId(const char* szName) const
{
	StuNode* pTarget = m_pRoot;
	while (pTarget != nullptr)
	{
		if (strcmp(szName, (pTarget->m_stu).m_szName) < 0)
		{
			//转左子树
			pTarget = pTarget->m_pl;
		}
		else if (strcmp(szName, (pTarget->m_stu).m_szName) > 0)
		{
			//转右子树
			pTarget = pTarget->m_pr;
		}
		else
		{
			cout << "姓名为" << szName << "的学生ID为: " << (pTarget->m_stu).m_szId; //相等表示找到了
			size_t nCount = (pTarget->m_vctId).Size();
			if (nCount != 0)
			{
				for (size_t i = 0; i < nCount; ++i)
				{
					cout << ", " << (pTarget->m_vctId)[i];
				}
			}
			cout << " " << endl;
			return true;
		}
	}
	cout << "没有找到该学生的记录" << endl;
	return false;
}

bool CStuTree::IsEmpty() const
{
 	return  m_nSize == 0; // or return m_pRoot == nullptr;
	
}

size_t CStuTree::Size() const
{
	return m_nSize;
}


//void CStuTree::DelLeaf(StuNode* pDel)
//{
//	StuNode* pParent = pDel->m_pp;
//	//判断是否根节点
//	if (pDel == m_pRoot)
//	{
//		delete pDel;
//		m_pRoot = nullptr;
//		--m_nSize;
//		return;
//	}
//
//
//	if (pParent->m_pl == pDel)
//	{
//		pParent->m_pl = nullptr;
//	}
//	else
//	{
//		pParent->m_pr = nullptr;
//	}
//
//	delete pDel;
//	--m_nSize;
//
//	//删掉节点后，调整父节点高度
//	AdjustHeight(pParent);
//	return;
//
//}

//void CStuTree::DelSingle(StuNode* pDel)
//{
//	//获取要上提的节点
//	StuNode* pUp = pDel->m_pl == nullptr ? pDel->m_pr : pDel->m_pl;
//
//	//判断是否根结点：
//	if (pDel == m_pRoot)
//	{
//		m_pRoot = pUp;
//		pUp->m_pp = nullptr;
//		delete pDel;
//		--m_nSize;
//		return;
//	}
//
//	//判断要删除的是左还是右
//	StuNode* pParent = pDel->m_pp;
//	if (pParent->m_pl == pDel)
//	{
//		//删除左，上提的节点设为左孩子
//		pParent->m_pl = pUp;
//	}
//	else
//	{
//		//删除右，上提的节点设为右孩子
//		pParent->m_pr = pUp;
//	}
//	pUp->m_pp = pParent;
//	delete pDel;
//	--m_nSize;
//
//	//删掉节点后，调整父节点高度
//	AdjustHeight(pParent);
//}

void CStuTree::DelDouble(StuNode* pDel)
{
	//左子树查找最大值 或者 右子树删除最小值
	StuNode* pMax = pDel->m_pl;
	while (pMax->m_pr != nullptr)
	{
		pMax = pMax->m_pr; //一路向右
	}
	
	//拷贝到被删除节点
	memcpy((pDel->m_stu).m_szId, (pMax->m_stu).m_szId, sizeof((pDel->m_stu).m_szId));
	memcpy((pDel->m_stu).m_szName, (pMax->m_stu).m_szName, sizeof((pDel->m_stu).m_szName));

	//删除左子树最大节点
	if (pMax->m_pl == nullptr)
	{
		DelLeaf(pMax);
	}
	else
	{
		DelSingle(pMax);
	}
}


void CStuTree::MidLoopPrint()
{
	CStack<StuNode*> stk;
	StuNode* p = m_pRoot;
	//沿着左孩子，一路向下，入栈
	while (true)
	{
		while (p != nullptr)
		{
			stk.Push(p);
			p = p->m_pl;
		}
		//栈为空，则处理完毕
		if (stk.IsEmpty())
		{
			break;
		}
		//弹栈，输出，转右子树
		p = stk.Top();
		cout << (p->m_stu).m_szId << " " << (p->m_stu).m_szName << endl; //先输出再弹不然拿不到      
		stk.Pop();
		p = p->m_pr;
	}
}



StuNode* CStuTree::FindNode(const char* szId) const
{
	StuNode* pTarget = m_pRoot;
	while (pTarget != nullptr)
	{
		if (strcmp(szId, (pTarget->m_stu).m_szId) < 0)
		{
			//转左子树
			pTarget = pTarget->m_pl;
		}
		else if (strcmp(szId, (pTarget->m_stu).m_szId) > 0)
		{
			//转右子树
			pTarget = pTarget->m_pr;
		}
		else
		{
			return pTarget; //相等表示找到了
		}
	}
	return nullptr;
}

bool CStuTree::FindStuName(const char* szId) const
{
	StuNode* pTarget = m_pRoot;
	while (pTarget != nullptr)
	{
		if (strcmp(szId, (pTarget->m_stu).m_szId) < 0)
		{
			//转左子树
			pTarget = pTarget->m_pl;
		}
		else if (strcmp(szId, (pTarget->m_stu).m_szId) > 0)
		{
			//转右子树
			pTarget = pTarget->m_pr;
		}
		else
		{
			cout << "ID为" << szId << "的学生姓名为: " << (pTarget->m_stu).m_szName << endl; //相等表示找到了
			return true;
		}
	}
	cout << "没有找到该学生的记录" << endl;
	return false;
}
