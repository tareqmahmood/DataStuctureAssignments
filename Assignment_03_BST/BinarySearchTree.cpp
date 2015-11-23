#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;

void printInOrder(struct treeNode *, int);


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node == 0) return 0;
    if(node->item == item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
}


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
}

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node == 0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item == item) return 0; //already an item exists, so return NULL

    if(item < node->item && node->left == 0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item > node->item && node->right == 0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item < node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node == 0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l > r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node == 0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node == 0) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode * temp = root;
    int depth = -1;
    while(temp != 0)
    {
        depth++;
        if(temp->item == node->item) break;
        if(node->item < temp->item) temp = temp->left;
        else temp = temp->right;
    }
    if(temp != 0) return depth;     // node exists
    else return -1;
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode * temp = root;
    int depth = -1;
    while(temp != 0)
    {
        depth++;
        if(temp->item == item) break;
        if(item < temp->item) temp = temp->left;
        else temp = temp->right;
    }
    if(temp != 0) return depth;   // item exists
    else return -1;
}

struct treeNode * findParent(int item)
{
    struct treeNode * temp = root;
    struct treeNode * par = 0;
    while(temp->item != item)
    {
        par = temp;
        if(item < temp->item) temp = temp->left;
        else temp = temp->right;
    }
    return par;
}


int deleteItem(struct treeNode * node, int item)
{
    if(node == 0) return FALSE_VALUE;
    //printf("node : %d\n", node->item);
    // node found
    if(node->item == item)
    {
        struct treeNode * par = findParent(item);   // finding parent
        //if(par != 0) printf("Par : %d\n", par->item);
        // leaf node
        if(node->left == 0 && node->right == 0)
        {
            if(par == 0) // the root is being deleted and tree is being empty
            {
                free(root);
                root = 0;
            }
            else if(par->left != 0 && par->left->item == item)
            {
                free(par->left);
                par->left = 0;
            }
            else
            {
                free(par->right);
                par->right = 0;
            }
            return TRUE_VALUE;
        }
        // node with one child which is right
        else if(node->left == 0 && node->right != 0)
        {
            if(par == 0)    // root node with one right child
            {
                root = node->right;
            }
            else if(par->left != 0 && par->left->item == item)
            {
                par->left = node->right;
            }
            else
            {
                par->right = node->right;
            }
            free(node);
            return TRUE_VALUE;
        }
        // node with one child which is left
        else if(node->right == 0 && node->left != 0)
        {
            if(par == 0)    // root node with one left child
            {
                root = node->left;
            }
            else if(par->left != 0 && par->left->item == item)
            {
                par->left = node->left;
            }
            else
            {
                par->right = node->left;
            }
            free(node);
            return TRUE_VALUE;
        }
        // node with both left and right child
        else
        {
            struct treeNode * temp = node->right;
            struct treeNode * prev = node;
            while(temp->left != 0)
            {
                prev = temp;
                temp = temp->left;
            }
       item = temp->item;
            deleteItem(node, temp->item);
            node->item = item;
            return TRUE_VALUE;
        }
    }
    // node not found ...
    else
    {
        int ret = deleteItem(node->left, item);
        if(ret == FALSE_VALUE) ret = deleteItem(node->right, item);
        return ret;
    }
}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode * temp = root;
    while(temp->left != 0)
    {
        temp = temp->left;      // travrsing only to left side
    }
    return temp->item;
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode * temp = root;
    while(temp->right != 0)
    {
        temp = temp->right;     // traversing only to right side
    }
    return temp->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    if(node == 0) return 0;
    if(node->item < leftBound) return rangeSearch(node->right, leftBound, rightBound);  // node item is less than range, left subtree will also be less
    if(node->item > rightBound) return rangeSearch(node->left, leftBound, rightBound);  // node item is greater than range, so will be right tree
    else return 1 + rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);   // search both + itself
}


void printInOrder(struct treeNode * node, int height)
{
    if(node == 0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i < height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



void printMenu()
{
    printf("1. Insert item. \t 2. Delete item. \t 3. Search item. \n");
    printf("4. Height of tree. \t 5. Height of an item. \n");
    printf("6. PrintInOrder. \t 7. Size of tree. \t 8. Depth of item.\n");
    printf("9. Depth of node. \t 10. Get minimum. \t 11. Get maximum.\n");
    printf("12. Range search. \t 13. Delete item. \t 14. Exit. \n");
}



int main(void)
{
    //freopen("in2.txt", "r", stdin);
    initializeTree();
    while(1)
    {
        //printMenu();
        int ch;
        scanf("%d",&ch);
        if(ch == 1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch == 2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch == 3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch == 4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch == 5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch == 6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch == 7)
        {
            printf("%d\n", getSize(root));
        }
        else if(ch == 8)
        {
            int item;
            scanf("%d", &item);
            printf("%d\n", calcDepth(item));
        }
        else if(ch == 9)
        {
            printf("%d\n", calcNodeDepth(root));
        }
        else if(ch == 10)
        {
            if(root == 0) {
                printf("tree is empty\n");
                continue;
            }
            printf("%d\n", getMinItem());
        }
        else if(ch == 11)
        {
            if(root == 0) {
                printf("tree is empty\n");
                continue;
            }
            printf("%d\n", getMaxItem());
        }
        else if(ch == 12)
        {
            int left, right;
            scanf("%d %d", &left, &right);
            printf("%d\n", rangeSearch(root, left, right));
        }
        else if(ch == 13)
        {
            int item;
            scanf("%d", &item);
            //printf("Del : %d\n", item);
            //deleteItem(root, item);
            printf("%d\n", deleteItem(root, item));
        }
        else if(ch == 14)
        {
            break;
        }
    }

}
