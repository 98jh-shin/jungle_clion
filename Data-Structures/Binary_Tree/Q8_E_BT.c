//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 8 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode {
    int item;
    struct _btnode* left;
    struct _btnode* right;
} BTNode; // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode {
    BTNode* btnode;
    struct _stackNode* next;
} StackNode;

typedef struct _stack {
    StackNode* top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int hasGreatGrandchild(BTNode* node);

BTNode* createBTNode(int item);

BTNode* createTree();
void push(Stack* stack, BTNode* node);
BTNode* pop(Stack* stack);

void printTree(BTNode* node);
void removeAll(BTNode** node);

///////////////////////////// main() /////////////////////////////////////////////

int main() {
    char e;
    int c, value;
    BTNode* root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the great grandchildren of the binary tree.\n");
    printf("0: Quit;\n");

    while (c != 0) {
        printf("Please input your choice(1/2/0): ");
        if (scanf("%d", &c) > 0) {
            switch (c) {
                case 1:
                    removeAll(&root);
                    root = createTree();
                    printf("The resulting binary tree is: ");
                    printTree(root);
                    printf("\n");
                    break;
                case 2:
                    printf(
                        "\nThe values stored in all nodes of the tree that has at least one great-grandchild are: ");
                    hasGreatGrandchild(root);
                    removeAll(&root);
                    break;
                case 0:
                    removeAll(&root);
                    break;
                default:
                    printf("Choice unknown;\n");
                    break;
            }
        } else {
            scanf("%c", &e);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int hasGreatGrandchild(BTNode* node) {
    if (node == NULL) return -1;
    int left_height = hasGreatGrandchild(node->left);
    int right_height = hasGreatGrandchild(node->right);
    if (left_height >= 2 || right_height >= 2) {
        printf("%d ", node->item);
    }
    int current_height = ((left_height > right_height) ? left_height : right_height) + 1;
    return current_height;
}







/*
BT 8번 문제는 증손자 노드를 가지고 있는, 높이가 3이상인 노드를 출력하는 문제입니다.
이 함수를 후위 순회 방식과 재귀를 이용하여 풀었습니다. 함수 반환 값으로는 현재 노드를 루트로 하는 서브트리의 높이를 반환합니다.
첫째 , 재귀의 종료 조건입니다.
노드가 NULL일 경우, -1을 반환합니다. 이를 통해 리프 노드의 높이가 0으로 계산됩니다.
둘째 핵심 로직입니다.
후위 순회 방식에 따라, 왼쪽과 오른쪽 자신 노드를 재귀 호출을 보낸 뒤 높이 값을 반환 받습니다.
만약 반환받은 자식의 높이가 2 이상이라면 현재 노드가 증손자를 가졌다고 판단하여 출력합니다.
마지막으로 반환 값입니다.
현재 노드의 높이는 자식들의 높이 중 더 큰 값에 1을 더한 값으로 이 값을 부모 노드로 반환합니다. 이상입니다
*/
//////////////////////////////////////////////////////////////////////////////////

BTNode* createBTNode(int item) {
    BTNode* newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode* createTree() {
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf(
        "Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if (scanf("%d", &item) > 0) {
        root = createBTNode(item);
        push(&stack, root);
    } else {
        scanf("%c", &s);
    }

    while ((temp = pop(&stack)) != NULL) {
        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if (scanf("%d", &item) > 0) {
            temp->left = createBTNode(item);
        } else {
            scanf("%c", &s);
        }

        printf("Enter an integer value for the Right child of %d: ",
               temp->item);
        if (scanf("%d", &item) > 0) {
            temp->right = createBTNode(item);
        } else {
            scanf("%c", &s);
        }

        if (temp->right != NULL)
            push(&stack, temp->right);
        if (temp->left != NULL)
            push(&stack, temp->left);
    }
    return root;
}

void push(Stack* stack, BTNode* node) {
    StackNode* temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stack->top == NULL) {
        stack->top = temp;
        temp->next = NULL;
    } else {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode* pop(Stack* stack) {
    StackNode *temp, *top;
    BTNode* ptr;
    ptr = NULL;

    top = stack->top;
    if (top != NULL) {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode* node) {
    if (node == NULL)
        return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}

void removeAll(BTNode** node) {
    if (*node != NULL) {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}