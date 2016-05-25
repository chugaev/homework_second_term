#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#define COUNT_INSTRUCTIONS 9
#define MAX_LEN_INSTRUCTION 4
#define MAX_SIZE 1048576
#define MAX_LINES 1000
#define MAX_LEN_NAME 30


typedef struct {
    int type;
    union {
        int number;
        char lbl[MAX_LEN_NAME];
    } arg;
} tinstraction;
typedef struct {
    char name[MAX_LEN_NAME];
    size_t line;
} tlabel;
typedef enum {
    LD,
    ST,
    LDC,
    ADD,
    SUB,
    CMP,
    JMP,
    BR,
    RET,
} instraction;

char *commands[COUNT_INSTRUCTIONS] = {"ld", "st", "ldc", "add", "sub", "cmp", "jmp", "br", "ret"};
int find(char *, char*, int);
int number_instruction(char*);
int read(FILE*, char*, char*, tinstraction*, tlabel*, char*, int*, int *);
int run(FILE*, tinstraction*, int*, int*, tlabel*);


int main() {
    int *data = (int*)calloc(MAX_SIZE, sizeof(int));
    int *stack = (int*)calloc(MAX_SIZE, sizeof(int));
    if (data == NULL || stack == NULL) {
        printf("Memory error\n");
        free(data);
        free(stack);
        return 0;
    }
    char str[255];
    char stInstr[MAX_LEN_NAME];
    char stArg[MAX_LEN_NAME];
    int ip = 0;
    int p_label = 0;
    tinstraction instr[MAX_LINES];
    tlabel label[MAX_LINES];
    printf("Enter name of file: ");
    char fileName[MAX_LEN_NAME];
    gets(fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        free(data);
	    free(stack);
        printf("File not found\n");
        return 0;
    }
    if (!read(file, &str, &stInstr, &instr, &label, &stArg, &ip, &p_label)) {
        free(data);
	    free(stack);
        fclose(file);
        return 0;
    }
    if (!run(file, &instr, data, stack, &label)) {
        fclose(file);
    }
    free(data);
    free(stack);
    return 0;
}
int find(char *stInstr, char *str, int i)
{
    while (str[i] == ' ') {
        i++;
    }
    if ((str[i] == ';') || (str[i] == '\0')) {
        return i;
    }
    int j = 0;
    while ((isalpha(str[i])) || (isdigit(str[i])) || (str[i] == '-')) {
        stInstr[j] = str[i];
        i++;
        j++;
    }
    stInstr[j] = '\0';
    return i;
}

int number_instruction(char *stInstr) {
    int k;
    for (k = 0; k < COUNT_INSTRUCTIONS; k++) {
        if (strcmp(stInstr, commands[k]) == 0) {
            return k;
        }
    }
}

int read(FILE *file, char *str, char *stInstr, tinstraction *instr, tlabel *label, char * stArg, int *ip, int *p_label)
{
    while (!feof(file)) {
        fgets(str, 255, file);
        int i = 0;
        while (str[i] == ' ') {
            i++;
        }
        if ((str[i] == ';') || (str[i] == '\n') || (str[i] == '\0')) {
            continue;
        }
        i = 0;
        i = find(stInstr, str, i);
        instr[*ip].type = number_instruction(stInstr);
        while (str[i] == ' ') {
            i++;
        }
        if (str[i] == ':') {
            strcpy(label[*p_label].name, stInstr);
            label[*p_label].line = *ip;
            (*p_label)++;
            i++;
            if (str[i] == '\0') {
                continue;
            }
            else {
                i = find(stInstr, str, i);
            }
        }
        while (str[i] == ' ') {
            i++;
        }
        instr[*ip].type = number_instruction(stInstr);
        i = find(stArg, str, i);
        if (isdigit(stArg[0]) || (stArg[0] == '-')) {
            instr[*ip].arg.number = atoi(stArg);
        }
        else {
            strcpy(instr[*ip].arg.lbl, stArg);
        }
        (*ip)++;
   }
   return 1;
}

int run(FILE *file, tinstraction *instr, int *data, int *stack, tlabel *label)
{
    int SP = -1;
    int i = -1;
    int arg;
    char lbl[MAX_LEN_NAME];
    int a, b, j;
    while (1) {
       i++;
       switch (instr[i].type) {
           case LD:
               SP++;
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > MAX_SIZE) || (arg > MAX_SIZE) || (arg < 0)) {
                  printf("ERROR_LD");
                  return 0;
               }
               stack[SP] = data[arg];
               break;
           case ST:
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > MAX_SIZE) || (arg > MAX_SIZE) || (arg < 0)) {
                  printf("ERROR_ST");
                  return 0;
               }
               data[arg] = stack[SP];
               SP--;
               break;
           case LDC:
               SP++;
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > MAX_SIZE)) {
                   printf("ERROR_LDC");
                   return 0;
               }
               stack[SP] = arg;
               break;
           case ADD:
               if (SP < 1) {
                   printf("ERROR_ADD");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a + b;
               break;
           case SUB:
               if (SP < 1){
                   printf("ERROR_SUB");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a - b;
               break;
           case CMP:
               if (SP < 1) {
                   printf("ERROR_CMP");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a > b ? 1 : a < b ? -1 : 0;
               break;
          case JMP:
               j = 0;
               strcpy(lbl, instr[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0) {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case BR:
               if ((stack[SP] == 0)) {
                   break;
               }
               j = 0;
               strcpy(lbl, instr[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0) {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case RET:
               printf("result = %d\n", stack[SP]);
               fclose(file);
               return 1;
        }
    }
}

