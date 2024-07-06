#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

template<typename T>
class CBaseTree
{
protected: 
	void AdjustHeight(T* pNode);
	int GetHeight(T* pNode);
	void RotateLeft(T* pNode);
	void RotateRight(T* pNode);
	void DelLeaf(T* pDel);
	void DelSingle(T* pDel);
	//void DelDouble(T* pDel);
protected: 
	T* m_pRoot = nullptr;
	size_t m_nSize = 0;
};

template<typename T>
inline void CBaseTree<T>::AdjustHeight(T* pNode)
{
	while (pNode != nullptr)
	{
		//取左右子节点高度较大的值，再加1
		int nLHeight = GetHeight(pNode->m_pl);
		int nRHeight = GetHeight(pNode->m_pr);
		pNode->m_nHeight = std::max(nLHeight, nRHeight) + 1;

		//判断是否平衡
		if (nRHeight - nLHeight > 1)
		{
			T* pR = pNode->m_pr;
			if (GetHeight(pR->m_pl) > GetHeight(pR->m_pr))
			{
				/*		Node
						   \
							R         先右旋再左旋
						   /
						  RL
				*/
				RotateRight(pR);
				RotateLeft(pNode);

			}
			else
			{
				/*		Node
						  \
						   R
							\
							 RR
							  */
							  //GetHeight(pR->m_pl) <= GetHeight(pR->m_pr)  左旋 
				RotateLeft(pNode);
			}

		}
		if (nLHeight - nRHeight > 1)
		{
			T* pL = pNode->m_pl;
			if (GetHeight(pL->m_pl) < GetHeight(pL->m_pr))
			{

				/*		Node
					 /
					L
					 \
					 LR

			*/
				RotateLeft(pL);
				RotateRight(pNode);

			}
			else
			{
				/*		Node
						 /
						L
					   /
					  LL
				*/
				//GetHeight(pL->m_pl) > = GetHeight(pL->m_pr)  右旋 
				RotateRight(pNode);

			}




		}
		//沿着父节点，一路向上
		pNode = pNode->m_pp;
	}
}

template<typename T>
inline int CBaseTree<T>::GetHeight(T* pNode)
{
	return pNode == nullptr ? 0 : pNode->m_nHeight;
}

template<typename T>
inline void CBaseTree<T>::RotateLeft(T* pNode)
{/*
				 pp						      pp
				  |						       |
				Node					       R
				   \		rotate		   /      \
					\		left		  Node   RR
					 R      ===>	    	\
					/ \					     RL
				   RL  RR
	*/
	T* pPP = pNode->m_pp;
	T* pR = pNode->m_pr;
	T* pRL = pR->m_pl;

	pNode->m_pr = pRL;
	pNode->m_pp = pR;

	pR->m_pl = pNode;
	pR->m_pp = pPP;

	pRL != nullptr ? (pRL->m_pp = pNode) : nullptr;

	if (pPP == nullptr)
	{
		m_pRoot = pR;
	}
	else
	{
		//判断R位于PP的左边还是右边
		pPP->m_pl == pNode ? pPP->m_pl = pR : pPP->m_pr = pR;
	}
	pNode->m_nHeight =
		std::max(GetHeight(pNode->m_pl), GetHeight(pNode->m_pr)) + 1;
	pR->m_nHeight =
		std::max(GetHeight(pR->m_pl), GetHeight(pR->m_pr)) + 1;

}

template<typename T>
inline void CBaseTree<T>::RotateRight(T* pNode)
{

	/*
				 pp								 pp
				  |								  |
				Node					          L
				/			rotate			    /   \
			   /		    right 		   LL    Node
			  L             ===>		           /
			 / \							         LR
			LL  LR
	*/
	T* pPP = pNode->m_pp;
	T* pL = pNode->m_pl;
	T* pLR = pL->m_pr;

	//Node
	pNode->m_pl = pLR;
	pNode->m_pp = pL;

	//L
	pL->m_pp = pPP;
	pL->m_pr = pNode;

	//LR
	pLR != nullptr ? pLR->m_pp = pNode : nullptr;

	if (pPP == nullptr)
	{
		m_pRoot = pL;
	}
	else
	{
		pPP->m_pl == pNode ? pPP->m_pl = pL : pPP->m_pr = pL;
	}

	//调整高度
	pNode->m_nHeight =
		std::max(GetHeight(pNode->m_pl), GetHeight(pNode->m_pr)) + 1;
	pL->m_nHeight =
		std::max(GetHeight(pL->m_pl), GetHeight(pL->m_pr)) + 1;
}

template<typename T>
inline void CBaseTree<T>::DelLeaf(T* pDel)
{
	T* pParent = pDel->m_pp;
	//判断是否根节点
	if (pDel == m_pRoot)
	{
		delete pDel;
		m_pRoot = nullptr;
		--m_nSize;
		return;
	}


	if (pParent->m_pl == pDel)
	{
		pParent->m_pl = nullptr;
	}
	else
	{
		pParent->m_pr = nullptr;
	}

	delete pDel;
	--m_nSize;

	//删掉节点后，调整父节点高度
	AdjustHeight(pParent);
	return;
}

template<typename T>
inline void CBaseTree<T>::DelSingle(T* pDel)
{
	//获取要上提的节点
	T* pUp = pDel->m_pl == nullptr ? pDel->m_pr : pDel->m_pl;

	//判断是否根结点：
	if (pDel == m_pRoot)
	{
		m_pRoot = pUp;
		pUp->m_pp = nullptr;
		delete pDel;
		--m_nSize;
		return;
	}

	//判断要删除的是左还是右
	T* pParent = pDel->m_pp;
	if (pParent->m_pl == pDel)
	{
		//删除左，上提的节点设为左孩子
		pParent->m_pl = pUp;
	}
	else
	{
		//删除右，上提的节点设为右孩子
		pParent->m_pr = pUp;
	}
	pUp->m_pp = pParent;
	delete pDel;
	--m_nSize;

	//删掉节点后，调整父节点高度
	AdjustHeight(pParent);
}

//template<typename T>
//inline void CBaseTree<T>::DelDouble(T* pDel)
//{
//	//左子树查找最大值 或者 右子树删除最小值
//	T* pMax = pDel->m_pl;
//	while (pMax->m_pr != nullptr)
//	{
//		pMax = pMax->m_pr; //一路向右
//	}
//
//	//拷贝到被删除节点
//	memcpy((pDel->m_cou).m_szId, (pMax->m_cou).m_szId, sizeof((pDel->m_cou).m_szId));
//	memcpy((pDel->m_cou).m_szName, (pMax->m_cou).m_szName, sizeof((pDel->m_cou).m_szName));
//
//	//删除左子树最大节点
//	if (pMax->m_pl == nullptr)
//	{
//		DelLeaf(pMax);
//	}
//	else
//	{
//		DelSingle(pMax);
//	}
//}
