#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sumTwo.h"
int * twoSum(int * nums,int numSize,int target);

int main(){
    int num[]={2,7,11,15};
    int target=2; 
    int numSize=4;
    int * result=twoSum(num,numSize,target);
    printf("%d\n",result[0]);
    printf("%d\n",result[1]);
    free(result);
    result=NULL;
    return EXIT_SUCCESS;
}

int* twoSum(int* nums, int numsSize, int target)
{
	if (numsSize < 2) return NULL;
	int *res = (int *)malloc(sizeof(int) * 2);
    if (res==NULL){
        fprintf(stderr,"no memory,aborting.\n");
        exit(0);
    }
    res[0]=-1;
    res[1]=-1;
	//最好算一下初始容量，提高效率
	int initialCapacity = (int)((float)numsSize/ 0.75F + 1.0F);
	HashMapPointer map = NULL;
	map=HashMap_Init(initialCapacity);

	for (int i = 0; i < numsSize; i++) {
		//在map中寻找余数
		if (!HashMap_Contains(map,target - nums[i])) {
			HashMap_Put(map,nums[i], i);
		}
		else {
			res[0] = HashMap_GetValue(map,target - nums[i]);
			res[1] = i;
			break;
		}
	}
	HashMap_Free(map);
	return res;
}