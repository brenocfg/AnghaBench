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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  ExitProcess (int) ; 
 int /*<<< orphan*/  FALSE ; 

void _font_assert(const char *msg, const char *file, int line)
{
  /* Assertion failed at foo.c line 45: x<y */
  DbgPrint("Assertion failed at %s line %d: %s\n", file, line, msg);
#ifdef _WIN32K_
  ASSERT(FALSE);
#else
  ExitProcess(3);  
  for(;;); /* eliminate warning by mingw */
#endif
}