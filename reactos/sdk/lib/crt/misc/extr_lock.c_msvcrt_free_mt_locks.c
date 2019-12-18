#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ bInit; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int _TOTAL_LOCKS ; 
 TYPE_1__* lock_table ; 
 int /*<<< orphan*/  msvcrt_uninitialize_mlock (int) ; 

void msvcrt_free_mt_locks(void)
{
  int i;

  TRACE(": uninitializing all mtlocks\n" );

  /* Uninitialize the table */
  for( i=0; i < _TOTAL_LOCKS; i++ )
  {
    if( lock_table[ i ].bInit )
    {
      msvcrt_uninitialize_mlock( i );
    }
  }
}