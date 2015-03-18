#include <stdio.h>
#define MEM_SIZE 100000
char Memory[MEM_SIZE];
int Frame_Pointer;
int Stack_Pointer;
int Temp;
double Temp_F;
int main() { 
Frame_Pointer=0;
Stack_Pointer=0;
int factorial(  )
{
(*(int *)(&Memory[(Frame_Pointer + 4)])) = 1;
if ((*(int *)(&Memory[(Frame_Pointer + 0)])))
{
Stack_Pointer += 4;
(*(int *)(&Memory[(Frame_Pointer + 8)])) = factorial();
;
(*(int *)(&Memory[(Frame_Pointer + 4)])) = (*(int *)(&Memory[(Frame_Pointer + 0)]))*(*(int *)(&Memory[(Frame_Pointer + 8)]));
Stack_Pointer -= 4;
}

}
Stack_Pointer += 12;
(*(int *)(&Memory[(Frame_Pointer + 0)])) = 3;
(*(int *)(&Memory[(Frame_Pointer + 4)])) = 4;
(*(int *)(&Memory[(Frame_Pointer + 8)])) = factorial();
;
Temp = (*(int *)(&Memory[(Frame_Pointer + 8)]));
printf("%d\n", Temp);
(*(int *)(&Memory[(Frame_Pointer + 8)])) = factorial();
;
Temp = (*(int *)(&Memory[(Frame_Pointer + 8)]));
printf("%d\n", Temp);
Temp = (*(int *)(&Memory[(Frame_Pointer + 0)]));
printf("%d\n", Temp);
Temp = (*(int *)(&Memory[(Frame_Pointer + 4)]));
printf("%d\n", Temp);
Stack_Pointer -= 12;
  return 0;
}
