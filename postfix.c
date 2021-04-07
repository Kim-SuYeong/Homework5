#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

typedef enum{
	lparen = 0,  // 왼쪽 괄호
	rparen = 9,  // 오른쪽 괄호
	times = 7,   // 곱셈
	divide = 6,  //나눗셈
	plus = 5,    //더하기
	minus = 4,   //빼기
	operand = 1 //피연산자(숫자)
} precedence; //이 구조체는 연산의 우선순위를 따지기 위해 만들어 놓은 구조체임(숫자가 높을수록 우선순위 높음)

char infixExp[MAX_EXPRESSION_SIZE]; 	// infix expression을 저장하는 배열 
char postfixExp[MAX_EXPRESSION_SIZE];	// postfix로 변경된 문자열을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];	// postfix로 변환을 위해 필요한 스택 
int evalStack[MAX_STACK_SIZE];	// 계산을 위해 필요한 스택 	

int postfixStackTop = -1;  //postfixStack용 top
int evalStackTop = -1;	  //evalStack용 top

int evalResult = 0;	   //계산 결과를 저장

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	printf("[----- [김수영] [2020039042] -----]");
    char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //postfix 스택에 push 후에 index 증가
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //초기상태면 공백 리턴
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //초기상태가 아니면 x에 스택값을 저장 후 postfixStackTop 감소
    }
    return x; //x 리턴
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //postfix 스택에 push 후에 index 증가
}

int evalPop()
{
    if(evalStackTop == -1) //초기상태면 -1 리턴
        return -1;
    else
        return evalStack[evalStackTop--]; //초기상태가 아니면 스택값을 리턴 후 evalStackTop 감소
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //infix 형식의 계산식을 입력함
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen; // '('이면 0 리턴
	case ')' : return rparen; // ')'이면 9 리턴
	case '+' : return plus; // '+'이면 5 리턴
	case '-' : return minus; // '-'이면 4 리턴
	case '/' : return divide; // '/'이면 6 리턴
	case '*' : return times; // '*'이면 7 리턴
	default : return operand; // 숫자를 입력하면 1 리턴
	}
}

precedence getPriority(char x)
{
	return getToken(x); //각 연산자에 해당하는 리턴값을 받아서 리턴해줌
}

void charCat(char* c)
{
	if (postfixExp == '\0') //만약 postfixExp에 저장된 값이 공백이면
		strncpy(postfixExp, c, 1); //c를 postfixExp로 1번 복사함
	else						
		strncat(postfixExp, c, 1); //공백이 아니면 c 1개를 postfixExp 뒤에 이어붙임
}

void toPostfix()
{
	
	char *exp = infixExp;
	char x; 
	int i=0;
	
	while(*(exp+i) != '\0')
	{
		if(*(exp+i) > '0' && *(exp+i) < '9') //숫자가 입력되었을 시의 경우이며 0~9까지만 입력받게 함
		{
			postfixPush(*(exp+i));
		}
		else
		{
			if(*(exp+i) == ')')
			{
				do
				{
					postfixExp[i++] = postfixPop();
				} while (postfixExp[i-1]!='(');
					i--;
					continue;
			}
			while(getPriority(*exp)<=getPriority(postfixStack[postfixStackTop]))
			{
				postfixExp[i++] = postfixPop();
			}
			 postfixPush(*(exp+(i++)));
		}
		
	do
	{
		postfixExp[i++] = postfixPop();
	} while (postfixExp[i-1]!='\0');
	exp++;
}

	

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); //postfix 형식으로 바뀐 계산식을 입력받음

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //infix 표현을 저장하는 배열의 처음을 공백으로 저장
	postfixExp[0] = '\0'; //postfix 표현을 저장하는 배열의 처음을 공백으로 저장

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //for문을 통해 postfixStack에 저장된 값들을 공백으로 하나씩 저장
         
	postfixStackTop = -1; 
	evalStackTop = -1;
	evalResult = 0;
	//postfix의 스택의 탑과 계산에 필요한 스택의 탑, 그리고 계산 결과값을 초기상태로 초기화
}

void evaluation()
{
	int op1, op2;
	for(int i=0; postfixExp[i]!='\0'; i++)
	{ 
		if(getToken(postfixExp[i])==1)
		{
			evalPush(postfixExp[i]-'0');
		}
		else
		{
			op1=evalPop();
			op2=evalPop();
			switch(getToken(postfixExp[i]))
			{
				case 5: evalResult = op1 + op2;
				break;
				case 4: evalResult = op1 - op2;
				break;
				case 6: evalResult = op1 / op2;
				break;
				case 7: evalResult = op1 * op2;
				break;
			}
			evalPush(evalResult);
		}
	}
}
