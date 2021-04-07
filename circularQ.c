#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear; 
	//front->원소가 삭제되는 끝, rear->새로운 원소가 삽입되는 끝
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ); //원형큐 메모리 해제
int isEmpty(QueueType *cQ); //원형큐가 비었는지 확인
int isFull(QueueType *cQ); //원형큐가 가득찼는지 확인
void enQueue(QueueType *cQ, element item); //원형큐에 item 삽입
void deQueue(QueueType *cQ, element* item); //원형큐에 삽입된 item 삭제
void printQ(QueueType *cQ); //원형큐에 저장된 item 출력
void debugQ(QueueType *cQ); //원형큐에 저장된 item과 rear와 front의 위치 정보 출력
element getElement(); //item을 입력하고 리턴해줌

int main(void)
{
	printf("[----- [김수영] [2020039042] -----]");
	QueueType *cQ = createQueue(); //만들어진 원형큐를 cQ 포인터에 선언
	element data; 
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //QueueType 구조체의 크기만큼 메모리 동적할당
	cQ->front = 0; 
	cQ->rear = 0; 
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //cQ에 할당받은 메모리가 없으면(=NULL) 1을 리턴
    free(cQ); //메모리 해제
    return 1;
}

element getElement()
{ 
	element item; //item이라는 변수를 element라는 자료형으로 선언
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

int isEmpty(QueueType *cQ)
{
	if((cQ->front)%MAX_QUEUE_SIZE==cQ->rear) 
	//삭제할 때마다 front를 증가시키고 front가 rear와 같은 위치에 있을 때 원형큐는 비어있는 상태
	//원형큐이기에 MAX_QUEUE_SIZE 이후에는 0으로 초기화되야 함
	//그래서 나머지 연산자(%)를 사용함 -> 매번 rear와 front의 변수를 새롭게 선언할 필요 없어짐
	{
		return 1;
	}
	return 0;
}

int isFull(QueueType *cQ)
{
   if((cQ->rear+1)%MAX_QUEUE_SIZE==cQ->front)
   //item을 추가할 때마다 rear를 증가시키고 rear가 front와 같은 위치에 있을 때 원형큐는 가득찬 상태
   //원형큐가 비어있는지 비교하는 조건과 차별점을 두기 위해 최대원소수를 MAX_QUEUE_SIZE-1로 하여 비교
   //즉, 공백을 하나 만들어 놓음
   //나머지 연산자(%)를 사용함 -> 매번 rear와 front의 변수를 새롭게 선언할 필요 없어짐
   {
	   return 1;
   }
   return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)==1) //큐가 가득차있으면 1을 반환하게 했고 가득차있으면 Queue is full! 출력
	{
		printf("Queue is full!");
	}
	else
	{
		cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE; //++rear
		cQ->queue[cQ->rear] = item; //다음 rear에 item 삽입
	}
}

void deQueue(QueueType *cQ, element *item)
{
    if(isEmpty(cQ)==1)
	{ 
		printf("Queue is empty!");
	}
	else
	{
		cQ->queue[cQ->front] = ' '; //삭제된 곳을 공백 처리
		cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE; //++front 
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //공백 하나를 만들어 놓기 위해 front와 rear에 1을 더함
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){ //i가 last와 같아질 때까지 반복
		printf("%3c", cQ->queue[i]); //순서대로 큐에 저장된 item 출력
		i = (i+1)%MAX_QUEUE_SIZE; //원형큐이기에 MAX_QUEUE_SIZE 다음에는 0으로 초기화됨
                                 //그래서 나머지 연산자(%) 사용
	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) { //i가 front와 같으면 해당 index에 front 출력
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //각 index에 해당되는 item 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //큐 상태에 맞는 rear와 front값 출력
}
