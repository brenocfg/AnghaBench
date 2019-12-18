#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AllocConsole () ; 
 int /*<<< orphan*/  CreateKeyTest () ; 
 int /*<<< orphan*/  DeleteKeyTest () ; 
 int /*<<< orphan*/  DeleteValueTest () ; 
 int /*<<< orphan*/  EnumerateKeyTest () ; 
 int /*<<< orphan*/  EnumerateValueTest () ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 void* InputHandle ; 
 void* OutputHandle ; 
 int /*<<< orphan*/  ReadConsoleA (void*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetValueTest1 () ; 
 int /*<<< orphan*/  SetValueTest2 () ; 
 int /*<<< orphan*/  dprintf (char*) ; 

int main(int argc, char* argv[])
{
  char Buffer[10];
  DWORD Result;

  AllocConsole();
  InputHandle = GetStdHandle(STD_INPUT_HANDLE);
  OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  while(1)
  {
    dprintf("choose test :\n");
    dprintf("  0 = Exit\n");
    dprintf("  1 = Create key\n");
    dprintf("  2 = Delete key\n");
    dprintf("  3 = Enumerate key\n");
    dprintf("  4 = Set value (REG_SZ)\n");
    dprintf("  5 = Set value (REG_DWORD)\n");
    dprintf("  6 = Delete value\n");
    dprintf("  7 = Enumerate value\n");
    ReadConsoleA(InputHandle, Buffer, 3, &Result, NULL) ;
    switch (Buffer[0])
    {
     case '0':
      return(0);

     case '1':
      CreateKeyTest();
      break;

     case '2':
      DeleteKeyTest();
      break;

     case '3':
      EnumerateKeyTest();
      break;

     case '4':
      SetValueTest1();
      break;

     case '5':
      SetValueTest2();
      break;

     case '6':
      DeleteValueTest();
      break;

     case '7':
      EnumerateValueTest();
      break;
    }
  }
  return(0);
}