
/*evaluation of expression
a+(b/c)*e

i/p:
2+(5/3)*3
253/3*+
Ans 5
*/
/***
 * @def only binary operations are allowed
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EXPLEN 20
#define STKLEN 30

int stack[STKLEN];
int top=-1;
char stackExp[STKLEN];
int topE = -1;

int isOperator(char ch){
    if(ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

void push(int d){
    if(top<STKLEN-1){
        stack[++top] = d;
    }else{
        printf("OVERFLOW\n");
    }
}

int pop(){
    if(top!=-1){
        int t = stack[top];
        top--;
        return t;
    }
    printf("UNDERFLOW\n");
}

void pushE(char c){
    if(topE < STKLEN-1){
        stackExp[++topE] = c;
    }else{
        printf("OVERFLOW\n");
    }
}

char popE(){
    if(topE!=-1){
        char c = stackExp[topE];
        topE--;
        return c;
    }
    return '#';
}

char peekE(){
    if(topE!=-1){
        return stackExp[topE];
    }
    return '#';
}

int OrderOfPrecendence(char ch){
    switch(ch){
        case '^': return 1;
        case '*': return 2;
        case '/': return 2;
        case '+': return 3;
        case '-': return 3;
    }
}

int isValidExpression(char *str){
    // if the string entered by user is more than 
    // the length of arr assigned
    if(*(str+EXPLEN-1) == '\0'){
        //valid
        int noBrackets=0;
        int k=0;
        while(*(str+k)){
            if(*(str+k) == '('){
                noBrackets -= 1;
            }
            else if(*(str+k) == ')'){
                noBrackets += 1;
            }
            k++;
        }
        return (!noBrackets)? 1 : 0;
    }
    else{
        return 0;
    }
}

int main(){
    char exp[EXPLEN]={0};
    printf("Enter a valid Expression: ");
    scanf("%s",exp);
    if(!isValidExpression(exp))
    {
        fprintf(stderr, "INVALID! expression\n");
        exit(EXIT_FAILURE);
    }
    printf("Inorder expression: %s\n",exp);

    char expPostfix[EXPLEN]={0};
    ///// convert to postfix /////
    // if operand then print
    // if the operator is * + ) ( -
    int k=-1;
    int i=0;
    while(exp[i]){
        if(!isOperator(exp[i])){
            //then perform operations
            if(exp[i]=='('){
                pushE(exp[i]);
                i++;
                continue;
            }
            if(exp[i]==')'){
                //loop through till we get the '('
                while(peekE() != '#' && peekE()!='('){
                    expPostfix[++k] = popE();
                }
                popE();// removed '('
                i++;
                continue;
            }
            int op1 = OrderOfPrecendence(exp[i]);
            int op2 = OrderOfPrecendence(peekE());
            if(op1 < op2){
                // higher precedence simplly push it
                pushE(exp[i]);
            }else if(op1 > op2){
                // comming operator is of lower precedence
                // then pop the top element and then check whether it is higher of not
                while(topE!=-1 && peekE()!='(' && op1 > OrderOfPrecendence(peekE())){
                    expPostfix[++k] = popE();
                }
                if(peekE() == '('){
                    i++;
                    continue;
                }
                pushE(exp[i]);
            }else{
                //associavity
                expPostfix[++k] = popE();
                // check for pushing it
            }
        }
        else{
            // printf("\t\t\toperand: \t%c\n",exp[i]);
            //oprand is just pushed
            expPostfix[++k] = exp[i];
        }
        // printf("iteration val -> %c || %s\n",exp[i], expPostfix);
        i++;
    }
    while(peekE()!='#'){
        expPostfix[++k] = popE();
    }
    printf("postfix expression: %s\n",expPostfix);

    ///// Evaluation /////
    int A=0,
        B=0;
    int res=0;
    for(int i=0;expPostfix[i];i++){
        if(isOperator(expPostfix[i]))
        {
            push((int)(expPostfix[i]-'0'));
        }
        else
        {
            A = pop();
            B = pop();
            // printf("A: %d\n",A);
            // printf("B: %d\n",B);
            switch(expPostfix[i]){
                case '^': push(((int)(pow(B, A) + 0.5)));break;
                case '*': push(B * A); break;
                case '/': push(B / A);break;
                case '+': push(B + A);break;
                case '-': push(B - A);break;
            }
            // printf("curr res: %d\n",res);
            // printf("operator: %c\n",exp[i]);
        }
    }
    /***
     * Linux
     * On Linux, you can change the current foreground and background color by writing special character sequences into the output. Write the ESC escape character (octal "\033", hex \x1b), followed by an opening square bracket [. The color definition will follow next, termniated by a lowercase m.
     * The color definition is a series of numbers, separated by semicolons. In order to make the text color red (number 31), you can write "\033[31m" which will make any following output red. If you want yellow text (33) on blue background (44), you write "\033[31;44m". To reset everything back to the default colors, you write "\033[0m".
     */
    printf("\033[33;44mResult: %d\n",pop());
    printf("\033[0m");
    return 0;
}