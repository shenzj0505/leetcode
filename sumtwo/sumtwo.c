#include <stdio.h>
#include <stdlib.h>
int * twoSum(int * nums,int numSize,int target,int * returnSize);

int main(){
int num[]={2,7,11,15};
int target=1; 
int numSize=4;
int returnSizeValue=0;
int * returnSize=&returnSizeValue;
int * result=twoSum(num,numSize,target,returnSize);
printf("%d\n",result[0]);
printf("%d\n",result[1]);
free(result);
result=NULL;
return EXIT_SUCCESS;

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int* res = malloc(sizeof(int) * 2);
    if (res==NULL){
        fprintf(stderr,"no memory, aborting.\n");
        exit(0);
    }
    for (int tmp=0;tmp<2;tmp++){    //initialise the res heap memory
        *(res+tmp)=-1;
    }
    for(int i = 0; i < numsSize-1; i++) {
        for(int j = i + 1; j < numsSize; j++) {
            if(nums[i] + nums [j] == target) {
                res[0] = i;
                res[1] = j;
                *returnSize = 2;
            }
        }       
    }
    return res;
}

