#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LENGTH 1024

typedef struct _binaryTree* Position;
typedef struct _binaryTree {

    int number;
    Position left;
    Position right;

}binaryTree;

typedef struct _queue* Pos;
typedef struct _queue {

    Position node;
    Pos next;

}queue;


int Choose(Position root);
Position Insert(Position root, int number);
Position AddNumber(int number);
Position Preorder(Position root);
Position Inorder(Position root);
Position Postorder(Position root);
Position Levelorder(Position root, Pos HeadQueue);
int AddEndElQueue(Pos HeadQueue, Position nodeAddress);
Position DeleteFirstElQueue(Pos HeadQueue);
Position DeleteNumber(Position root, int number);
bool FindNumber(Position root, int number);
int Replace(Position root);
int RandomNumber();
Position InorderFile(Position root, FILE* filepointer);
int FileWrite(Position root);



int main() {

    Position root = (Position)malloc(sizeof(binaryTree));
    root->left = NULL;
    root->right = NULL;

    Choose(root);
}

int Choose(Position root) {

    int number = 0, choice = 0, check = 0, check2 = 0, randNumber = 0;
    Position check_address;
    srand(time(0));

    while (1)
    {
        printf("Izaberite:\n1-insert number\n2-preorder\n3-inorder\n4-postorder\n5-level order\n6-delete element\n7-find element\n8-replace\n9-random\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Unesite broj: ");
            scanf("%d", &number);
            if (check == 0)
            {
                root->number = number;
                check = 1;
            }
            else
            {
                check_address = Insert(root, number);
                if (check_address != root)
                    return -1;

            }
        }

        if (choice == 2)
        {
            printf("Preorder: ");
            check_address = Preorder(root);

            if (check_address != root)
                return -1;

            printf("\n");

        }


        if (choice == 3)
        {
            printf("Inorder: ");
            check_address = Inorder(root);

            if (check_address != root)
                return -1;

            printf("\n");
            FileWrite(root);
        }

        if (choice == 4)
        {
            printf("Postorder: ");
            check_address = Postorder(root);

            if (check_address != root)
                return -1;

            printf("\n");
        }

        if (choice == 5)
        {
            queue HeadQueue = { .next = NULL, .node = NULL };
            printf("Levelorder: ");
            Levelorder(root, &HeadQueue);

            printf("\n");
        }

        if (choice == 6)
        {
            printf("koji broj zelite izbrisati: ");
            scanf("%d", &number);
            DeleteNumber(root, number);
            Preorder(root);

        }

        if (choice == 7)
        {
            printf("Unesite broj: ");
            scanf("%d", &number);

            if (FindNumber(root, number) == true)
                printf("Broj %d nalazi se u stablu\n", number);

            else
                printf("Broj %d ne nalazi se u stablu\n", number);

        }
        if (choice == 8)
        {
            if (Replace(root) == 0)
                return -1;
        }

        if (choice == 9)
        {
            if (check2 == 0)
            {
                randNumber = RandomNumber();
                if (!randNumber)
                    return -1;
                root->number = randNumber;
                check2 = 1;
            }
            else
            {
                randNumber = RandomNumber();
                if (!randNumber)
                    return -1;

                check_address = Insert(root, randNumber);
                if (check_address != root)
                    return -1;

            }

        }

    }

}
Position Insert(Position root, int number) {

    if (root == NULL)
        root = AddNumber(number);

    else if (number < root->number)
        root->left = Insert(root->left, number);

    else if (number >= root->number)
        root->right = Insert(root->right, number);

    return root;
}

Position AddNumber(int number) {

    Position newNumber = (Position)malloc(sizeof(binaryTree));

    newNumber->number = number;
    newNumber->left = NULL;
    newNumber->right = NULL;

    return newNumber;
}

Position Preorder(Position root) {

    if (root != NULL)
    {
        printf("%d ", root->number);
        Preorder(root->left);
        Preorder(root->right);
    }
    return root;
}

Position Inorder(Position root) {

    if (root != NULL)
    {
        Inorder(root->left);
        printf("%d ", root->number);
        Inorder(root->right);
    }

    return root;

}

Position Postorder(Position root) {

    if (root != NULL)
    {
        Postorder(root->left);
        Postorder(root->right);
        printf("%d ", root->number);
    }

    return root;

}

Position Levelorder(Position root, Pos HeadQueue) {

    if (root == NULL)
        return 0;

    AddEndElQueue(HeadQueue, root);

    while (1)
    {
        Position current = DeleteFirstElQueue(HeadQueue);

        if (current != NULL)
        {
            printf(" %d ", current->number);

            if (current->left != NULL)
                AddEndElQueue(HeadQueue, current->left);

            if (current->right != NULL)
                AddEndElQueue(HeadQueue, current->right);;
        }
        else
            return 0;
    }
}

int AddEndElQueue(Pos HeadQueue, Position nodeAddress) {

    Pos newEl = (Pos)malloc(sizeof(queue));
    Pos currentEl = HeadQueue;

    newEl->next = NULL;
    newEl->node = nodeAddress;

    while (currentEl->next != NULL)
        currentEl = currentEl->next;

    newEl->next = currentEl->next;
    currentEl->next = newEl;

    return 0;

}

Position DeleteFirstElQueue(Pos HeadQueue) {

    Pos toDelteEl = HeadQueue->next;
    Position todeleteNode;

    if (HeadQueue->next != NULL)
    {
        todeleteNode = toDelteEl->node;
        HeadQueue->next = toDelteEl->next;
        free(toDelteEl);
        return todeleteNode;
    }

    else
        return NULL;

}

bool FindNumber(Position root, int number) {

    bool istrue = false;

    if (root != NULL)
    {
        if (istrue == true)
            return istrue;

        else
        {
            if (number < root->number)
                istrue = FindNumber(root->left, number);

            else if (number > root->number)
                istrue = FindNumber(root->right, number);

            else
                istrue = true;
        }

    }
    return istrue;

}

Position DeleteNumber(Position root, int number) {

    Position temp;
    Position new;

    if (root == NULL)
        return root;

    if (number < root->number)
        root->left = DeleteNumber(root->left, number);

    else if (number > root->number)
        root->right = DeleteNumber(root->right, number);

    else
    {
        if (root->right == NULL && root->left == NULL)
        {
            free(root);
            return NULL;

        }
        else if (root->left == NULL && root->right != NULL)
        {
            temp = root->right;
            free(root);
            return temp;

        }
        else if (root->right == NULL && root->left != NULL)
        {
            temp = root->left;
            free(root);
            return temp;

        }
        else
        {
            temp = root->right;

            while (temp->left != NULL)
                temp = temp->left;

            root->number = temp->number;
            root->right = DeleteNumber(root->right, temp->number);
        }

    }
    return root;
}

int Replace(Position root)
{
    int leftchild, rightchild;
    int rootbefore;

    if (root == NULL)
        return 0;

    leftchild = Replace(root->left);
    rightchild = Replace(root->right);

    rootbefore = root->number;

    root->number = leftchild + rightchild;

    return rootbefore + root->number;


}
int RandomNumber()
{
    return rand() % 79 + 11;
}

Position InorderFile(Position root, FILE* filepointer) {

    if (root != NULL)
    {
        InorderFile(root->left, filepointer);
        fprintf(filepointer, "%d ", root->number);
        InorderFile(root->right, filepointer);
    }

    return root;

}

int FileWrite(Position root)
{
    FILE* filepointer = NULL;
    char buffer[MAX_LENGTH];

    filepointer = fopen("Inorder.txt", "a");

    if (!filepointer)
        return -1;

    InorderFile(root, filepointer);
    fprintf(filepointer, "\n", root->number);

    fclose(filepointer);

}