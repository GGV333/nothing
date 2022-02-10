#include "syscall.h"

int main(){

    int i;
    char c;
    PrintString("Your ascii sequences:\n");
    for (i = 32; i <= 127; i++){
        PrintNum(i - 31);
        PrintString(". ");
        c = i + '0' - '0';
        PrintChar(c);
        PrintChar('\n');
    }
    Halt();
}