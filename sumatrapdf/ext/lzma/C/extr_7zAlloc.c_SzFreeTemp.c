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
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int g_allocCountTemp ; 
 int /*<<< orphan*/  stderr ; 

void SzFreeTemp(void *p, void *address)
{
  p = p;
  #ifdef _SZ_ALLOC_DEBUG
  if (address != 0)
  {
    g_allocCountTemp--;
    fprintf(stderr, "\nFree_temp; count = %10d", g_allocCountTemp);
  }
  #ifdef _WIN32
  HeapFree(GetProcessHeap(), 0, address);
  return;
  #endif
  #endif
  free(address);
}