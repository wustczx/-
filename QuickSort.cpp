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
		if(i<j)
		{
			arr[i]=arr[j];
			i++;
		}
		while(i<j && tmp>=arr[i])
			i++;
		if(i<j)
		{
			arr[j]=arr[i];
			j--;
		}
	}
	arr[i]=tmp;
	return i;
}
void quicksort(int arr[], int left, int right)
{
	if( left>right)
		return;
	int index=partation(arr, left, right);
	quicksort(arr, left, index-1);
	quicksort(arr, index+1, right);
}
int main()
{
	int a[]={1,2,5,1,4,3};
	quicksort(a,0,5);
	for(int i=0;i<6;i++)
	{
		cout<<a[i];
	}
	cout<<endl;
	return 0;
}
