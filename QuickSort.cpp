#include<iostream>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
//平均时间复杂度为NlgN,快排的最差情况为序列完全有序，此时快排退化为冒泡排序，时间复杂度为N^2
//过程：
//	1、设两个指示 i=left，j=right；设 arr[left] 为基准数
//	2、从后向前寻找比基准元素小的元素，填至空位处
//	3、从前向后寻找比基准元素大的元素，填至空位处
//	4、重复执行 2、3 步，直到两指示相等，将基准元素填至指示的位置，本次划分结束
//
//参考：
//	https://www.sczyh30.com/posts/Algorithm/algorithm-quicksort/
////////////////////////////////////////////////////////////////////////
int partation(int arr[], int left, int right)
{
	int i=left, j=right;
	int tmp=arr[left];
	while(i<j)
	{
		while(i<j && tmp<=arr[j])
			j--;
		arr[i]=arr[j];
		while(i<j && tmp>=arr[i])
			i++;
		arr[j]=arr[i];
	}
	arr[i]=tmp;
	return i;
}

/////////////////////////////////////////////////////////////////////////////
//两端扫描交换
////////////////////////////////////////////////////////////////////////////
void Swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
int DeSwapPartation(int arr[], int left, int right)
{
	int i = left+1,j=right;
	int tmp = arr[left];
	while(i<=j)
	{
		while(i<=j && arr[i]<tmp)
			i++;
		while(i<=j && arr[j]>=tmp)
			j--;
		if(i<j)
		{
			Swap(arr, i, j);
		}
	}
	Swap(arr, j, left);
	return j;
}
////////////////////////////////////////////////////////////////////
//单向扫描
///////////////////////////////////////////////////////////////////
int forwardPartation(int arr[], int left, int right)
{
	int i = left, j = left+1;
	int tmp = arr[left];
	while(j<=right)
	{
		if(arr[j] < tmp)
		{
			i++;
			Swap(arr, i, j);
		}
		j++;
	}
	Swap(arr, i, left);
	return i;
}
///////////////////////////////////////////////////////////////////////////
//针对多重复元素，单向三分
//////////////////////////////////////////////////////////////////////////
void div3ScanPartation(int arr[], int left, int right, int* i, int* j)
{
	int k = left + 1, tmp = arr[left];
	*i = left;
	*j = right;
	while(k<=*j)
	{
		if(arr[k]<tmp)
		{
			Swap(arr, *i, k);
			(*i)++;
			k++;
		}else if(arr[k]>tmp){
			Swap(arr, k, *j);
			(*j)--;
		}else{
			k++;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
//双轴快排
///////////////////////////////////////////////////////////////////////////////
void dualPivotPartation(int arr[], int left, int right, int *i, int *j)
{
	if(arr[left] > arr[right])
	{
		Swap(arr, left, right);
	}	
	int pivot1 = arr[left], pivot2 = arr[right], k = left+1;
	*i = left;
	*j = right;
	LOOP_Tag: while(k < *j)
	{
		if(arr[k] <pivot1)
		{
			Swap(arr, ++(*i), k++);
		}else if(arr[k] <= pivot2)
		{
			k++;
		}else{
			while(arr[--(*j)]>pivot2){
				if(*j<= k){
					goto LOOP_Tag;
				}
			}
			if(arr[*j]<pivot1)
			{
				Swap(arr, *j, k);
				Swap(arr, ++(*i), k);
			}else{
				Swap(arr, *j, k);
			}
			k++;
		}
	}
	Swap(arr, left, *i);
	Swap(arr, right, *j);
}
void quicksort(int arr[], int left, int right)
{
	if( left>right)
		return;
	int i = 0, j = 0;
	div3ScanPartation(arr, left, right, &i, &j);
	quicksort(arr, left, i-1);
	quicksort(arr, i+1, j-1);
	quicksort(arr, j+1, right);
}


//////////////////////////////////////////////////////////////////////////////
//快排的改进主要有三种方法：
//	小数组使用插入排序、双枢轴（快速三向切分）、划分策略优化（五取样划分）
//经过优化后的快速排序算法时间复杂度可以介于N到NlgN之间，性能更优
/////////////////////////////////////////////////////////////////////////////
int main()
{
	int a[]={1,2,5,1,1,1,4,4,3};
	quicksort(a,0,8);
	for(int i=0;i<9;i++)
	{
		cout<<a[i];
	}
	cout<<endl;
	return 0;
}
