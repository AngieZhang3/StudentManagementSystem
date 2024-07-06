#pragma once
#include "Clist.h"
template<typename T>
class CStack
{
public:
	void Push(T& val) { m_stack.InsertHead(val); } //Ñ¹Õ»
	void Pop() { m_stack.DeleteHead(); }
	T Top() { return m_stack.Head(); }
	size_t Size() { return m_stack.Size(); }
	void Clear() { m_stack.Clear(); }
	bool IsEmpty() { return m_stack.IsEmpty(); }

private:
	CList<T> m_stack; //Í·Õ»¶¥£¬Î²Õ»µ×
};

  