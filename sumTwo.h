typedef struct HashMap_Class * HashMapPointer;
HashMapPointer HashMap_Init(int initialCapacity);
void HashMap_Put(HashMapPointer map,int key,int value);
bool HashMap_Contains(HashMapPointer map, int key);
void HashMap_Free(HashMapPointer map);
int HashMap_GetValue(HashMapPointer map,int key);