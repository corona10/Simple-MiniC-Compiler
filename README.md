Travis Build Status
==============
Master ![alt tag](https://magnum.travis-ci.com/corona10/Simple-MiniC-Compiler.svg?token=WuoJn3YfnHZ7RWX2jGYM&branch=master)

Simple Mini C Compiler
==============


#Objective: Implementing a simple Mini C comiler with LLVM 3.5
#프로젝트 목표
  - LLVM 3.4(->3,5로 변경됨.)로 미니 C컴파일러를 구현해보자..
  - 처음엔 완전한 c언어 구현이 목표였으나.. 아직 그 정도 만들능력은 안됨을 자각..
  - 함수 호출하고 반복문 실행해서 put함수로 화면에 뿌리는 정도만 해보자..
  - 할 수 있으면 scanf()정도까지 구현해볼까??
# 진행상태
  - 기타 구현은 계속 진행중
  - .bc파일 자동으로 생성 (./result/ 디렉토리에..)
  - .bc파일을 llvm 인터프리터로 실행가능
  - .bc파일을 바이너리 파일 뽑아낼 계획임.
  - 함수 호출 구현완료 2014/11/29
  - 함수 매개변수 구현 완료  2014/12/02
  - 이항연산 구현 완료.. 2014/12/15
  - 함수의 변수 심볼테이블 구현 예정 2014/12/15

# 문법 구현 상태
  - int float double 형 변수 선언 가능
    ex)
 
    '

        int a;
        int b = 5; 
        float c = 4.5;

    '
   - 함수 정의 가능
     ex)
 
     '

         int sum()
         {
            int a = 3;
            return a;
         }
     
     '

      int, double, float, void 형으로 정의 가능
   - 함수 호출 구현 완료 
   - 반복문 구현 (기능 구현 예정 중..)
   - 내장함수 구현 중..( 기능 구현 중..)
   
# 현재 실행 가능한 소스코드 예제
  
    **<예제 코드>**


   '

     int function_test(int hello)
     {
        return 1;
     }
  
     float what()
     {
       return 3.5;
     }
    
    int add(int x, float y)
    {
       int a =3;
       return a;
    }
    
    int main()
    {
  
       int a= 5;
       float c = 3.5;
       what();
       function_test(a);
       add(a, c);
       return 0;
    }


   '

    **<LLVM IR 코드 결과물>**


   '

    
     define i32 @function_test(i32 %hello) {
       entry:
       ret i32 1
     }

     define float @what() {
       entry:
       ret float 3.500000e+00
    }

    define i32 @add(i32 %x, float %y) {
       entry:
       %a = alloca i32, align 4
      store i32 3, i32* %a, align 4
      ret i32 3
   } 

    define i32 @main() {
      entry:
      %a = alloca i32, align 4
      store i32 5, i32* %a, align 4
      %c = alloca float, align 4
     store float 3.500000e+00, float* %c, align 4
     %0 = call float @what()
     %1 = call i32 @function_test(i32 5)
     %2 = call i32 @add(i32 5, float 3.500000e+00)
     ret i32 0
   }

   '
# License
-----------------------------------------------------------------------------

The MIT License (MIT)

Copyright (c) 2014 Dong-hee,Na <corona10@gmail.com> 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

-----------------------------------------------------------------------------

MIT 라이선스

Copyright (c) 2014 나동희 <corona10@gmail.com> 
 
이 소프트웨어의 복제본과 관련된 문서화 파일(“소프트웨어”)을 획득하는 사람은 누구라도 소프트웨어를 별다른 제한 없이 무상으로 사용할 수 있는 권한을 부여 받는다. 여기에는 소프트웨어의 복제본을 무제한으로 사용, 복제, 수정, 병합, 공표, 배포, 서브라이선스 설정 및 판매할 수 있는 권리와 이상의 행위를 소프트웨어를 제공받은 다른 수취인들에게 허용할 수 있는 권리가 포함되며, 다음과 같은 조건을 충족시키는 것을 전제로 한다.
 
위와 같은 저작권 안내 문구와 본 허용 문구가 소프트웨어의 모든 복제본 및 중요 부분에 포함되어야 한다.
 
이 소프트웨어는 상품성, 특정 목적 적합성, 그리고 비침해에 대한 보증을 포함한 어떠한 형태의 보증도 명시적이나 묵시적으로 설정되지 않은 “있는 그대로의” 상태로 제공된다.
소프트웨어를 개발한 프로그래머나 저작권자는 어떠한 경우에도 소프트웨어나 소프트웨어의 사용 등의 행위와 관련하여 일어나는 어떤 요구사항이나 손해 및 기타 책임에 대해 계약상, 불법행위 또는 기타 이유로 인한 책임을 지지 않는다. 

