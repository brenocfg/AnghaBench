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
 int alloc_num ; 
 int alloc_size ; 
 int /*<<< orphan*/  printf (char*,void*,int,int,char*) ; 

void dumpfunc(void *ptr, int sz, char *file, int line)
{
   printf("%p (%6d)  -- %3d:%s\n", ptr, sz, line, file);
   alloc_size += sz;
   alloc_num  += 1;
}