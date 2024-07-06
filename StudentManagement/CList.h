#pragma once
#include <cassert>
#include<iostream>
#include <stdexcept>
using namespace std;

template<typename T>
struct Node
{
    T m_val = T();
    Node* m_prev = nullptr;
    Node* m_next = nullptr;
};

template<typename T>
class CList
{

public:
    CList();
    CList(const CList& list);
    void Copy(const CList& list);
    CList(CList&& list);
    virtual ~CList();
    CList& operator=(const CList& list);

    //插入
    Node<T>* InsertHead(const T& val);
    Node<T>* InsertTail(const T& val);
    Node<T>* Insert(Node<T>* pNode, const T& val);

    //删除
	void DeleteHead();
	void DeleteTail();
	void Delete(Node<T>* pNode);

    //修改
    T& Head();
    T& Tail();
    T& Access(Node<T>* pNode);

    //清空
    void Clear();

    //查询
    Node<T>* Find(const T& val) const;

    //其他
    size_t Size() const;
    bool IsEmpty() const;
private:
    void CreateGuard();
    void DestroyGuard();
private:
    Node<T>* m_pHeadGuard = nullptr; //头哨兵
    Node<T>* m_pTailGuard = nullptr; //尾哨兵
    size_t m_nCnt = 0; //个数
};


template <typename T>
CList<T>::CList()
{
    CreateGuard();
}

template <typename T>
CList<T>::CList(const CList& list)
{
    //创建哨兵节点
    CreateGuard();

    //遍历目标，取出所有数据，赋给自身
    Copy(list);
}

template <typename T>
void CList<T>::Copy(const CList& list)
{
    Node<T>* pNode = list.m_pHeadGuard->m_next;
    while (pNode != list.m_pTailGuard)
    {
        InsertTail(pNode->m_val);
        pNode = pNode->m_next;
    }

}

template <typename T>
CList<T>::CList(CList&& list)
{
    memcpy(this, &list, sizeof(list));
    memset(&list, 0, sizeof(list));
}

template <typename T>
CList<T>::~CList()
{
    //清掉节点
    Clear();
    //删除哨兵
    DestroyGuard();
}

template <typename T>
CList<T>& CList<T>::operator=(const CList& list)
{
    //清空自身
    Clear();
    //拷贝目标节点
    Copy(list);

    return *this;
}

template <typename T>
Node<T>* CList<T>::InsertHead(const T& val)
{
    return Insert(m_pHeadGuard->m_next, val);
}

template <typename T>
Node<T>* CList<T>::InsertTail(const T& val)
{
    return Insert(m_pTailGuard, val);
}

template <typename T>
Node<T>* CList<T>::Insert(Node<T>* pNode, const T& val)
{
    if (pNode == nullptr)
    {
        cout << "插入节点不能为空" << endl;
    }
    //创建新节点
	Node<T>* pNew = new Node<T>{ val };
    //判断插入的节点是否为空
	if (pNew == nullptr)
	{
        cout << "插入节点不能为空" << endl;
	}


    //插入指定节点
    /*
    *          new
    *          \|/
      pPre  <------> pNode
                |
               \|/
      pPre<--->new<--->pNode
    */
    // 创建新节点


    Node<T>* pPre = pNode->m_prev;
    pPre->m_next = pNew;
    pNode->m_prev = pNew;
    pNew->m_prev = pPre;
    pNew->m_next = pNode;

    ++m_nCnt;
    return pNew;

}
template <typename T>
void CList<T>::DeleteHead()
{
    //检查链表是否为空，否则会删除尾哨兵
    if (m_nCnt == 0)
    {
        throw std::exception("list is empty");
    }
    return Delete(m_pHeadGuard->m_next);
}
template <typename T>
void CList<T>::DeleteTail()
{
    //检查链表是否为空，否则会删除尾哨兵
    if (m_nCnt == 0)
    {
        cout << "list is empty" << endl;
    }
    return  Delete(m_pTailGuard->m_prev);
}

template <typename T>
void CList<T>::Delete(Node<T>* pNodel)
{
    //判断参数
    if (pNodel == nullptr)
    {
        throw std::invalid_argument("pNodel is null");

	}

    //删除
    /*
    pPre<--->pNode<--->pNext
                |
                |
               \|/
         pPre<---->pNext
    */
 
    Node<T>* pPre = pNodel->m_prev; //先把node的prev和next记录下来
    Node<T>* pNext = pNodel->m_next;
    pPre->m_next = pNext;
    pNext->m_prev = pPre;
    --m_nCnt;
    delete pNodel;

}

template <typename T>
T& CList<T>::Head()
{
    //空表无法访问
    if (m_nCnt == 0)
    {
        throw std::exception("list is empty");
    }

    //头结点是头哨兵的后继
    return m_pHeadGuard->m_next->m_val;
}

template <typename T>
T& CList<T>::Tail()
{
    //空表无法访问
    if (m_nCnt == 0)
    {
        throw std::exception("list is empty");
    }
    return m_pTailGuard->m_prev->m_val;
}

template<typename T>
inline T& CList<T>::Access(Node<T>* pNode)
{
    if (pNode == nullptr)
    {
        throw std::invalid_argument("pNode is null");
      
    }  
    return pNode->m_val;
}

template <typename T>
void CList<T>::Clear()
{
    while (!IsEmpty())
    {
        DeleteHead();
    }
    //对象不销毁，只是清数据。哨兵不清
#if 0
    Node* pNode = m_pHeadGuard->m_next;
    while (pNode != m_pTailGuard)
    {
        Node* pNext = pNode->m_next;
        delete pNode;
        pNode = pNext;
    }
    m_pHeadGuard->m_next = m_pTailGuard;
    m_pTailGuard->m_prev = m_pHeadGuard;
    m_nCnt = 0;
#endif // 0

}

template<typename T>
Node<T>* CList<T>::Find(const T& val) const
{
    Node<T>* pNode = m_pHeadGuard->m_next;
    while (pNode != m_pTailGuard)
    {
        if (pNode->m_val == val)
        {
            return pNode;
        }
        pNode = pNode->m_next;
    }
}

template <typename T>
size_t CList<T>::Size() const
{
    return m_nCnt;
}

template <typename T>
bool CList<T>::IsEmpty() const
{
    return m_nCnt == 0;
}

template <typename T>
void CList<T>::CreateGuard()
{
    m_pHeadGuard = new Node<T>;
    m_pTailGuard = new Node<T>;

    //要互相指一下
    m_pHeadGuard->m_next = m_pTailGuard;
    m_pTailGuard->m_prev = m_pHeadGuard;

}
template <typename T>
void CList<T>::DestroyGuard()
{
    delete m_pHeadGuard;
    delete m_pTailGuard;
}

