/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("[-----[LeeSeungHun] [2023041045]-----]");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf("  %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //insert할 node 구조체 메모리 할당
	node->key = key; //입력받은 key 값을 insert할 node의 key 값에 넣기

	node->link = h->first; //insert할 node의 link에 headnode의 first가 가리키던 값 넣기 
	h->first = node; //headnode의 first가 insert할 node를 가리킴

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;
	newNode->link = NULL;
	if (h->first == NULL || key < h->first->key) //리스트가 비어있거나 key가 첫번째 노드의 key보다 작을 경우
	{
		newNode->link = h->first; //새로운 노드를 첫 번째로 만들고, 기존 첫번째 노드는 두 번째로 이동
		h->first = newNode;
	}
	else {
		listNode* current = h->first; //첫번째 노드를 currentnode라고 지정
		while (current->link != NULL && current->link->key < key) //currentnode의 link가 NULL이 아니고 currentnode의 다음 node의 key값이 새로운 노드의 key값보다 크면 빠져나옴
		{
			current = current->link; //currentnode를 다음 node로 지정
		}
		newNode->link = current->link; //새로운 노드에 currentnode의 link 넣기
		current->link = newNode; //currentnode의 link에는 새로운노드값 넣기
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;
	newNode->link = NULL;

	if (h->first == NULL) //첫번째값이 비어있는 경우
	{ 
		h->first = newNode; //첫번째값에 새로운노드 넣기
	}
	else {
		listNode* current = h->first;
		while (current->link != NULL) //리스트의 끝을 찾음
		{ 
			current = current->link; //currentnode를 다음 node로 지정
		}
		current->link = newNode; //새로운 노드를 마지막에 추가
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) //리스트가 비어있는 경우
	{ 
		printf("리스트가 비어있습니다.\n");
		return -1;
	}
	listNode* temp = h->first;
	h->first = h->first->link; //첫번째 노드를 삭제하고 두 번째 노드를 첫 번째로 설정
	free(temp); //삭제한 노드 메모리 해제
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) //리스트가 비어있는 경우
	{ 
		printf("리스트가 비어있습니다.\n");
		return -1;
	}
	listNode* current = h->first; //첫번째 노드를 현재값에 넣음
	listNode* prev = NULL; //prevnode 초기화

	while (current != NULL && current->key != key) //삭제할 노드를 찾음
	{ 
		prev = current; //prevnode에 currentnode 넣기
		current = current->link; //다음노드로 이동
	}

	if (current == NULL) //삭제할 노드가 없는 경우
	{ 
		printf("삭제할 노드가 없습니다.\n");
		return -1;
	}

	if (prev == NULL) //첫번째 노드를 삭제하는 경우
	{ 
		h->first = current->link; //첫번째 노드에 다음노드값 넣기
	}
	else {
		prev->link = current->link; //prevnode link에 currentnode link 넣기
	}
	free(current); //삭제한 노드 메모리 해제
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) //리스트가 비어있는 경우
	{ 
		printf("리스트가 비어있습니다.\n");
		return -1;
	}
	listNode* current = h->first; //첫번째 노드를 currentnode에 넣음
	listNode* prev = NULL; //prevnode 초기화

	while (current->link != NULL) //마지막 노드의 이전 노드까지 이동
	{ 
		prev = current; //prevnode에 currentnode 넣기
		current = current->link; //다음노드로 이동
	}

	if (prev == NULL) //리스트에 노드가 하나인 경우
	{ 
		h->first = NULL;
	}
	else {
		prev->link = NULL; //마지막 노드 삭제
	}

	free(current); //삭제한 노드 메모리 해제
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* prev = NULL;
	listNode* current = h->first;
	listNode* next = NULL;

	while (current != NULL) {
		next = current->link; //다음 노드 저장
		current->link = prev; //현재 노드의 링크를 이전 노드로 설정
		prev = current; //이전 노드를 현재 노드로 변경
		current = next; // 현재 노드를 다음 노드로 변경
	}

	h->first = prev; //리스트의 헤드를 역순으로 된 리스트의 헤드로 변경
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

