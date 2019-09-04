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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ ,int*,int,int*,int /*<<< orphan*/ *) ; 

int _putch(int c)
{
  DWORD NumberOfCharsWritten;

  if (WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),&c,1,&NumberOfCharsWritten,NULL)) {
    return -1;
  }
  return NumberOfCharsWritten;
}