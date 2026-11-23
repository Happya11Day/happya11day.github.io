// 顺序表应用题：保留原代码的思路和逻辑，仅补充注释。
#include "Seqlist.cpp"

// 01. 删除最小值，并通过 e 带回被删元素的值。
bool DeleMin(Seqlist& L, int& e)
{
	if (L.length == 0)
	{
		return false; // 空表没有最小值，直接返回失败标志
	}

	e = L.data[0]; // e 既保存当前找到的最小值，也作为函数的结果返回
	int pos = 0;    // pos 指向当前最小值在数组中的下标
	for (int i = 1; i < L.length; i++)
	{
		if (L.data[i] < e)
		{
			e = L.data[i]; // 找到更小的元素，更新最小值

			pos = i; // 同时记录这个最小值的下标，最后才能准确删除它
		}
	}

	// 用最后一个元素覆盖最小值。若最小值原本就是最后一个元素，
	// 这里相当于把元素写回自身，不会影响结果。
	L.data[pos] = L.data[L.length - 1];
	L.length--; // 最后一个元素已经填入空位，顺序表长度减一
	return true;
}

// 02. 将顺序表原地逆置。
void Reverse(Seqlist& L)
{
	int temp;
	// 每次同时交换左右对称位置，因此只遍历前一半即可。
	for (int i = 0; i < L.length / 2; i++)
	{
		// 下标 i 的对称位置是 L.length - i - 1。
		// 先把左侧元素暂存起来，再完成左右交换。
		temp = L.data[i];
		L.data[i] = L.data[L.length - i - 1];
		L.data[L.length - i - 1] = temp;
	}
}

// 03. 删除所有值为 x 的元素。
void DelX(Seqlist& L, int x)
{
	// k 既是下一个保留元素的写入位置，也是已经保留的元素个数。
	// 由于 k 始终不会超过正在扫描的 i，写回不会破坏尚未读取的元素。
	int k = 0;
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] != x)
		{
			L.data[k] = L.data[i]; // 不等于 x，保留并写到前面
			k++;                  // 准备写入下一个保留元素
		}

	}
	L.length = k; // k 最终就是删除后剩下的元素个数
}

// 04. 删除值在 s 和 t 之间的元素。
bool Del_s_t(Seqlist& L, int s, int t)
{

	// k 记录前面已经删除的元素个数，也等于后续保留元素需要前移的距离。
	int k = 0;
	if (L.length == 0 || s >= t)
	{
		return false; // 空表没有元素可删；s >= t 不构成合法区间
	}
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i]>=s && L.data[i]<=t)
		{
			k++; // 当前元素在闭区间 [s, t] 内，跳过它并让前移距离增加
		}
		else
		{
			// 当前元素需要保留。它前面已经有 k 个元素被删除，
			// 所以把它向左移动 k 个位置，紧凑到已删除元素留下的空位中。
			L.data[i - k] = L.data[i];
		}
	
	}

	L.length -= k; // 删除 k 个元素后更新表长
	return true;
}

// 05. 删除有序顺序表中的重复元素。
bool DeleSame(Seqlist& L)
{
	if (L.length == 0)
	{
		return false; // 空表没有可比较的元素
	}
	int i, j;
	// i 指向最后一个确认不重复的元素，j 向后寻找新的不同值。
	// 有序表中所有相同元素都会相邻，因此只需比较 data[i] 与 data[j]。
	for (i = 0, j = 1; j < L.length; j++)
	{
		if (L.data[i] != L.data[j])
		{
			// 发现新值：先把 i 移到下一个保留位置，再复制新值。
			L.data[++i] = L.data[j];
		}
	}
	L.length = i + 1; // 下标 0 到 i 是去重后保留下来的全部元素
	return true;
}


// 06. 合并两个有序顺序表，结果由 C 带回。
bool Merge(Seqlist A, Seqlist B, Seqlist& C)
{
	if (A.length + B.length > C.Maxsize)
	{
		return false; // 结果表容量不足
	}

	// i、j 分别扫描 A、B，k 是结果表 C 的下一个写入位置。
	int i = 0, j = 0, k = 0;

	// 两表都还有元素时，每次把当前较小的元素放入 C。
	while (i < A.length && j < B.length)
	{
		if (A.data[i] < B.data[j])
		{
			C.data[k++] = A.data[i++]; // A 的当前元素较小，先取 A
		}
		else
		{
			C.data[k++] = B.data[j++]; // B 当前元素较小或相等，先取 B
		}
	}

	// 一个表遍历完后，另一个表可能还剩一段连续元素。
	// 由于两个输入表本来就是有序的，直接依次复制即可保持整体有序。
	while (i < A.length)
	{
		C.data[k++] = A.data[i++];
	}
	while (j < B.length)
	{
		C.data[k++] = B.data[j++];
	}

	C.length = k; // C 的长度等于实际写入的元素个数
	return true; 
}


typedef int datatype;
int m = 3, n = 4; // 前 m 个元素和后 n 个元素分别构成两个线性表
datatype* A = (datatype*)malloc(sizeof(datatype) * (m + n));

// 逆置数组的闭区间 [left, right]，right 是最后一个元素的下标。
void Reversebetter(datatype A[], int left, int right, int arraysize)
{
	if (left >= right || right > arraysize)
	{
		return; // 区间为空/只有一个元素，或右端点超出约定范围
	}
	int mid = (right + left) / 2; // 区间的中点下标

	// 第 i 次交换一对对称位置：
	// A[left + i] <-> A[right - i]。
	for (int i = 0; i <= mid - left; i++)
	{
		datatype temp = A[left + i];
		A[left + i] = A[right - i];
		A[right - i] = temp;
	}
}

// 07. 通过三次逆置交换数组中的前 m 个元素和后 n 个元素。
void Exchange(datatype A[], int left, int right, int arraysize)
{
	// 设原数组为 A + B，其中 A 有 m 个元素、B 有 n 个元素。
	// 1. 整体逆置后得到 B^R + A^R。
	Reversebetter(A, 0, m + n - 1, arraysize);

	// 2. 逆置前 n 个元素，把 B^R 恢复成 B。
	Reversebetter(A, 0, n - 1,arraysize);

	// 3. 逆置后 m 个元素，把 A^R 恢复成 A。
	// 最终顺序变为 B + A，完成两个线性表的位置交换。
	Reversebetter(A, n, m + n - 1, arraysize);
}
