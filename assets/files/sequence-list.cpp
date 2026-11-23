#include <iostream>
#include<cstdlib>
using namespace std;
#define InitSize 10

// 顺序表的结构定义。
typedef struct
{
	int* data;   // 指向连续存储空间
	int Maxsize; // 当前最大容量
	int length;  // 当前元素个数
}Seqlist;

// 初始化顺序表，申请初始存储空间。
void InitList(Seqlist& L)
{
	L.data = (int*)malloc(InitSize * sizeof(int));
	L.length = 0;
	L.Maxsize = InitSize;
}

// 扩容：申请更大的空间，把旧元素复制过去，再释放旧空间。
void IncreaseList(Seqlist& L, int len)
{
	int* p = L.data;
	L.data = (int*)malloc((L.Maxsize + len) * sizeof(int));
	for (int i = 0; i < L.length; i++)
	{
		L.data[i] = p[i];
	}
	L.Maxsize += len;
	free(p);
}

// 在第 i 个位置插入元素 e，位序从 1 开始。
bool ListInsert(Seqlist& L, int i, int e)
{
	if (i<1 || i>L.length + 1)
	{
		return 0; // 插入位置不合法
	}
	if (L.length >= L.Maxsize)
	{
		return 0; // 当前空间已满
	}
	// 从后往前移动元素，为第 i 个位置腾出空间。
	for (int j = L.length; j >= i; j--)
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return 1;
}

// 删除第 i 个元素，并通过 e 返回被删除的值。
bool ListDelete(Seqlist& L, int i,int& e)
{
	if (i<1 || i>L.length)
	{
		return 0; // 删除位置不合法
	}
	e = L.data[i - 1];
	// 把被删除元素后面的元素依次向前移动一位。
	for (int j = i; j < L.length; j++)
	{
		L.data[j - 1] = L.data[j];
	}

	L.length--;
	return 1;
}

// 读取第 i 个元素，并通过 e 返回它的值。
bool GetElem(const Seqlist& L, int i, int& e)
{
	if (i<1 || i>L.length)
	{
		return 0; // 读取位置不合法
	}
	e = L.data[i - 1];
	return 1;

}

// 查找第一个值等于 e 的元素，返回它的位序。
int LocateElem(const Seqlist& L, int e)
{
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] == e)
		{
			return i + 1; // 数组下标 i 对应位序 i + 1
		}
	}

	// 遍历结束后仍未找到，返回 0。
	return 0;
}

// 修改第 i 个元素的值为 e。
bool SetElem(Seqlist& L, int i, int e)
{
	if (i<1 || i>L.length)
	{
		return 0; // 修改位置不合法
	}

	L.data[i - 1] = e;
	return 1;
}

// 按存储顺序输出顺序表中的所有元素。
void PrintList(const Seqlist& L)
{
	cout << "List(length=" << L.length << "): ";
	for (int i = 0; i < L.length; i++)
	{
		cout << L.data[i] << " ";
	}
	cout << endl;
}

int main()
{
	Seqlist L;
	InitList(L);

	// 依次插入 10、20、30、40、50。
	for (int i = 1; i <= 5; i++)
	{
		ListInsert(L, i, i * 10);
	}
	PrintList(L);

	int e = 0;
	GetElem(L, 3, e); // 读取第 3 个元素
	cout << "第三个元素是" << e << endl;

	int pos = LocateElem(L, 40); // 查找值为 40 的元素
	cout << "值 40 的位序: " << pos << endl;

	SetElem(L, 2, 999); // 把第 2 个元素修改为 999
	cout << "修改后: ";
	PrintList(L);

	int del = 0;
	if (ListDelete(L, 1, del)) // 删除第 1 个元素
	{
		cout << "删除了: " << del << endl;
	}
		
	PrintList(L);

	free(L.data); // 释放顺序表申请的内存
	return 0;
}
