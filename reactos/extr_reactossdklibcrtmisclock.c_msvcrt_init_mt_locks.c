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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  _LOCKTAB_LOCK ; 
 int _TOTAL_LOCKS ; 
 int /*<<< orphan*/  msvcrt_initialize_mlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msvcrt_mlock_set_entry_initialized (int,int /*<<< orphan*/ ) ; 

void msvcrt_init_mt_locks(void)
{
  int i;

  TRACE( "initializing mtlocks\n" );

  /* Initialize the table */
  for( i=0; i < _TOTAL_LOCKS; i++ )
  {
    msvcrt_mlock_set_entry_initialized( i, FALSE );
  }

  /* Initialize our lock table lock */
  msvcrt_initialize_mlock( _LOCKTAB_LOCK );
}