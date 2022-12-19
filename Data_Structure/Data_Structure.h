//
//  Data_Structure.h
//  Data_Structure
//
//  Created by 邓杰 on 2022/12/19.
//

#ifndef Data_Structure_h
#define Data_Structure_h

#include <stdio.h>
#include "stdlib.h"

typedef enum{false,true} bool;


#pragma mark - 图结构声明
///图边节点
typedef struct EdgeNode {
    int adjvex;     /**该边顶点的位置*/
    struct EdgeNode * _Nullable next;  /**下一条边*/
}EdgeNode;
///图顶结点
typedef struct VertexNode {
    char data;  /**存顶点信息*/
    EdgeNode * _Nullable firstedge;    /**第一条以该节点为顶点的边*/
    EdgeNode * _Nullable lastedge;     /**最后一条边节点*/
}VertexNode, Digraph;


#pragma mark - 栈结构声明
///栈结点
typedef struct StackNode {
    int data;
    struct StackNode * _Nullable next;
}StackNode, *LinkStack;


#pragma mark - 集合结构声明
///二叉树结点
typedef struct TreeNode {
    int data;
    struct TreeNode * _Nullable leftChild;
    struct TreeNode * _Nullable rightChild;
}TreeNode;

///二叉树存储集合
typedef struct Set {
    TreeNode * _Nullable rootNode;
    int nodeCount;
}Set;

#pragma mark - 数组结构声明
typedef struct Array {
    int * _Nullable array;
    int length;
    int count;
}Array;

#pragma mark - 队列结构声明
typedef struct QueueNode {
    Set * _Nullable data;
    struct QueueNode * _Nullable next;
}QueueNode;

typedef struct Queue {
    QueueNode * _Nullable front;
    QueueNode * _Nullable rear;
    int count;
}Queue;

#pragma mark - NFA状态集合结构声明
typedef struct NFAStateSet {
    Set *_Nullable* _Nullable stateSet;
    int count;
}NFAStateSet;

#pragma mark - DFA结构声明
typedef struct DFAStruct {
    int *_Nullable* _Nullable dfa;
    Array * _Nullable terminationState;
}DFAStruct;

///标准化字符串
typedef struct StringArr {
    /**将字符串转为char指针数组*/
    char *_Nullable* _Nullable stringArr;
    /**字符数组**/
    char *_Nullable* _Nullable charArr;
    /**字符串成员的集合（不重复）**/
    char *_Nullable* _Nullable charSet;
    /**字符串真实长度（数组长度）*/
    int length;
    /**字符数组长度**/
    int charCount;
    /**字符种类数（集合大小）*/
    int setSize;
}StringArr;




#pragma mark - 栈方法
/// 初始化栈
LinkStack _Nullable initStack(void);

/// 入栈
/// - Parameters:
///   - e: 入栈元素
///   - S: 栈结构
void pushStack(int e, LinkStack _Nullable S);

/// 出栈
/// - Parameter S: 栈结构
int popStack(LinkStack _Nullable S);


#pragma mark - 图方法
/// 初始化图
/// - Parameter targetArr: 图结点数组
Digraph* _Nullable  initGraph(StringArr * _Nullable targetArr);

/// 连接图结点
/// - Parameters:
///   - graph: 图结构
///   - tail: 尾结点
///   - head: 头结点
void linkGraphNode(Digraph * _Nullable graph,int tail, int head);



#pragma mark - 数组方法
/// 初始化数组
Array* _Nullable initArray(void);

/// 添加数组元素
/// - Parameters:
///   - arr: 数组对象
///   - data: 添加的元素
void addArray(Array * _Nullable arr, int data);

/// 判断该元素是否存在于该数组
/// - Parameters:
///   - arr: 数组对象
///   - data: 查询数据
bool belongArray(Array * _Nullable arr, int data);



#pragma mark - 集合方法
/// 初始化集合
Set* _Nullable initSet(void);

/// 插入集合元素
/// - Parameters:
///   - set: 集合对象
///   - data: 插入数据
void insert(Set * _Nullable set, int data);

/// 求集合并集
/// - Parameters:
///   - set1: 集合1
///   - set2: 集合2
Set* _Nullable set_union(Set * _Nullable   set1, Set * _Nullable set2);

/// 前序遍历集合，将结果存入数组中
/// - Parameters:
///   - node: 集合数的根结点
///   - arr: 存储数组
void treePreorderTraversal(TreeNode * _Nullable node, Array * _Nullable   arr);

/// 判断两个集合是否相同
/// - Parameters:
///   - set1: 集合1
///   - set2: 集合2
bool SetSame(Set * _Nullable set1, Set * _Nullable   set2);

/// 判断集合中是否有查询对象
/// - Parameters:
///   - set: 集合对象
///   - adjvex: 查询对象
bool isRepetition(Set * _Nullable set, int adjvex);


#pragma mark - 队列方法
/// 初始化队列
Queue* _Nullable initQueue(void);

/// 入队列
/// - Parameters:
///   - Q: 队列对象
///   - set: 入队元素
void enQueue(Queue * _Nullable Q, Set * _Nullable   set);

/// 出队列
/// - Parameter Q: 队列对象
Set* _Nullable  deQueue(Queue * _Nullable Q);

/// 判断队列是否为空
/// - Parameter Q: 队列对象
bool queueEmpty(Queue * _Nullable Q);



#pragma mark - 状态集合方法
/// 初始化状态集合
NFAStateSet* _Nullable initStateSet(void);

/// 向集合中添加一个状态，返回是否添加成功
/// - Parameters:
///   - stateSet: 状态集合
///   - set: 添加的状态
bool addStateSet(NFAStateSet * _Nullable stateSet, Set * _Nullable set);

/// 判断集合中是否有该状态
/// - Parameters:
///   - stateSet: 状态集合对象
///   - set: 判断的状态
int stateSame(NFAStateSet * _Nullable stateSet, Set * _Nullable set);



/// 初始化DFA
DFAStruct* _Nullable initDFA(void);

StringArr* _Nullable initStringArray(char target[_Nullable]);

int getLocationInArray(StringArr * _Nullable arr, char * _Nonnull data);



#endif /* Data_Structure_h */
