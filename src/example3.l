%{
#include<stdio.h>
%}

%%
[a-zA-Z][[a-zA-Z0-0]* printf("WORD\n");
[1-9][0-9]*           printf("Integer\n");
[ \t]+

%%
