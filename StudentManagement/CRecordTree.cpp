#include "CRecordTree.h"
#include "CStack.h"  
CRecordTree::CRecordTree()
{
}

CRecordTree::~CRecordTree()
{
	Clear();
}

//按学生id删
void CRecordTree::Clear()
{
	while (!IsEmpty())
	{
		DeleteBySID((m_pRoot->m_rd).m_szStuId);
	}
}

void CRecordTree::CreateRdTreeBySId(const char* inputFilePath, CRecordTree& sdt)
{
	FILE* inputFile = fopen(inputFilePath, "rb");
	if (inputFile == NULL)
	{
		perror("无法读取inputFile");
		return;
	}
	record rd;
	while (fread(&rd, sizeof(record), 1, inputFile) > 0)
	{
		sdt.InsertBySId(rd.m_szStuId, rd.m_szCourseId, rd.m_grade);
	}
	fclose(inputFile);
}

//添加选课记录(学生ID，课程ID，成绩）
bool CRecordTree::InsertBySId(const char* szStuId, const char* szCourseId, int grade)
{
	if (strlen(szStuId) > SID_LEN || strlen(szCourseId) > CID_LEN || grade >= 1000)
	{
		cout << "输入学生信息有误" << endl;
		return false;
	}


	//创建节点

	RecordNode* pNew = new RecordNode{ szStuId, szCourseId, grade };
	if (pNew == nullptr)
	{
		cout << "创建课程记录节点失败" << endl;
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
	RecordNode* pTarget = m_pRoot;
	while (true)
	{
		if (strcmp(szStuId, (pTarget->m_rd).m_szStuId) < 0)
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
		else if (strcmp(szStuId, (pTarget->m_rd).m_szStuId) > 0)
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
		else   //学生ID相同，表示是同一个学生选的课，将选课记录加入vector
		{

			//检查想要插入的课程ID是否和pTarget的courseID相同，相同则不允许插入
			if (strcmp((pTarget->m_rd).m_szCourseId, szCourseId) == 0)
			{
				cout << "课程已存在，添加失败！" << endl;
				return false;
			}
			//遍历节点的vector，检查课程ID是否有重合，重合则不允许插入
			for (size_t i = 0; i < (pTarget->m_vctRecord).Size(); ++i)
			{
				if (strcmp(szCourseId, (pTarget->m_vctRecord)[i].m_szCourseId) == 0)
				{
					cout << "课程已存在，添加失败！" << endl;
					return false;
				}
			}
			record newRd;
			memcpy(newRd.m_szStuId, szStuId, sizeof(newRd.m_szStuId));
			memcpy(newRd.m_szCourseId, szCourseId, sizeof(newRd.m_szCourseId));
			memcpy(&newRd.m_grade, &grade, sizeof(newRd.m_grade));
			(pTarget->m_vctRecord).InsertTail(newRd);
			return true;
		}

	}
	return false;

}

void CRecordTree::MidLoopWriteFile(const char* outputFilePath)
{
	FILE* outputFile = fopen(outputFilePath, "wb");
	if (outputFile == NULL)
	{
		perror("studentTree无法写入outputFile");
		return;
	}

	CStack<RecordNode*> stk;
	RecordNode* p = m_pRoot;
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
		fwrite(&(p->m_rd), sizeof(Record), 1, outputFile); //先输出再弹不然拿不到      
		size_t nCount = (p->m_vctRecord).Size();
		if (nCount != 0)
		{
			for (size_t i = 0; i < nCount; ++i)
			{
				fwrite(&(p->m_vctRecord)[i], sizeof(record), 1, outputFile);
			}
		}
		stk.Pop();
		p = p->m_pr;
	}
	fclose(outputFile);
}

bool CRecordTree::AddLine(const char* szSId, const char* szCId, int grade, const char* outputFilePath)
{
	FILE* outputFile = fopen(outputFilePath, "ab");
	if (outputFile == NULL)
	{
		printf("RecordNode无法写入课程记录");
		return false;
	}
	RecordNode* pNode = new RecordNode{ szSId, szCId, grade };
	fwrite(&(pNode->m_rd), sizeof(record), 1, outputFile);
	fclose(outputFile);
	return true;
}

//void CRecordTree::AdjustHeight(RecordNode* pNode)
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
//			RecordNode* pR = pNode->m_pr;
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
//			RecordNode* pL = pNode->m_pl;
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
//
//int CRecordTree::GetHeight(RecordNode* pNode)
//{
//	return pNode == nullptr ? 0 : pNode->m_nHeight;
//}
//
//void CRecordTree::RotateLeft(RecordNode* pNode)
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
//	RecordNode* pPP = pNode->m_pp;
//	RecordNode* pR = pNode->m_pr;
//	RecordNode* pRL = pR->m_pl;
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
//
//void CRecordTree::RotateRight(RecordNode* pNode)
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
//	RecordNode* pPP = pNode->m_pp;
//	RecordNode* pL = pNode->m_pl;
//	RecordNode* pLR = pL->m_pr;
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

bool CRecordTree::DeleteBySID(const char* szId)
{
	//查找指定节点  
	RecordNode* pDel = FindNodeBySId(szId);
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
bool CRecordTree::DeleteRecord(const char* szSId, const char* szCId)
{
	RecordNode* pDel = FindNodeBySId(szSId);
	if (pDel == nullptr)
	{
		cout << "节点不存在" << endl;
		return false;
	}
	size_t nCount = pDel->m_vctRecord.Size();
	if (nCount == 0 && strcmp(szCId, (pDel->m_rd).m_szCourseId) == 0)
	{
		DeleteBySID(szSId);
		return true;
	}
	else if (nCount == 0 && strcmp(szCId, (pDel->m_rd).m_szCourseId) != 0)
	{
		cout << "课程ID不存在" << endl;
		return false;
	}
	else if (nCount != 0 && strcmp(szCId, (pDel->m_rd).m_szCourseId) == 0)  //节点的m_rd 为被删除对象，但vector里还有该学生的其他选课信息，所以不能删除整个节点

	{
		//将Vector里的尾元素拷贝到m_rd; 
		//然后将vector尾元素删除
		memset(&(pDel->m_rd).m_szStuId, 0,  SID_SIZE);
		memset(&(pDel->m_rd).m_szCourseId, 0,  CID_SIZE);
		memset(&(pDel->m_rd).m_grade, 0, sizeof(int));
		memcpy(&(pDel->m_rd).m_szStuId, (pDel->m_vctRecord[nCount - 1]).m_szStuId, SID_SIZE);
		memcpy(&(pDel->m_rd).m_szCourseId, (pDel->m_vctRecord[nCount - 1]).m_szCourseId, CID_SIZE);
		memcpy(&(pDel->m_rd).m_grade, &(pDel->m_vctRecord[nCount - 1]).m_grade, sizeof(int));
		(pDel->m_vctRecord).DeleteTail();
		return true;
	}
	else
	{
		for (size_t i = 0; i < nCount; ++i)
		{
			char* id = (pDel->m_vctRecord)[i].m_szCourseId;
			if (strcmp(id, szCId) == 0)
			{
				(pDel->m_vctRecord).Delete(i);
				cout << "节点已删除" << endl;
				return true;
			}
		}

	}
	cout << "选课记录不存在！" << endl;
	return false;

}

//bool CRecordTree::Find(const char* szId) const
//{
//	return FindNode(szId) != nullptr;
//
//}

bool  CRecordTree::Update(const char* szSId, const char* szCId, int nNewGrade)
{
	RecordNode* pUpdate = FindNodeBySId(szSId);
	if (pUpdate == nullptr)
	{
		cout << "节点不存在!" << endl;
		return false;
	}

	if (DeleteRecord(szSId, szCId) && InsertBySId(szSId, szCId, nNewGrade))
	{
		return true;
	}
	return false;
}
void CRecordTree::CreateRdTreeByCId(const char* inputFilePath, CRecordTree& crt)
{
	FILE* inputFile = fopen(inputFilePath, "rb");
	if (inputFile == NULL)
	{
		printf("无法读取选课记录");
		return;
	}
	record rd;
	while (fread(&rd, sizeof(record), 1, inputFile) > 0)
	{
		crt.InsertByCId(rd.m_szStuId, rd.m_szCourseId, rd.m_grade);
	}
	fclose(inputFile);
}
bool CRecordTree::InsertByCId(const char* szStuId, const char* szCourseId, int grade)
{
	//创建节点
	RecordNode* pNew = new RecordNode{ szStuId, szCourseId, grade };
	if (pNew == nullptr)
	{
		cout << "创建课程记录节点失败" << endl;
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
	RecordNode* pTarget = m_pRoot;
	while (true)
	{
		if (strcmp(szCourseId, (pTarget->m_rd).m_szCourseId) < 0)
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
		else if (strcmp(szCourseId, (pTarget->m_rd).m_szCourseId) > 0)
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
		else   //课程ID相同，将选课记录加入vector
		{
			record newRd;
			memcpy(newRd.m_szStuId, szStuId, sizeof(newRd.m_szStuId));
			memcpy(newRd.m_szCourseId, szCourseId, sizeof(newRd.m_szCourseId));
			memcpy(&newRd.m_grade, &grade, sizeof(newRd.m_grade));
			(pTarget->m_vctRecord).InsertTail(newRd);
			return true;
		}

	}
	return false;
}
bool CRecordTree::DeleteByCId(const char* szCourseId)
{
	//查找指定节点  
	RecordNode* pDel = FindNodeByCId(szCourseId);
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
RecordNode* CRecordTree::FindNodeByCId(const char* szId) const
{
	RecordNode* pTarget = m_pRoot;
	while (pTarget != nullptr)
	{
		if (strcmp(szId, (pTarget->m_rd).m_szCourseId) < 0)
		{
			//转左子树
			pTarget = pTarget->m_pl;
		}
		else if (strcmp(szId, (pTarget->m_rd).m_szCourseId) > 0)
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
bool CRecordTree::FindStudent(const char* szCourseId) const
{
	RecordNode* pRet = FindNodeByCId(szCourseId);
	if (pRet == nullptr)
	{
		cout << "该课程不存在！" << endl;
		return false;
	}
	size_t nCount = (pRet->m_vctRecord).Size();
	cout << "课程ID： " << (pRet->m_rd).m_szCourseId << " " << "选修的学生： " << (pRet->m_rd).m_szStuId << " " << "成绩： " << (pRet->m_rd).m_grade << endl;
	if (nCount == 0)
	{
		return true;
	}
	for (size_t i = 0; i < nCount; ++i)
	{
		cout << "课程ID： " << (pRet->m_vctRecord)[i].m_szCourseId << " " << "选修的学生： " << (pRet->m_vctRecord)[i].m_szStuId << " " << "成绩： " << (pRet->m_vctRecord)[i].m_grade << endl;
	}
	return true;
}

bool CRecordTree::FindCourse(const char* szStuId) const //通过学生ID查询课程ID和成绩,并打印
{
	RecordNode* pRet = FindNodeBySId(szStuId);
	if (pRet == nullptr)
	{
		cout << "该学生ID不存在！" << endl;
		return false;
	}
	size_t nCount = (pRet->m_vctRecord).Size();
	cout << "学生ID： " << (pRet->m_rd).m_szStuId << " " << "选修课程： " << (pRet->m_rd).m_szCourseId << " " << "成绩： " << (pRet->m_rd).m_grade << endl;
	if (nCount == 0)
	{
		return true;
	}
	for (size_t i = 0; i < nCount; ++i)
	{
		cout << "学生ID： " << (pRet->m_vctRecord)[i].m_szStuId << " " << "选修课程： " << (pRet->m_vctRecord)[i].m_szCourseId << " " << "成绩： " << (pRet->m_vctRecord)[i].m_grade << endl;
	}
	return true;
}

bool CRecordTree::IsEmpty() const
{
	return m_pRoot == nullptr; // m_nSize == 0;
}

size_t CRecordTree::Size() const
{
	return m_nSize;
}

//void CRecordTree::DelLeaf(RecordNode* pDel)
//{
//	RecordNode* pParent = pDel->m_pp;
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
//
//void CRecordTree::DelSingle(RecordNode* pDel)
//{
//	//获取要上提的节点
//	RecordNode* pUp = pDel->m_pl == nullptr ? pDel->m_pr : pDel->m_pl;
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
//	RecordNode* pParent = pDel->m_pp;
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

void CRecordTree::DelDouble(RecordNode* pDel)
{
	//左子树查找最大值 或者 右子树删除最小值
	RecordNode* pMax = pDel->m_pl;
	while (pMax->m_pr != nullptr)
	{
		pMax = pMax->m_pr; //一路向右
	}

	//拷贝到被删除节点
	memcpy(&(pDel->m_rd), &(pMax->m_rd), sizeof(pDel->m_rd)); //拷贝record
	//拷贝vector里的内容
	pDel->m_vctRecord = pMax->m_vctRecord;

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

void CRecordTree::MidLoopPrint()
{
	CStack<RecordNode*> stk;
	RecordNode* p = m_pRoot;
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
		cout << (p->m_rd).m_szStuId << " " << (p->m_rd).m_szCourseId << " " << (p->m_rd).m_grade << endl; //先输出再弹不然拿不到      
		size_t nCount = (p->m_vctRecord).Size();
		if (nCount != 0)
		{
			for (size_t i = 0; i < nCount; ++i)
			{
				cout << (p->m_vctRecord)[i].m_szStuId << " " << (p->m_vctRecord)[i].m_szCourseId << " " << (p->m_vctRecord)[i].m_grade << " " << endl;
			}
		}
		stk.Pop();
		p = p->m_pr;
	}
}

RecordNode* CRecordTree::FindNodeBySId(const char* szId) const
{
	RecordNode* pTarget = m_pRoot;
	while (pTarget != nullptr)
	{
		if (strcmp(szId, (pTarget->m_rd).m_szStuId) < 0)
		{
			//转左子树
			pTarget = pTarget->m_pl;
		}
		else if (strcmp(szId, (pTarget->m_rd).m_szStuId) > 0)
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
