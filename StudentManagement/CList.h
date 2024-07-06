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

    //����
    Node<T>* InsertHead(const T& val);
    Node<T>* InsertTail(const T& val);
    Node<T>* Insert(Node<T>* pNode, const T& val);

    //ɾ��
	void DeleteHead();
	void DeleteTail();
	void Delete(Node<T>* pNode);

    //�޸�
    T& Head();
    T& Tail();
    T& Access(Node<T>* pNode);

    //���
    void Clear();

    //��ѯ
    Node<T>* Find(const T& val) const;

    //����
    size_t Size() const;
    bool IsEmpty() const;
private:
    void CreateGuard();
    void DestroyGuard();
private:
    Node<T>* m_pHeadGuard = nullptr; //ͷ�ڱ�
    Node<T>* m_pTailGuard = nullptr; //β�ڱ�
    size_t m_nCnt = 0; //����
};


template <typename T>
CList<T>::CList()
{
    CreateGuard();
}

template <typename T>
CList<T>::CList(const CList& list)
{
    //�����ڱ��ڵ�
    CreateGuard();

    //����Ŀ�꣬ȡ���������ݣ���������
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
    //����ڵ�
    Clear();
    //ɾ���ڱ�
    DestroyGuard();
}

template <typename T>
CList<T>& CList<T>::operator=(const CList& list)
{
    //�������
    Clear();
    //����Ŀ��ڵ�
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
        cout << "����ڵ㲻��Ϊ��" << endl;
    }
    //�����½ڵ�
	Node<T>* pNew = new Node<T>{ val };
    //�жϲ���Ľڵ��Ƿ�Ϊ��
	if (pNew == nullptr)
	{
        cout << "����ڵ㲻��Ϊ��" << endl;
	}


    //����ָ���ڵ�
    /*
    *          new
    *          \|/
      pPre  <------> pNode
                |
               \|/
      pPre<--->new<--->pNode
    */
    // �����½ڵ�


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
    //��������Ƿ�Ϊ�գ������ɾ��β�ڱ�
    if (m_nCnt == 0)
    {
        throw std::exception("list is empty");
    }
    return Delete(m_pHeadGuard->m_next);
}
template <typename T>
void CList<T>::DeleteTail()
{
    //��������Ƿ�Ϊ�գ������ɾ��β�ڱ�
    if (m_nCnt == 0)
    {
        cout << "list is empty" << endl;
    }
    return  Delete(m_pTailGuard->m_prev);
}

template <typename T>
void CList<T>::Delete(Node<T>* pNodel)
{
    //�жϲ���
    if (pNodel == nullptr)
    {
        throw std::invalid_argument("pNodel is null");

	}

    //ɾ��
    /*
    pPre<--->pNode<--->pNext
                |
                |
               \|/
         pPre<---->pNext
    */
 
    Node<T>* pPre = pNodel->m_prev; //�Ȱ�node��prev��next��¼����
    Node<T>* pNext = pNodel->m_next;
    pPre->m_next = pNext;
    pNext->m_prev = pPre;
    --m_nCnt;
    delete pNodel;

}

template <typename T>
T& CList<T>::Head()
{
    //�ձ��޷�����
    if (m_nCnt == 0)
    {
        throw std::exception("list is empty");
    }

    //ͷ�����ͷ�ڱ��ĺ��
    return m_pHeadGuard->m_next->m_val;
}

template <typename T>
T& CList<T>::Tail()
{
    //�ձ��޷�����
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
    //�������٣�ֻ�������ݡ��ڱ�����
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

    //Ҫ����ָһ��
    m_pHeadGuard->m_next = m_pTailGuard;
    m_pTailGuard->m_prev = m_pHeadGuard;

}
template <typename T>
void CList<T>::DestroyGuard()
{
    delete m_pHeadGuard;
    delete m_pTailGuard;
}

