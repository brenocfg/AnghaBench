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
typedef  void* HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_TEXTMODE_BUFFER ; 
 void* CreateConsoleScreenBuffer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 scalar_t__ SetConsoleActiveScreenBuffer (void*) ; 
 void* hStdin ; 
 void* hStdout ; 

void GetInputOutputHandles()
{
#ifdef NEW_CONSOLE
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
										FILE_SHARE_READ | FILE_SHARE_WRITE,
										0, CONSOLE_TEXTMODE_BUFFER, 0);

	if (SetConsoleActiveScreenBuffer(console) == FALSE)
	{
		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	else
	{
		hStdin = GetStdHandle(STD_INPUT_HANDLE);//console;
		hStdout = console;
	}
#else
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}