//
//  RegExp.c
//  Data_Structure
//
//  Created by 邓杰 on 2022/12/19.
//

#include "RegExp.h"

Digraph* createNFA(StringArr *targetArr);
DFAStruct* createDFA(StringArr *targetArr, Digraph *digraphNFA);
Set* epsilonChange(Digraph *digraph, int i, int M);
Set* matchcConversion(Set *oldSet, char matchChar, Set **NFA, Digraph *digraph);
void graphPreOrderTraverse(EdgeNode *EnodeLast, Digraph *digraph, EdgeNode *Enode, Set *set, int M);
bool search(StringArr *textArr, StringArr *targetArr, DFAStruct *DFA);



bool regExp(char text[], char target[]) {

    //创建字符串对象
    StringArr *textString = initStringArray(text);
    StringArr *targetString = initStringArray(target);
    
    //创建NFA表示ε转换
    Digraph *digraphNFA = createNFA(targetString);

    //将NFA转换为DFA
    DFAStruct *DFA = createDFA(targetString, digraphNFA);

    //DFA中是否能匹配文本
    __unused bool ishave = search(textString, targetString, DFA);

    return ishave;
}


/// 构建NFA用于判断 ε 转换
Digraph* createNFA(StringArr *targetArr) {
    //图结点存储每一个状态
    Digraph *digraph = initGraph(targetArr);
    //栈结构来判断ε转换
    LinkStack stack = initStack();
    
    for(int i = 0; i < targetArr->setSize; i++) {
        targetArr->charSet[i] = NULL;
    }
    targetArr->setSize = 0;
    
    for(int i = 0; i < targetArr->length; i++) {
        if(*targetArr->stringArr[i] != '(' && *targetArr->stringArr[i] != ')' && *targetArr->stringArr[i] != '|' && *targetArr->stringArr[i] != '*') {
            targetArr->charArr[targetArr->charCount] = targetArr->stringArr[i];
            targetArr->charCount++;
         
            if(getLocationInArray(targetArr, targetArr->stringArr[i]) == -1) {
                targetArr->charSet[targetArr->setSize] = targetArr->stringArr[i];
                targetArr->setSize++;
            }
        }
        
        int lp = i;
        if(*targetArr->stringArr[i] == '(' || *targetArr->stringArr[i] == '|') {
            pushStack(i, stack);
        }
        else if(*targetArr->stringArr[i] == ')') {
            int or = popStack(stack);
            if(*targetArr->stringArr[or] == '|') {
                lp = popStack(stack);
                linkGraphNode(digraph, lp, or+1);
                linkGraphNode(digraph, or, i);
            }
            else lp = or;
        }
        if (i < targetArr->length-1 && *targetArr->stringArr[i+1] == '*') {
            linkGraphNode(digraph, lp, i+1);
            linkGraphNode(digraph, i+1, lp);
        }
        if(*targetArr->stringArr[i] == '(' || *targetArr->stringArr[i] == '*' || *targetArr->stringArr[i] == ')') {
            linkGraphNode(digraph, i, i+1);
        }
    }
    return digraph;
}



///将NFA转换为DFA
DFAStruct* createDFA(StringArr *targetArr, Digraph *digraphNFA) {
    
    //将ε转换图的集合
    Set **epsilonSet = (Set **)malloc(sizeof(Set *)*targetArr->length);
    for(int i = 0; i < targetArr->length; i++) {
        epsilonSet[i] = epsilonChange(digraphNFA, i, targetArr->length);
    }
        
    //DFA
    DFAStruct *DFA = initDFA();
    
    Queue *stateQueue = initQueue();
    enQueue(stateQueue, epsilonSet[0]);
    
    //DFA状态的集合
    NFAStateSet *stateSet = initStateSet();

    while (!queueEmpty(stateQueue)) {
        Set *set = deQueue(stateQueue);
        addStateSet(stateSet, set);
        for(int i = 0; i < targetArr->setSize; i++) {
            Set *set0 = matchcConversion(set, *targetArr->charSet[i], epsilonSet, digraphNFA);
            if(stateSame(stateSet, set0)) {
                DFA->dfa[stateSame(stateSet, set)-1][getLocationInArray(targetArr, targetArr->charSet[i])] = stateSame(stateSet, set0)-1;
            }
            else{
                enQueue(stateQueue, set0);
                DFA->dfa[stateSame(stateSet, set)-1][getLocationInArray(targetArr, targetArr->charSet[i])] = stateSet->count;
                addStateSet(stateSet, set0);
            }
            
            if(isRepetition(set0, targetArr->length)) {
                addArray(DFA->terminationState, stateSame(stateSet, set0)-1);
            }
        }
    }
    return DFA;
}




///顶点 i 经过epsilon转换到达的顶点集合
Set* epsilonChange(Digraph *digraph, int i, int M) {
    Set *set = initSet();
    insert(set, i);
    graphPreOrderTraverse(NULL, digraph, digraph[i].firstedge, set, M);
    return set;
}

///匹配转换
Set* matchcConversion(Set *oldSet, char matchChar, Set **NFA, Digraph *digraph) {
    
    Set *newSet = initSet();
    
    Array *arr = initArray();
    treePreorderTraversal(oldSet->rootNode, arr);
    
    int k = 0;
    while (digraph[arr->array[k]].data != matchChar) {
        k++;
        if(k == arr->count)
            return NFA[0];
    }
    
    for(int i = 0; i < arr->count; i++) {
        if(digraph[arr->array[i]].data == matchChar)
            newSet = set_union(NFA[arr->array[i]+1], newSet);
    }
    return newSet;
}


///图的深度优先遍历
void graphPreOrderTraverse(EdgeNode *EnodeLast, Digraph *digraph, EdgeNode *Enode, Set *set, int M) {
    if(EnodeLast) {
        if(Enode == NULL)
            Enode = EnodeLast->next;
        if(EnodeLast->adjvex == M)
            return;
    }
    while (Enode == NULL || (isRepetition(set, Enode->adjvex) && Enode->next)) {
        if(Enode && Enode->next)
            Enode = Enode->next;
        if(Enode == NULL || (isRepetition(set, Enode->adjvex) && !Enode->next))
            return;
    }
    do {
        insert(set, Enode->adjvex);
        graphPreOrderTraverse(Enode, digraph, digraph[Enode->adjvex].firstedge, set, M);
        Enode = Enode->next;
    }while(Enode);
}


///DFA中是否能匹配文本
bool search(StringArr *textArr, StringArr *targetArr, DFAStruct *DFA) {
    int i;  //文本位置
    int j;  //目标字符串位置
    for(i = 0, j = 0; i < textArr->length && j < targetArr->length; i++) {
        if(getLocationInArray(targetArr, textArr->stringArr[i]) == -1)
            j = 0;
        else
            j = DFA->dfa[j][getLocationInArray(targetArr, textArr->stringArr[i])];
        if(belongArray(DFA->terminationState, j))
            return true;
    }
    return false;
}

