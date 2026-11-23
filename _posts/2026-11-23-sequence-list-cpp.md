---
title: C++ 实现顺序表：从初始化到增删改查
date: 2026-11-23 00:00:00 +0800
categories: [编程笔记, C++]
tags: [顺序表, 数据结构, C++, 线性表]
description: 使用 C++ 实现顺序表，并为初始化、扩容、插入、删除、查找和修改逐步添加注释。
toc: true
comments: false
---

顺序表用一段连续的内存保存线性表，因此可以通过下标直接访问元素。这篇笔记使用 C++ 实现一个顺序表，并给每个核心操作添加注释。

> 文中的“位序”从 1 开始，而 C++ 数组下标从 0 开始。例如，第 1 个元素保存在 `data[0]`。

<div class="article-tags">
  <span class="article-tags-label">标签：</span>
{% for tag in page.tags %}
  <a
    class="article-tag"
    href="{{ site.baseurl }}/tags/{{ tag | slugify | url_encode }}/"
    title="查看标签 {{ tag }} 的相关文章"
  >{{ tag }}</a>
{% endfor %}
</div>

## 一、顺序表的结构

顺序表需要保存三部分信息：

- `data`：指向连续存储空间；
- `Maxsize`：当前最多能保存多少个元素；
- `length`：当前实际保存了多少个元素。

初始容量设为 10。`length` 不超过 `Maxsize`，合法位序是 `1` 到 `length`。

## 二、带注释的完整代码

下面的代码保留原实现，只增加注释，不对原有逻辑作修改。

```cpp
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
```

按照原代码运行，会看到：

```text
List(length=5): 10 20 30 40 50
第三个元素是30
值 40 的位序: 4
修改后: List(length=5): 10 999 30 40 50
删除了: 10
List(length=4): 999 30 40 50
```

## 三、可以改进的地方

下面只是建议，代码本身仍保持原样。

### 1. 检查 `malloc` 是否成功

`InitList` 和 `IncreaseList` 都调用了 `malloc`。实际项目中建议检查返回值是否为 `nullptr`，避免内存申请失败后继续访问空指针。

### 2. 扩容失败时的处理

当前扩容代码直接使用新的 `malloc` 结果覆盖 `L.data`。实际项目中建议先保存新空间地址并检查申请是否成功，确认成功后再替换原有指针，避免申请失败时丢失原数据。

## 四、复杂度小结

| 操作 | 时间复杂度 | 说明 |
| --- | --- | --- |
| 按下标读取 | O(1) | 可以直接计算元素地址 |
| 按值查找 | O(n) | 最坏情况下要检查全部元素 |
| 插入 | O(n) | 平均需要移动约一半元素 |
| 删除 | O(n) | 平均需要移动约一半元素 |
| 扩容 | O(n) | 需要把旧元素全部复制一遍 |

顺序表适合频繁按下标访问、元素数量相对稳定的场景；如果经常在中间插入或删除，通常可以考虑链表。

[下载完整的 C++ 源文件](/assets/files/sequence-list.cpp)
