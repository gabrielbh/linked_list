#include<stdio.h>
#include<stdlib.h>

typedef struct node nodeStruct;


/**
 * create Struct node.
 */
struct node
{
    int data;
    nodeStruct *next;
} *head;

// initialize to 0.
int sizeOfNodes = 0;


/**
 * adds the data in the last place of the list
 * @param dataToAdd the data to add
 */
void addToEnd(int dataToAdd)
{
    nodeStruct *temp, *right;
    temp = (struct node *) malloc(sizeof(struct node));

    // The memory was allocated before.
//    temp->data = (int) malloc(sizeof(int));

    temp->data = dataToAdd;
    // We dont need to declare right and head as a struct again.
    right = head;

    while (right->next != NULL)
    {
        right = right->next;
    }

    right->next = temp;

    // WE dont need the current right to have the value of next.
//    right=temp;

    // We want to initialize the next of right->next to NULL.
    //(ofcourse not to change right->next that we just changed)
    right->next->next = NULL;
}

/**
 * adds the data in the first place of the list
 * @param dataToAdd the data to add
 */
void addFirst(int dataToAdd)
{
    nodeStruct *tempNode;
    tempNode = (struct node *) malloc(sizeof(struct node));

    // The memory was allocated before.
//    tempNode->data = (int) malloc(sizeof(int));

    tempNode->data = dataToAdd;
    if (head == NULL)
    {
        head = tempNode;
        head->next = NULL;
    }
    else
    {

        // We lost the pointer of head if we change the order of the calls.
        tempNode->next = head;
        head = tempNode;
    }

}

/**
 * adds a new data in a given place to add
 * @param dataToAdd the data to add
 * @param placeToAdd the place to add
 */
void addInPlace(int dataToAdd, int placeToAdd)
{
    int i;
    nodeStruct *temp, *left, *right;
    right = head;

    // We need to run until the index of the inserted data, and not more than that.
    // So we changed the i<placeToAdd + 1.
    for (i = 0; i < placeToAdd; i++)
        // Brackets added.
    {
        left = right;
        right = right->next;
    }
    temp = (struct node *) malloc(sizeof(struct node));

    // The memory was allocated before.
//    temp->data = (int) malloc(sizeof(int));

    temp->data = dataToAdd;
    left->next = temp;

    //WE dont need the current left to have the value of next.
//    left=temp;

    // We need the next of left->next, not left->next that we just changed.
    left->next->next = right;
    return;
}


/**
 * inserts a new data number
 * the data is inserted in ascending order, from the lowest to highest
 * @param dataToAdd the data to insert
 * @param numberOfNodes the current number of nodes
 */
void insert(int dataToAdd, int *numberOfNodes)
{
    int c = 0;
    nodeStruct *temp;
    temp = head;
    if (temp == NULL)
    {
        addFirst(dataToAdd);
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->data < dataToAdd)
            {
                c++;
                temp = temp->next;
            }
                // If (temp->data) > (dataToAdd) we would want to break
                // (else we would get infinite loop).
            else
            {
                break;
            }

        }

        if (c == 0)
        {
            addFirst(dataToAdd);
        }
        else if (c < *numberOfNodes)
        {
            addInPlace(dataToAdd, ++c);
        }
        else
        {
            addToEnd(dataToAdd);
        }
    }
    //we need the value of the pointer.
    (*numberOfNodes)++;
}


/**
 * deletes the first node with the number num
 * @param dataToDelete the data to delete
 * @param numberOfNodes the number of nodes
 * @return
 */
int delete(int dataToDelete, int *numberOfNodes)
{
    nodeStruct *temp, *prev;
    temp = head;
    while (temp != NULL)
    {
        if (temp->data == dataToDelete)
        {
            if (temp == head)
            {
                head = temp->next;
                free(temp);

            }
            else
            {
                // Not a mistake. will always be initialize, because if its not the
                // head it will be initialize in the "else" in the outer scoop.
                prev->next = temp->next;
                free(temp);
            }
            //we need the value of the pointer.
            (*numberOfNodes)--;
            return 1;

        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
    return 0;
}

/**
 * should print all the nodes in the linked list in this format:
 * number of nodes: <numberOfNodes>\n
 * <firstNodeData> --> <secondNodeData> --> .... <lastNodeData>\n
 * @param startingNodeToPrint the first node to print
 */
void display(nodeStruct *startingNodeToPrint)
{
    printf("number of nodes: %d\n", sizeOfNodes);
    if (startingNodeToPrint == NULL)
    {
        return;
    }
    while (startingNodeToPrint != NULL)
    {
        printf("%d --> ", startingNodeToPrint->data);
        startingNodeToPrint = startingNodeToPrint->next;
    }
    printf("NULL\n");
}


void basicTest()
{
    int data0 = 0;
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    insert(data1, &sizeOfNodes);
    insert(data2, &sizeOfNodes);
    insert(data3, &sizeOfNodes);
    insert(data2, &sizeOfNodes);
    insert(data1, &sizeOfNodes);
    insert(data2, &sizeOfNodes);
    insert(data1, &sizeOfNodes);
    insert(data0, &sizeOfNodes);
    display(head);

    delete(data1, &sizeOfNodes);
    delete(data2, &sizeOfNodes);
    display(head);
    delete(data2, &sizeOfNodes);
    delete(data3, &sizeOfNodes);
    delete(data2, &sizeOfNodes);
    display(head);
    delete(data1, &sizeOfNodes);
    delete(data1, &sizeOfNodes);
    delete(data0, &sizeOfNodes);
    display(head);
}

void hardTest()
{
    for (int i = 0; i < 100; i++)
    {
        insert(i, &sizeOfNodes);
    }
    display(head);

    for (int i = 0; i < 100; i++)
    {
        insert(i, &sizeOfNodes);
    }

    display(head);
    for (int i = 0; i < 100; i++)
    {
        delete(i, &sizeOfNodes);
    }
    display(head);
    for (int i = 0; i < 100; i++)
    {
        delete(i, &sizeOfNodes);
    }
    display(head);
}


int main()
{

    basicTest();
    hardTest();

    return 0;
}