#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "sumTwo.h"

typedef struct Node_Class Node;
struct Node_Class {
	int key;
	int value;
	struct Node_Class *next;
};


struct HashMap_Class
{
	int threshold; //桶个数
	struct Node_Class** table; //桶列表
};

/*
 * 初始化HashMap
 * @initialCapacity 初始容量，也就是HashMap中桶的个数，一般为 (预估最大个数)/0.75f+1
 */
HashMapPointer HashMap_Init(int initialCapacity) {
	HashMapPointer map=malloc(sizeof(struct HashMap_Class)*1);
	if (map==NULL){
		fprintf(stderr,"no memory, aborting.\n");
		exit(0);
	}
	int threshold = 1;
	//自动填充为大于initialCapacity的2的倍数值
	while (threshold < initialCapacity)
		threshold <<= 1;
	map->threshold = threshold;
	Node** table = malloc(sizeof(Node*)*threshold);
    if (table==NULL){
        fprintf(stderr,"no memory, aborting.\n");
        exit(0);
    }
    for (int tmp=0;tmp<threshold;tmp++){
        table[tmp]=NULL;
    }
	map->table = table;
	return map;
}

/*
 * HashMap的Hash值计算，暂时是就是自己
 * 
 */
int HashMap_HashCode(HashMapPointer map, int key) {
	return key;
}

/*
 * HashMap的put方法，首先将产生的Hash值做高低位异或，然后再取余，产生的值小于threshold
 * 产生的值作为桶的下标，找到对应的桶
 * 遍历桶中的链表，一个个比较key值，key相同则替换value值，如果没有key就在桶最后面加上一个Node
 *
 */
void HashMap_Put(HashMapPointer map,int key,int value) {
	if (map==NULL){
		printf("HashMap_Put: no Hash Map initialised.\n");
		return;
	}
	Node *p;
	Node *tail;
	unsigned int hash = (unsigned int)HashMap_HashCode(map, key);
	//得到Hash值后将高低位交互运算下
	hash= hash ^ (hash >> 16);
	//最后取余数
	hash=hash&(map->threshold - 1);
	p = map->table[hash];
	//如果桶是空的就新建Node放入桶中
	if (p == NULL) {
		Node* node = malloc(sizeof(Node));
        if (node==NULL){
            fprintf(stderr,"no memory, aborting.\n");
            exit(0);
        }
		node->key = key;
		node->value = value;
		node->next = NULL;
		map->table[hash] = node;
	}else {
        int found=0;
		while (p != NULL && !found) {
			//如果找到key就替换
			if (p->key == key) {
				p->value = value;
				found=1;
			}
            else{
			    tail = p;
			    p = p->next;
			    //找到末尾也找不到key，就新建Node添加到最后
			    if (p == NULL) {
				    Node* node = malloc(sizeof(Node));
					if (node==NULL){
						fprintf(stderr,"no memory, aborting.\n");
						exit(0);
					}
				    node->key = key;
				    node->value = value;
				    node->next = NULL;
				    tail->next = node;
			    }
            }
		}
	}
}

/*
 * HashMap的getNode方法，与put方法差不多，只是找到对应的key之后直接返回Node,其他时候返回NULL
 */
Node* HashMap_GetNode(HashMapPointer map, int key) {
	if (map==NULL){
		printf("HashMap_GetNode: no Hash Map initialised.\n");
		return NULL;
	}
	Node *p;
	unsigned int hash = (unsigned int)HashMap_HashCode(map, key);
	hash = hash ^ (hash >> 16);
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	while(p!=NULL){
        if (p->key==key){
            return p;
        }
        else{
            p=p->next;
        }
    }
    return NULL;
}

int HashMap_GetValue(HashMapPointer map,int key){
	if (map==NULL){
		printf("HashMap_GetValue: no Hash Map initialised.\n");
		return INT_MAX;
	}
	Node *p=NULL;
	int ret=INT_MAX;
	p=HashMap_GetNode(map,key);
	if (p!=NULL){
		ret=p->value;
	}
	return ret;
}

bool HashMap_Contains(HashMapPointer map, int key) {
	if (map==NULL){
		printf("HashMap_Contains: no Hash Map initialised.\n");
		return false;
	}
	if (HashMap_GetNode(map, key) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void HashMap_Free(HashMapPointer map) {
	if (map==NULL){
		printf("HashMap_Free: no Hash Map initialised.\n");
		return;
	}
	for (int i = 0; i < map->threshold; i++) {
		Node *p = map->table[i];
		while (p  != NULL) {
			Node *temp = p;
			p = p->next;
			free(temp);
            temp=NULL;
		}
	}
	free(map->table);
    map->table=NULL;
	free(map);
    map=NULL;
}

