#pragma once
#include <exception>
#include <stdexcept>

template<typename T>
class CVector
{
public:
	static size_t constexpr npos = -1;
public:
	CVector();
	CVector(const CVector& vct);
	CVector(CVector&& vct);
	virtual ~CVector();
	CVector& operator=(const CVector& vct); 

	size_t Size() const;
	void Clear();

	//增加（插入）
	void InsertHead(const T& val); //T -> const T& 避免一直使用拷贝构造
	void InsertTail(const T& val);
	void Insert(size_t nIdx, const T& val);

	//删除
	void DeleteHead();
	void DeleteTail();
	void Delete(size_t nIdx);

	//修改
	T& operator[](size_t nIdx);

	//查询
	size_t Find(T val);
private:
	CVector& Copy(const CVector& vct);
private:
	T* m_p = nullptr; //缓冲区
	size_t m_nCnt = 0; //元素个数
	size_t m_nCapacity = 0; //容量 
};
template<typename T>
void CVector<T>::InsertHead(const T& val)
{
	Insert(0, val);
}

template<typename T>
void  CVector<T>::InsertTail(const T& val)
{
	Insert(m_nCnt, val);
}

template<typename T>
void CVector<T>::Insert(size_t nIdx, const T& val)
{
	//检查索引
	if (nIdx > m_nCnt)
	{
		throw std::out_of_range("nIdx out of range");
	}
	//检查容量是否足够
	if (m_nCnt >= m_nCapacity)
	{
		//申请新内存
		size_t nNewCapacity = (m_nCapacity + 1) * 1.5; //1.5倍为经验值
		T* pNew = new T[nNewCapacity]; 
		if (pNew == nullptr)
		{
			throw std::bad_alloc();
		}

		//拷贝原来数据
		//memcpy(pNew, m_p, m_nCapacity * sizeof(T));
		for (size_t i = 0; i < m_nCapacity; i++)
		{
			pNew[i] = m_p[i]; //让使用的人实现operator=的重写(CString).
		}

		//释放原来内存
		delete[] m_p;

		//更新到新数据
		m_p = pNew;
		m_nCapacity = nNewCapacity;
	}
	//存入新数据
	//memmove(m_p + nIdx + 1, m_p + nIdx, sizeof(T) * (m_nCnt - nIdx));
	//从最大索引开始考
	for (size_t i = m_nCnt; i > nIdx; i--)
	{
		m_p[i] = m_p[i - 1];
	}

  	m_p[nIdx] = val;
	++m_nCnt;

}

template<typename T>
void  CVector<T>::DeleteHead()
{
	Delete(0);
}

template<typename T>
void CVector<T>::DeleteTail()
{
	Delete(m_nCnt - 1);
}

template<typename T>
void CVector<T>::Delete(size_t nIdx)
{
	//检查索引
	if (nIdx >= m_nCnt)
	{
		throw std::out_of_range("nIdx out of range");
	}
	//删除元素
	memmove(m_p + nIdx, m_p + nIdx + 1, (m_nCnt - nIdx - 1) * sizeof(T));
	--m_nCnt;
}

template<typename T>
T& CVector<T>::operator[](size_t nIdx)
{
	if (nIdx >= m_nCnt)
	{
		throw std::out_of_range("nIdx out of range");
	}
	return m_p[nIdx];
 }

template<typename T>
size_t  CVector<T>::Find(T val)
{
	for (size_t i = 0; i < m_nCnt; i++)
	{
		if (val == m_p[i])
		{
			return i;
		}

	}
	return npos;
}

template<typename T>
CVector<T>::CVector()
{
	//赋值为0
}

template<typename T>
CVector<T>::CVector(const CVector& vct)
{
	// *this = vct; 这个方法也可
	Copy(vct);
}

template<typename T>
CVector<T>::CVector(CVector&& vct)
{
	memcpy(this, &vct, sizeof(vct));
	memset(&vct, 0, sizeof(vct));
}

template<typename T>
CVector<T>::~CVector()
{
	if (m_p != nullptr)
	{
		delete[] m_p;
	}
	m_p = nullptr;
	m_nCapacity = 0;
	m_nCnt = 0;
}

template<typename T>
CVector<T>& CVector<T>::operator=(const CVector& vct)
{
	//清空自身
	Clear();
	//存储目标
		//检查
	return Copy(vct);

}

template<typename T>
CVector<T>& CVector<T>::Copy(const CVector& vct)
{
	if (vct.m_nCnt == 0)
	{
		return *this;
	}
	//申请内存
	m_p = new T[vct.m_nCnt];
	if (m_p == nullptr)
	{
		throw std::bad_alloc();
	}


	//拷贝数据
	m_nCnt = vct.m_nCnt;
	m_nCapacity = vct.m_nCapacity;
	memcpy(m_p, vct.m_p, sizeof(T) * m_nCnt);
	return *this;
}

template<typename T>
size_t  CVector<T>::Size() const
{
	return m_nCnt;
}

template<typename T>
void  CVector<T>::Clear()
{
	if (m_p != nullptr)
	{
		delete[] m_p;
	}
	m_p = nullptr;
	m_nCapacity = 0;
	m_nCnt = 0;
}

