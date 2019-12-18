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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 char* THAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char* THMemoryFile_cloneString(const char *str, ptrdiff_t size)
{
  char *cstr = THAlloc(size);
  memcpy(cstr, str, size);
  return cstr;
}