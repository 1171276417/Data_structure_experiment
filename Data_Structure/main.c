//
//  main.c
//  Data_Structure
//
//  Created by 邓杰 on 2022/12/19.
//

#include <stdio.h>
#include "RegExp.h"

int main(int argc, const char * argv[]) {
   
    //正则表达式测试
    char text1[] = "ABD";
    char target1[] = "((A*B|AC)D)";
//    char text1[] = "我我我我BD";
//    char target1[] = "((我*B|AC)D)";

    __unused bool ishave1 = regExp(text1, target1);
    
    printf("");
    
    
    
}
