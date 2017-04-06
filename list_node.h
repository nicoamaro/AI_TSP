
typedef struct listNode{
  int idCurrentCity;
  int totalCost;
  int father;

  struct listNode* nextListItem;
  struct listNode* prevListItem;
} listNode;

bool nextElementIs(listNode* element, listNode* next_element);
bool prevElementIs(listNode* element, listNode* prev_element);
listNode* setNextElement(listNode* element, listNode* next_element);
listNode* setPrevElement(listNode* element, listNode* prev_element);
void putItem(listNode* element, listNode* prev_element);
listNode* popItem(listNode* prev_element);
listNode* createItem(void);
listNode* newList(unsigned int list_len);
