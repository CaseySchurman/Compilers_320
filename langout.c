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
Stack_Pointer += 24;
(*(int *)&Memory[Frame_Pointer + 0]) = (Memory[Frame_Pointer + 4]);
(*(int *)&Memory[Frame_Pointer + 0]) = (Memory[Frame_Pointer + 4]);
(Memory[Frame_Pointer + 4]) = (*(int *)&Memory[Frame_Pointer + 0]);
Stack_Pointer -= 24;
  return 0;
}
