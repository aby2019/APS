#include<bits/stdc++.h>
using namespace std;
struct node 
{
	int data;
	int index;//index of file from which minimum element is taken;
};
void merge(vector <int> &arr, int low, int mid, int high)
{
    int temp[high + 1],i= low,j= mid + 1,k = 0;

    while (i<=mid&&j<=high)
    {
        if (arr[i]<=arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }
    while (i<=mid)
        temp[k++]=arr[i++];
    while (j<=high)
        temp[k++]=arr[j++];
    k--;
    while (k>=0)
    {
        arr[k+low]=temp[k];
        k--;
    }
}

void mergeSort(vector <int> &arr, int low, int high)
{
    int mid;

    if (low<high)
    {
        mid=(low+high)/2;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
}
int h_size;
node *aux_heap=new node[100];
void heapify(int inx)
{
		//cout<<"i="<<inx<<endl;
		int l = 2*inx+1; 
	    int r = 2*inx+2; 
	    int smallest = inx; 
	    if ((l<h_size)&&(aux_heap[l].data < aux_heap[inx].data)) 
	        smallest = l; 
	    if ((r<h_size)&&(aux_heap[r].data < aux_heap[smallest].data)) 
	        smallest = r; 
	    if (smallest != inx) 
	    { 
	       	node temp=aux_heap[inx];
	    	aux_heap[inx]=aux_heap[smallest];
	    	aux_heap[smallest]=temp;
	        heapify(smallest); 
	    } 
}
node build_heap(int x)
{
	//cout<<"heapsize="<<x<<endl;
	h_size=x;
	//cout<<"hi";
	//cout<<h_size<<endl;
	for(int i=(h_size/2)-1;i>=0;i--)
		{	
			heapify(i);
		}	
}

int main(int argc,char *argv[])
{
		FILE * ifp;
	int n=0;//elements
	char input[100];
	snprintf(input, sizeof(input), "%s",argv[1]);
	cout<<input<<endl;
	ifp=fopen(input,"r");
	int inx;
	int total;
	int k;
	while(fscanf(ifp,"%d",&k)!=-1)
	{
		n++;
		// if(i==n-1)
		// fprintf(ifp, "%d",rand()%1000+1);
		// else
		// fprintf(ifp, "%d\n",rand()%1000+1);

	} 
	fclose(ifp);
	cout<<n<<endl;
	inx=n;
	total=n;
	int b_point;//break point;
	b_point=1000000;
	vector <int> arr;
	int temp,count=0;
	ifp=fopen(input,"r");
	FILE *ofp[10000];//list of output file pointers;
	int ofp_inx=0;//to append at the end(file name)&&index of output file pointer list
	char output_file[100];
	snprintf(output_file, sizeof(output_file), "%d", ofp_inx);
	ofp[ofp_inx]=fopen(output_file,"w");
	//for(int i=0;i<total;i++)
	while(fscanf(ifp,"%d\n",&temp)==1)
	{		
		arr.push_back(temp);
		// if(count==b_point-1)
		// fprintf(ofp[ofp_inx], "%d",temp);
		// else
		// fprintf(ofp[ofp_inx], "%d\n",temp);
		count++;
		if(count==b_point||count==total)
		{
			total=total-b_point;
			mergeSort(arr,0,arr.size()-1);	
			for(int i=0;i<arr.size();i++)
			{	
				if(i==arr.size()-1)
				fprintf(ofp[ofp_inx], "%d",arr[i]);
				else
				fprintf(ofp[ofp_inx], "%d\n",arr[i]);
			}
			arr.clear();
			count=0;
			//fclose(ofp[ofp_inx]);
			if(
				feof(ifp)!=0)
				break;
			ofp_inx++;
			snprintf(output_file, sizeof(output_file), "%d", ofp_inx);
			//cout<<output_file;
			ofp[ofp_inx]=fopen(output_file,"w");

		}
	}
	//fclose(ofp[ofp_inx]);
	
	fclose(ifp);
	int file_count=ofp_inx+1;//total file count
	int h_size=file_count;
	//cout<<"h_size="<<h_size<<endl;
	char output[100];
	
	snprintf(output, sizeof(output), "%s", argv[2]);

	
	ofp_inx=0;
	//cout<<file_count<<endl;
	snprintf(output_file, sizeof(output_file), "%d", ofp_inx);
	//cout<<output_file;
	for(int i=0;i<file_count;i++)
	{
		snprintf(output_file, sizeof(output_file), "%d", i);
		fclose(ofp[i]);
		
	}
	for(int i=0;i<file_count;i++)
	{
		snprintf(output_file, sizeof(output_file), "%d", i);
		ofp[i]=fopen(output_file,"r");
		
	}

	FILE *result=fopen(output,"w");
	
	for(int i=0;i<file_count;i++)
	{		
			fscanf(ofp[i],"%d\n",&temp);
			//cout<<temp<<endl;
			aux_heap[i].data=temp;
			aux_heap[i].index=i;
	}

	build_heap(file_count);
	inx=0;
	//no of files currently closed
		// int heap_data=aux_heap[0].data;
		// int heap_index=aux_heap[0].index;
		// fscanf(ofp[heap_index],"%d\n",&temp);
		// if(feof(ofp[heap_index])!=0)
		// 	{
		// 		inx++;
		// 		aux_heap[0].data=INT_MAX;
		// 		heapify(0);
		// 	}
	int heap_data;
	int heap_index;
	int last_element;
	while(inx!=file_count)
	{

		heap_data=aux_heap[0].data;
		heap_index=aux_heap[0].index;
		// cout<<heap_data<<endl;
		fprintf(result, "%d\n",heap_data);
		fscanf(ofp[heap_index],"%d\n",&temp);
		
		if(feof(ofp[heap_index])!=0)
			{
				inx++;
				last_element=temp;
				temp=INT_MAX;
			}
		aux_heap[0].data=temp;
		heapify(0);
	}
	fprintf(result, "%d",last_element);


	for(int i=0;i<file_count;i++)
	{
		fclose(ofp[i]);
		snprintf(output_file, sizeof(output_file), "%d", i);
		remove(output_file);
	}
	fclose(result);

}