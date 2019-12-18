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
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 void* InputHandle ; 
 void* OutputHandle ; 
 int /*<<< orphan*/  ReadConsoleA (void*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  test1 () ; 
 int /*<<< orphan*/  test2 () ; 
 int /*<<< orphan*/  test3 () ; 
 int /*<<< orphan*/  test4 () ; 
 int /*<<< orphan*/  test5 () ; 
 int /*<<< orphan*/  test6 () ; 
 int /*<<< orphan*/  test7 () ; 
 int /*<<< orphan*/  test8 () ; 
 int /*<<< orphan*/  test9 () ; 

int main(int argc, char* argv[])
{
 char Buffer[10];
 DWORD Result;

  AllocConsole();
  InputHandle = GetStdHandle(STD_INPUT_HANDLE);
  OutputHandle =  GetStdHandle(STD_OUTPUT_HANDLE);
  while(1)
  {
    dprintf("choose test :\n");
    dprintf("  0=Exit\n");
    dprintf("  1=Ntxxx read functions\n");
    dprintf("  2=Ntxxx write functions : volatile keys\n");
    dprintf("  3=Ntxxx write functions : non volatile keys\n");
    dprintf("  4=Regxxx functions\n");
    dprintf("  5=FlushKey \n");
    dprintf("  6=Registry link create test\n");
    dprintf("  7=Registry link delete test\n");
    dprintf("  8=Not available\n");
    dprintf("  9=Ntxx read tcp/ip key test\n");
    ReadConsoleA(InputHandle, Buffer, 3, &Result, NULL) ;
    switch (Buffer[0])
    {
     case '0':
      return(0);
     case '1':
      test1();
      break;
     case '2':
      test2();
      break;
     case '3':
      test3();
      break;
     case '4':
      test4();
      break;
     case '5':
      test5();
      break;
     case '6':
      test6();
      break;
     case '7':
      test7();
      break;
#if 0
     case '8':
      test8();
      break;
#endif
     case '9':
      test9();
      break;
    }
  }
  return 0;
}