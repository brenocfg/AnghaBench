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
 int SQLITE_NOMEM_BKPT ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 void* sqlite3_malloc (int) ; 
 int sqlite3_os_init () ; 

int sqlite3OsInit(void){
  void *p = sqlite3_malloc(10);
  if( p==0 ) return SQLITE_NOMEM_BKPT;
  sqlite3_free(p);
  return sqlite3_os_init();
}