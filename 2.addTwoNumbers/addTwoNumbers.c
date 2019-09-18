/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode * initNode(int value){
    struct ListNode* node=malloc(sizeof(struct ListNode));
    if (node==NULL){
        fprintf(stderr,"no memory, aborting.\n");
        exit(0);
    }
    node->val=value;
    node->next=NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode * ret=NULL;
    if(l1==NULL || l2==NULL){
        printf("l1 or l2 is not initialised.\n");
        return ret;
    }
    ret=initNode(0);
    struct ListNode * tmpret;
    struct ListNode * previous=NULL;
    struct ListNode * tmp1;
    struct ListNode * tmp2;
    tmpret=ret;
    tmp1=l1;
    tmp2=l2;
    while(tmp1!=NULL && tmp2!=NULL){
        int sum=0;
        int sumLow=0;int sumHigh=0;
        sum=tmpret->val+tmp1->val+tmp2->val;
        sumLow=sum%10;  //低位
        sumHigh=sum/10; //高位
        
        tmpret->val=sumLow;
        if (sumHigh!=0){//进位
            tmpret->next=initNode(sumHigh);
        }
        tmp1=tmp1->next;
        tmp2=tmp2->next;
        if (tmp1!=NULL && tmp2!=NULL && sumHigh==0){
            tmpret->next=initNode(0);
        }
        previous=tmpret;
        tmpret=tmpret->next;
    }
    
    if (tmp1==NULL && tmp2==NULL){
        ;
    }
    else if (tmp1==NULL && tmp2!=NULL){
        while(tmp2!=NULL){
            int sum=0;
            int sumLow=0;int sumHigh=0;
            if (tmpret==NULL){
                tmpret=initNode(0);
                previous->next=tmpret;
            }
            sum=tmpret->val+tmp2->val;
            sumLow=sum%10;
            sumHigh=sum/10;
            tmpret->val=sumLow;
            if (sumHigh!=0){
                tmpret->next=initNode(sumHigh);
            }
            previous=tmpret;
            tmpret=tmpret->next;
            tmp2=tmp2->next;
        }
    }
    else if (tmp1!=NULL && tmp2==NULL){
        while(tmp1!=NULL){
            int sum=0;
            int sumLow=0;int sumHigh=0;
            if (tmpret==NULL){
                tmpret=initNode(0);
                previous->next=tmpret;
            }
            sum=tmpret->val+tmp1->val;
            sumLow=sum%10;
            sumHigh=sum/10;
            tmpret->val=sumLow;
            if (sumHigh!=0){
                tmpret->next=initNode(sumHigh);
            }
            previous=tmpret;
            tmpret=tmpret->next;
            tmp1=tmp1->next;
        }
    }
    
    /*
    tmpret=ret;
    while (tmpret!=NULL){
        printf("%d ",tmpret->val);
        tmpret=tmpret->next;
    }*/
    return ret;
}


