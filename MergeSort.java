//时间复杂度为O(nlog2n) 空间复杂度为O(n) 属于稳定排序算法
public class MergeSort {
	public static void Merge(int[] arr, int begin, int mid, int end){
		int i=begin,j=mid+1,k=0;
		int[] tmp=new int[end-begin+1];
		while(i<=mid && j<=end){
			if(arr[i]<= arr[j])
				tmp[k++]=arr[i++];
			else
				tmp[k++]=arr[j++];
		}
		while(i<=mid)
			tmp[k++]=arr[i++];
		while(j<=end)
			tmp[k++]=arr[j++];
		for(k=0,i=begin;i<=end;)
			arr[i++]=tmp[k++];
	}
	public static void MergeAll(int[] arr,int step,int len){
		int i=0;
		//归并长度为step的相邻两个子序列
		for(;i+2*step-1<len;i+=2*step){
			Merge(arr, i, i+step-1, i+2*step-1);
		}
		//归并最后两个子序列，其中后一个少于step个数据
		if(i+step-1<len)
			Merge(arr, i, i+step-1, len-1);
	}
	public static void mergeSort(int[] arr){
		for(int step=1;step<arr.length;step*=2)
			MergeAll(arr, step, arr.length);
	}
	
	public static void main(String[] args) {
		int[] arr={8,2,1,5,3,7,4,9,0,6};
		MergeSort.mergeSort(arr);
		for(int i=0;i<arr.length;++i)
			System.out.print(arr[i]);
	}
}
