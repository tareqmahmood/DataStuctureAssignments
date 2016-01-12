#include<stdio.h>
#include<stdlib.h>

// done editing. ready to submit //


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    //write your codes here
    struct listNode * newNode;
    newNode = (struct listNode*) malloc(sizeof(struct listNode));
    newNode->item = item;
    newNode->next = 0;
    struct listNode * temp = list, *prev = 0;
    if(temp == 0) // list is empty
    {
        list = newNode;
        return SUCCESS_VALUE;
    }
    while(temp != 0) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = newNode;
    return SUCCESS_VALUE;
}

int insertAfter(int oldItem, int newItem)
{
    //write your codes here
    struct listNode * newNode = (listNode *) malloc(sizeof(struct listNode));
    newNode->item = newItem;
    newNode->next = 0;
    struct listNode *temp = list;
    while(temp != 0)
    {
        if(temp->item == oldItem)
        {
            newNode->next = temp->next;
            temp->next = newNode;
            return SUCCESS_VALUE;
        }
        temp = temp->next;
    }
    return NULL_VALUE;
}

int deleteLast()
{
    //write your codes here
    if(list == 0) return NULL_VALUE;
    struct listNode * temp = list, *prev = 0;
    while(temp->next != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if(temp != list) prev->next = 0;
    else list = 0;
    free(temp);
    return SUCCESS_VALUE;
}

int deleteFirst()
{
    //write your codes here
    if(list == 0) return NULL_VALUE;
    struct listNode * temp = list;
    list = list->next;
    free(temp);
}


int main(void)
{
    //freopen("one.txt", "r", stdin);
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        //printf("4. (Add from homework). 5. Print. 6. exit.\n");
        printf("4. Insert item at last. 5. Insert item after an item. 6. Delete first item.\n");
        printf("7. Delete last item. 8. Print. 9. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch == 1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch == 2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch == 3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch == 4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch == 5)
        {
            int olditem, newitem;
            scanf("%d %d", &olditem, &newitem);
            if(insertAfter(olditem, newitem) != SUCCESS_VALUE)
            {
                printf("Insertion after %d failed!\n", olditem);
            }
        }
        else if(ch == 6)
        {
            deleteFirst();
        }
        else if(ch == 7)
        {
            deleteLast();
        }
        else if(ch == 8)
        {
            printList();
        }
        else if(ch == 9)
        {
            break;
        }
        //printList();
    }

}
