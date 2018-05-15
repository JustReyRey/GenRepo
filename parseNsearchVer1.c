#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void mergesort(int *a,int i,int j);
void merge(int *a,int i1,int j1,int i2,int j2);
void binSearch(int a[], int start, int finish,int search);
void readFile (char *filename);

int main (int argc, char *argv[]) {

	int array[] = {6,4,2,8,8,2,3,10,6,2,9,3,10};
	int size = sizeof(array)/sizeof(int);
	mergesort(array,0,size-1);
	char *fileName;
	int search;
	scanf("%d",&search);

	printf("sorted array\n");
	for (int i = 0; i < size; ++i) {
		printf("%d\n", array[i]);
	}

	binSearch(array,0,size,search);
	//readFile(argv[1]);

	return 0;
}


void mergesort(int array[],int front,int end){
    int mid;
    if(front<end)
    {
    	mid=(front+end)/2;
        mergesort(array,front,mid);       
        mergesort(array,mid+1,end);   
        merge(array,front,mid,mid+1,end);    
    }
}
 
void merge(int array[],int front1,int end1,int front2,int end2){
    int temp[500000];   
    int itator1,itator2,itator3;
    itator1=front1;    
    itator2=front2;    
    itator3=0;



    while(itator1<=end1 && itator2<=end2)    
    {
        if(array[itator1]<array[itator2]){
            temp[itator3++]=array[itator1++];
        }
        
        else{
            temp[itator3++]=array[itator2++];
        }
    }
    
    while(itator1<=end1){   
        temp[itator3++]=array[itator1++];
    }
    while(itator2<=end2){   
        temp[itator3++]=array[itator2++];
    }
        
    
    for(itator1=front1,itator2=0;itator1<=end2;itator1++,itator2++){
        array[itator1]=temp[itator2];
    }

}

void binSearch(int a[], int start, int finish, int search){

	printf("start [%d]. finish [%d].\n", start, finish);

	int mid = (start + finish) / 2;
	if (a[mid] == search){
		printf("found at index [%d]\n",mid);
	}
	else{
		if(mid == start || mid == finish){
			printf("not in array\n");
			return;
		}	
		else if (a[mid] > search){
			binSearch(a,start,mid,search);
		}
		else if(a[mid] < search){
			binSearch(a,mid,finish,search);
		}	
	}
}

//unsortedNumbers.txt
void readFile (char *filename){

	FILE *file;
	file = fopen(filename,"r");

	if (file == NULL){
		printf("Error Opening File\n");
		exit(1);
	}

	char sentence[400];
	char *temp;
	int *array = malloc(sizeof(int));
	int size = 0;
	

	while (fgets(sentence,400,file) != NULL){
		if (strcmp(sentence,"\n") != 0){
			temp = strtok(sentence," \n\r\t");
			while (temp != NULL){
				size++;
				array = realloc(array,size * sizeof(int));
				array[size-1] = atoi(temp);
				temp = strtok(NULL," \n\r\t");
			}
		}
	}

	printf(" array\n");
	for (int i = 0; i < size; ++i) {
		printf("%d\n", array[i]);
	}
	mergesort(array,0,size-1);

	printf("\n\nsorted array\n");
	for (int i = 0; i < size; ++i) {
		printf("%d\n", array[i]);
	}




}
