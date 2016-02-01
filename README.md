Travis Build Status
==============
[![Build Status](https://travis-ci.org/corona10/Simple-MiniC-Compiler.svg?branch=master)](https://travis-ci.org/corona10/Simple-MiniC-Compiler)

#프로젝트 목표
  - (Simple Implementation of Mini C Compiler with LLVM)
       
# 현재 실행 가능한 소스코드 예제
  

   ```<cpp>
int minus(int x, int y)
{
   int result = 0;
   result = x - y;
   return result;
}

int add(int x, int y)
{
  int sum = 0;
  sum = x + y;
  return sum;
}

int main()
{
  
  int a = 3;
  int b = 1;
  float c = 4.5;
  a = 3+ 2+ 1;
  b = a + b; 
  add(a,b);
  minus(a, b);  
  return b;
}  
   
   ```
