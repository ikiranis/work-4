#include <stdio.h> 
#include <stdlib.h> 
/* ��������� C ��� ���������� ��� ������ (Stack) �� �� ����� ������������ ������ */
/* ��� ������� ��� ����� ��������� ���� �� �����. */
/* � ������ �������� ��� ����� ���� ������� ���� ���10 */ 
/* � ������ ����������� ���� ������������ ������ */
/* �� ��������� �������� ��� �����������: */
/* ��� construct ��� ����������� �� ������ */ 
/* ��� isEmpty ��� ������� �� � ������ ����� ����� */
/* ��� push ��� ������� �������� ��� ������ */
/* T�� pop ��� ������ �������� ��� �� ������ ��� ��� top ��� ��� ����� �� �������� ��� ������� */
/* T�� ���������� ��������� Insert_Sort ��� ��������� ���������� ��� ������ */ 
/* ��� ���������� ��������� sort_Stack ��� ����� ��� Insert_Sort ��� �� ����������� �� ������ */
/* � Insert_Sort ����� ��� ���� ���� ���������� ���������� ��� ����� ���� ��������� �� ���������� */
/* ��� ���������� ��������� show � ����� ��������� ��� �� �������� ��� ������� */  
/* ��� st_delete ��� ������������� ��� ���� ������ ��� ���� ��������� ��� �� ������ */

struct stack 
{ 
    int grade; 
    struct stack *next; 
}; 
void construct(struct stack **); 
int isEmpty(struct stack *); 
void push(struct stack **, int x); 
int pop(struct stack **); 
int top(struct stack *); 
void Insert_Sort(struct stack **, int x); 
void sort_Stack(struct stack **); 
void show(struct stack *); 
void st_delete(struct stack **);

/* ������������ ���� ������ ������� */
void construct(struct stack **head) 
{ 
    *head = NULL; 
} 
  
/* ��������� ��� ������� �� � ������ ����� ����� */
int isEmpty(struct stack *head) 
{ 
    if (head == NULL) 
        return 1; 
    return 0; 
} 
  
/* ��������� ��� ������� �������� ���� ��� ������ */
void push(struct stack **head, int vath) 
{ 
    struct stack *p = (struct stack *)malloc(sizeof(*p)); 
  
    if (p == NULL) 
    { 
        fprintf(stderr, "��� ������� ��������� �����\n"); 
        return; 
    }  
    p->grade = vath; 
    p->next = *head; 
    *head = p; 
} 
  
/* ��������� ��� ������� ��� �������� ��� �� ������ */ 
int pop(struct stack **head) 
{ 
    int x; 
    struct stack *temp; 
  
    x = (*head)->grade; 
    temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
  
    return x; 
} 
  
/* ��������� ��� ���������� �� �������� ��� ������� ��� ������� */
int top(struct stack *head) 
{ 
    return (head->grade); 
} 
  
/* ���������� ��������� ����������� ������� Insert_Sort */
void Insert_Sort(struct stack **head, int vath) 
{ 
/* ���� �� ����� �� ��������� ������ ������ C ��� �� �������� ��� ���������� Insert_Sort */
/* �������� �� ��� ���� ������ */

/* ��� � ������ ����� ����� � ��� � ���� ���� �������� ������ ����� ����������� */
/* ��� ����� ��� ������ ��� �������, ������� ����������� ��� ����� ���� �������� ��� ������ */

/* ������ � ��������� �� �a��� ���������� �o� ����� ��� (��������� Insert_Sort) */ 
/* ���� ��������� ����� �� �������� ��� ������� */ 
/* ���� ��� ���� ��� ������ �� �������� ��� ������� ��� ����� ��������� ���� */	
	 
} 
  
/* ���������� ��������� ��� �������� ��� ���������� ������� ��� ����� ��� ���������� Insert_Sort */
/* ��� �� ������������� �� ��� ����� ���������� ���� ��� ���� ���������!! */
void sort_Stack(struct stack **head) 
{ 
/* ������ ������ C ��� �� �������� ��� ���������� �������� ��� �������� �� ��������� Insert_Sort.*/
/* ��������� �� ��� ���� ������*/
/* �� � ������ ��� ����� ����� */ 
/* �������� �� �������� ��� ������� */
/* ���������� ��� �������� ������ �������� ���������� ��� ����� ��� */
/* ���������� ���� �� �������� ��� ������� ���� ������������ ������ */
/* ����� ��� Insert_Sort */ 
    
} 
  
/* ���������� ��������� ��� ��� �������� ��� ��������� ��� ������� */ 
void show(struct stack *head) 
{ 
/* ��� ������ ������ C ��� �� �������� �� ��������� show ��� ��� �������� ��� ��������� ��� ������� */
/* � ��������� ����� ���������� ��� ��������� �� �������� ��� ������� ��� ��� ������ ���� �� ����. */
} 

/* ��������� ��������� ��� ������� */
void st_delete(struct stack **head)
{
    struct stack *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
/* ��������� ��� ����� ��� ���� ��������� � temp */
        free(temp);
    }
}

  
/* ������ ��������� */
int main() 
{ 
/* �������� ��������� ���������� */
    system("chcp 1253>nul");
    struct stack *top;
	int vathmologia,answer; 
    construct(&top);
	printf("\n"); 
	printf("������� ����������� ����������� �������� ��� ���� �� ���10\n");
	printf("***********************************************************\n");
    printf("\n");
   
/* ��� ������ ������ ��� ��� �������� ��� ������ ��� ������ ��� �������� */
/* �������������� �������� �������������� ���� �� ������ ��� �� ���������� �� */
/* ���������� ��� ������� �������� [1,10]. ���������� ��� ���� �� ������ ����� �������� */ 
/* ���� �������� ������ ��� �� ������ ��� [1,10] �� ��������� ���� ������ */
    
		printf("� ������ ��� ������ ���� �����������. \n "); 
        printf("\n");   
/* ��� ������ ������ ��� ��� �������� ��� ��� ������ 1 ���� �� ��������� ��� �������� � 0 ��� �� ���������� */ 
/* �������������� �������� �������������� ���� �� ������ �� �������� ���� 1 ��� �������� ��� 0 ��� ����� ��� ��������� */	

/* ��� ������ ������ ��� ��� �������� ��� ��������� ��� ������� ���� ��� ���������� */

/* ��� ������ ������ ��� ��� ����� ��� ���������� ����������� ��� ������� �� �������� ����� */

/* ��� ������ ������ ��� ��� �������� ��� ��������� ��� ������� ���� ��� ���������� */
	
    st_delete(&top); /* ������������ ��� ������ ��� �������� � ������ */
    system("pause");

    return 0; 
} 


