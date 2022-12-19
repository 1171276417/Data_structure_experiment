//
//  Data_Structure.c
//  Data_Structure
//
//  Created by 邓杰 on 2022/12/19.
//

#include "Data_Structure.h"
int getStringCount(char string[]);
int getLocationInArray(StringArr *arr, char *data);




#pragma mark - 栈操作
///初始化一个栈
LinkStack initStack(void) {
    LinkStack S = (StackNode *)malloc(sizeof(StackNode));
    S->data = 123456;
    S->next = NULL;
    return S;
}
///入栈操作
void pushStack(int e, LinkStack S) {
    StackNode *topNode = (StackNode *)malloc(sizeof(StackNode));
    *topNode = *S;
    S->next = topNode;
    S->data = e;
}
///出栈操作
int popStack(LinkStack S) {
    int data = S->data;
    StackNode *node = S->next;
    S->next = node->next;
    S->data = node->data;
    free(node);
    return data;
}


#pragma mark - 图操作
///初始化图
Digraph* initGraph(StringArr *targetArr) {
    Digraph *graph = (VertexNode *)malloc(sizeof(VertexNode)*(targetArr->length+1)); /**开辟图空间*/
    for(int i = 0; i < targetArr->length; i++) {
        graph[i].data = *targetArr->stringArr[i];  /**输入顶点信息*/
        graph[i].firstedge = NULL;
        graph[i].lastedge = NULL;
    }
    return graph;
}

///连接图节点
void linkGraphNode(Digraph *graph,int tail, int head) {
    EdgeNode *Enode = (EdgeNode *)malloc(sizeof(EdgeNode));
    Enode->adjvex = head;
    Enode->next = NULL;
    if(!graph[tail].firstedge) {
        graph[tail].firstedge = Enode;
        graph[tail].lastedge = Enode;
    }
    else {
        graph[tail].lastedge->next = Enode;
        graph[tail].lastedge = Enode;
    }
}




#pragma mark - 数组操作
///数组创建初始化
Array* initArray(void) {
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->array = (int *)malloc(sizeof(int)*20);
    for(int i = 0; i < 20; i++)
        arr->array[i] = '\0';
    arr->length = 20;
    arr->count = 0;
    return arr;
}

///数组添加元素
void addArray(Array *arr, int data) {
    arr->array[arr->count] = data;
    arr->count++;
    if(arr->count == arr->length) {
        int *newArr = (int *)malloc(sizeof(int)*(int)(arr->length*1.25));
        for(int i = 0; i < arr->count; i++)
            newArr[i] = arr->array[i];
        free(arr->array);
        arr->array = newArr;
    }
}

///判断某元素是否属于该数组
bool belongArray(Array *arr, int data) {
    for(int i = 0; i < arr->count; i++)
        if(arr->array[i] == data) return true;
    return false;
}

#pragma mark - 集合操作
///初始化集合
Set* initSet(void) {
    Set *set = (Set *)malloc(sizeof(Set));
    set->rootNode = NULL;
    set->nodeCount = 0;
    return set;
}

///插入集合数据
void insert(Set *set, int data) {
    if(!set->rootNode) {
        set->rootNode = (TreeNode *)malloc(sizeof(TreeNode));
        set->rootNode->data = data;
        set->rootNode->leftChild = NULL;
        set->rootNode->rightChild = NULL;
        set->nodeCount++;
    }
    else {
        TreeNode *node = set->rootNode;
        do {
            if(data < node->data) {
                if(node->leftChild)
                    node = node->leftChild;
                else {
                    node->leftChild = (TreeNode *)malloc(sizeof(TreeNode));
                    node->leftChild->leftChild = NULL;
                    node->leftChild->rightChild = NULL;
                    set->nodeCount++;
                    node->leftChild->data = data;break;
                }
            }
            if(data > node->data) {
                if(node->rightChild)
                    node = node->rightChild;
                else {
                    node->rightChild = (TreeNode *)malloc(sizeof(TreeNode));
                    node->rightChild->leftChild = NULL;
                    node->rightChild->rightChild = NULL;
                    set->nodeCount++;
                    node->rightChild->data = data;break;
                }
            }
            if(data == node->data)break;
        }while(node);
    }
}

///集合并集
Set* set_union(Set *set1, Set *set2) {
    Set *set = initSet();
    
    if(!set2->rootNode)
        return set1;
    if(!set1->rootNode)
        return set2;
    
    
    Array *arr1 = initArray();
    Array *arr2 = initArray();
    
    treePreorderTraversal(set1->rootNode, arr1);
    treePreorderTraversal(set2->rootNode, arr2);

    for(int i = 0; i < arr1->count; i++)
        insert(set, arr1->array[i]);
    for(int i = 0; i < arr2->count; i++)
        insert(set, arr2->array[i]);
    return set;
}

///前序遍历集合
void treePreorderTraversal(TreeNode *node, Array *arr) {
    if(node == NULL)
        return;
    addArray(arr, node->data);
    
    treePreorderTraversal(node->leftChild, arr);
    treePreorderTraversal(node->rightChild, arr);
}

///判断两个集合是否相同
bool SetSame(Set *set1, Set *set2) {
    Array *arr1 = initArray();
    Array *arr2 = initArray();
    

    treePreorderTraversal(set1->rootNode, arr1);
    treePreorderTraversal(set2->rootNode, arr2);
    
    if(arr1->count != arr2->count)
        return false;
    else {
        for(int i = 0; i < arr1->count; i++)
            if(arr1->array[i] != arr2->array[i]) return false;
        return true;
    }
}

///判断集合中是否已经存储
bool isRepetition(Set *set, int adjvex) {
    Array *arr = initArray();
    treePreorderTraversal(set->rootNode, arr);
    for(int i = 0; i < arr->count; i++)
        if(arr->array[i] == adjvex) return true;
    return false;
}



#pragma mark - 队列操作

///队列初始化
Queue* initQueue(void) {
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->count = 0;
    Q->front = NULL;
    Q->rear = NULL;
    return Q;
}

///入队列
void enQueue(Queue *Q, Set *set) {
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = set;
    node->next = NULL;
    
    if(Q->rear == NULL) {
        Q->front = node;
        Q->rear = node;
    }
    else {
        Q->rear->next = node;
        Q->rear = node;
    }
    Q->count++;
}

///出队列
Set* deQueue(Queue *Q) {
    if(queueEmpty(Q))
        return NULL;
    Set *set = Q->front->data;
    QueueNode *node = Q->front;
    if(Q->front->next)
        Q->front = Q->front->next;
    else {
        Q->front = NULL;
        Q->rear = NULL;
    }
    free(node);
    Q->count--;
    
    return set;
}

///判断队列是否为空
bool queueEmpty(Queue *Q) {
    if(Q->count == 0)
        return true;
    return false;
}


#pragma mark - 状态集合操作
///初始化状态集合
NFAStateSet* initStateSet(void) {
    NFAStateSet *stateSet = (NFAStateSet *)malloc(sizeof(NFAStateSet));
    stateSet->stateSet = (Set **)malloc(sizeof(Set *)*100);
    stateSet->count = 0;
    return stateSet;
}

///DFA状态集合添加状态
bool addStateSet(NFAStateSet *stateSet, Set *set) {
    if(stateSame(stateSet, set))
        return false;
    stateSet->stateSet[stateSet->count] = set;
    stateSet->count++;
    return true;
}

///判断该状态在DFA中是否已经存在，如果存在则返回位置
int stateSame(NFAStateSet *stateSet, Set *set) {
    for(int i = 0; i < stateSet->count; i++){
        if(!set) {
            printf("");
        }
        if(SetSame(stateSet->stateSet[i], set))
            return i+1;
    }
      
    return 0;
}

#pragma mark - DFA操作
///初始化DFA
DFAStruct* initDFA(void) {
    DFAStruct *DFA = (DFAStruct *)malloc(sizeof(DFAStruct));
    DFA->dfa = (int**)malloc(sizeof(int*)*20);
    for(int i = 0; i < 20; i++)
        DFA->dfa[i] = (int *)malloc(sizeof(int)*128);
    
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 128; j++)
            DFA->dfa[i][j] = '\0';
    
    DFA->terminationState = initArray();
    return DFA;
}


///将字符串标准化返回StringArr*
StringArr* initStringArray(char target[]) {
    int initialLength = getStringCount(target);
    
    //创建并初始化StringArr
    StringArr *arr = (StringArr *)malloc(sizeof(StringArr));
    arr->setSize = 0;
    arr->length = 0;
    arr->charArr = (char **)malloc(sizeof(char*)*arr->length);
    for(int k = 0; k < arr->length; k++)
        arr->stringArr[k] = (char *)malloc(sizeof(char)*3);
    arr->charCount = 0;
    arr->stringArr = NULL;
    
    /**ASCII字符个数*/
    int ASCIICount = 0;
    /**Unicode字符个数*/
    int UnicodeCount = 0;
    
    //计算字符串真实长度
    for(int i = 0; i < initialLength; i++) {
        if((int)target[i] < 0)  UnicodeCount++;     //Unicode编码占三个char，并且int强转为负
        if((int)target[i] > 0)  ASCIICount++;       //ASCII字符占一个char，int转换为正
    }
    arr->length = ASCIICount + UnicodeCount/3;      //字符串真实长度
    
    //开辟二维char数组存字符串
    arr->stringArr = (char **)malloc(sizeof(char*)*arr->length);
    for(int k = 0; k < arr->length; k++)                          //数组长度为length
        arr->stringArr[k] = (char *)malloc(sizeof(char)*3);         //数组每个元素为一个长为3的字符串
    
    //初始化数组元素
    for(int n = 0; n < arr->length; n++)
        for(int m = 0; m < 3; m++)
            arr->stringArr[n][m] = '\0';
    
    /**原始字符串位置下标*/
    int location = 0;
    //将原始字符串标准化存入数组中
    for(int i = 0; i < arr->length; i++) {
        if((int)target[location] > 0) {
            arr->stringArr[i][0] = target[location];
            location++;     //ASCII字符占一个char,所以location+1
        }
        else {
            arr->stringArr[i][0] = target[location++];
            arr->stringArr[i][1] = target[location++];
            arr->stringArr[i][2] = target[location++];  //Unicode编码占3个char,所以location+3
        }
    }
    
    //计算获得数组元素集合
    arr->charSet = (char **)malloc(sizeof(char*)*arr->length);
    for(int i = 0; i < arr->length; i++) {
        if(getLocationInArray(arr, arr->stringArr[i]) == -1) {
            arr->charSet[arr->setSize] = arr->stringArr[i];     //如果集合中不存在，则存入新元素
            arr->setSize++;
        }
    }
    
    return arr;
}

///获得字符串长度
int getStringCount(char string[]) {
    int count = 0;
    while (string[count]) {
        count++;
    }
    return count;
}


///获得该字符在集合的位置
int getLocationInArray(StringArr *arr, char *data) {
    for(int i = 0; i < arr->setSize; i++) {
        if(arr->charSet[i][0] == data[0] && arr->charSet[i][1] == data[1] && arr->charSet[i][2] == data[2])
            return i;
    }
    return -1;
}
