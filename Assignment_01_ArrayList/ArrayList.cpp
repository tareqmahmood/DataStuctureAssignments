#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX 100
#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


int shrinkList();


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
    if(list == NULL) initializeList();
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrinkList();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	shrinkList();
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    printf(">> ");
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("\n");
    printf("Current size: %d, \tcurrent length: %d\n", listMaxSize, length);
}


/// what i have added now ///

int getLength()
{
    return length;
}

int insertItemAt(int pos, int item)
{
    if(list == NULL) initializeList();
    int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = list[pos] ;
	list[pos] = item;
	length++ ;
	return SUCCESS_VALUE ;
}

int shrinkList()
{
    if(length * 2 == listMaxSize && length >= LIST_INIT_SIZE) {
        int * tempList ;
        tempList = (int*) malloc (length*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
        listMaxSize = length;
        return SUCCESS_VALUE;
    }
    else return NULL_VALUE;
}

int deleteLast()
{
    int temp;
    if(length > 0) {
        temp = list[length - 1];
        length--;
    }
    else temp = NULL_VALUE;
    shrinkList();
    return temp;
}

void clearList()
{
    free(list);
    list = NULL;
    listMaxSize = 0;
    length = 0;
}
/*
void deleteAll()
{
    free(list);
    listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}
*/



int main(void)
{
    initializeList();
    while(1)
    {
        //printf("1. Insert new item.\t2. Delete item at.\t3. Delete item.\n");
        //printf("4. Insert item at.\t5. Print.\t\t6. exit.\n");

        printf("1. Insert new item.\t2. Insert item at.\t3. Delete last item.\n");
        printf("4. Delete item.\t\t5. Delete item at.\t6. Print.\n");
        printf("7. Clear list.\t\t8.Exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item, pos;
            printf("item: ");
            scanf("%d", &item);
            printf("position: ");
            scanf("%d", &pos);
            insertItemAt(pos, item);
        }
        else if(ch==3)
        {
            deleteLast();
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==5)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==6)
        {
            printList();
        }
        else if(ch==7)
        {
            clearList();
        }
        else if(ch==8)
        {
            break;
        }
        printList();
    }
}



/*
int main()
{
    initializeList();
    char str[MAX];
    gets(str);
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] == '(' || str[i] == '{' || str[i] == '[') insertItem((int)(str[i]));
        else {
            if(getLength() == 0) {
                printf("Not Balanced");
                return 0;
            }
            char item = (char)deleteLast();
            if(item == '(' && str[i] == ')') continue;
            else if(item == '{' && str[i] == '}') continue;
            else if(item == '[' && str[i] == ']') continue;
            else {
                printf("Not Balanced");
                return 0;
            }
        }
    }
    if(getLength() == 0) printf("Balanced");
    else printf("Not Balanced");
    clearList();
    return 0;
}
*/
