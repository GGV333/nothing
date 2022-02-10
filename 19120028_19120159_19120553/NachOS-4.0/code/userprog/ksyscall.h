/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"


void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}


char* User2System(int virtAddr, int limit)
{
	int i; // Index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; // String for terminal
	if (kernelBuf == NULL)
		return kernelBuf;
		
	memset(kernelBuf, 0, limit + 1);
	
	for (i = 0; i < limit; i++)
	{
		kernel->machine->ReadMem(virtAddr + i, 1, &oneChar); // Read char in virtual address
		kernelBuf[i] = (char)oneChar;
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

int System2User(int virtAddr, int len, char* buffer)
{
	if (len < 0) return -1; // Check len
	if (len == 0)return len; 
	int i = 0; // Index
	int oneChar = 0;
	do{
		oneChar = (int)buffer[i];
		kernel->machine->WriteMem(virtAddr + i, 1, oneChar); // Write char to virtual address
		i++;
	} while (i < len && oneChar != 0); // Check len or end of string
	return i;
}

int SysReadNum(){
  char c;
  bool negative = false; // Check negative number
  c = kernel->synchConsoleIn->GetChar(); // Get first character
  int res = 0, maxInt = 65000;
  if (c=='-') // If it is negative number --> negative = True
    negative = true;
  else if (c>'9' || c <'0') // If it is invalid number
    return 0;
  else // If it is a number
    res = c - '0';
  while(true){
    c = kernel->synchConsoleIn->GetChar(); // Get a char in screen
    if (c=='\n' || c=='\0'||c==' ') // Check end of a string number
      break;
    else if (c>'9' || c < '0') // Check a invalid number
      return 0;
    if (res >= maxInt){ // Check overflow
      return 0;
    }
    res = res*10 + (c - '0'); // String to num
  }

  if (negative){
    return (-1)*res; // Negative number
  }
  return (int)res; // Positive number
}

void SysPrintNum(int res){
  if (res==0){ // Print 0 if a number =  0
    kernel->synchConsoleOut->PutChar('0');
  }
  else{
    if (res < 0){ // Check a negative number
      kernel->synchConsoleOut->PutChar('-');
      res = -1*res;
    }
    int resReverse = 0, count= 0;
    while(res%10==0){ // Check a sequence zero at the end of string
      count++;
      res/=10;
    }
    while (res!=0){ // Reverse number
      int c = (res%10);
      resReverse = resReverse*10 + c;
      res = res/10;
    }
    while (resReverse!=0){ // Print Number
      char c = (resReverse%10) + '0';
      kernel->synchConsoleOut->PutChar(c);
      resReverse/=10;
    }
    while(count > 0){ // Print a sequence of zero at the end of number
      count--;
      kernel->synchConsoleOut->PutChar('0');
    }
  }
}

char SysReadChar(){
  char c = kernel->synchConsoleIn->GetChar(); // Get a char from screen
  return c;
}

void SysPrintChar(char c){ // Put a char from screen
  kernel->synchConsoleOut->PutChar(c);
}

int SysRandomNum(){
  int res;
  srand(time(NULL)); // Set null for random
  res = rand()%65536; // Random in range(0, 65535)
  return res;
}

void SysReadString(int userBuff,int length){
  char *kernelBuff = new char[length + 1]; // Initalize the array of character
  for (int i = 0; i < length;i++){
    kernelBuff[i] = kernel->synchConsoleIn->GetChar(); // Get a char in screen
    if (kernelBuff[i] == '\n'){ // Check the end of string
      kernelBuff[i + 1] = '\0';
      break;
    }
  }
  kernelBuff[length] = '\0'; // Set the '\0' at the end of string
  System2User(userBuff, length, kernelBuff); // Transfer data from system to user
  delete kernelBuff;
}

void SysPrintString(int userbuff){
  char *kernelBuff = User2System(userbuff, 255); // Get a string by address
  int length = 0;
  while (kernelBuff[length]!='\0')
    length++; // Length of string
  for (int i = 0; i < length;i++) // Print string by put LENGTH char in screen
    kernel->synchConsoleOut->PutChar(kernelBuff[i]);
  delete kernelBuff;
}



#endif /* ! __USERPROG_KSYSCALL_H__ */
