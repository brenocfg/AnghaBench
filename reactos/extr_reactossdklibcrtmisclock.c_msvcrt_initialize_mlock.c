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
struct TYPE_2__ {int /*<<< orphan*/  crit; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* lock_table ; 
 int /*<<< orphan*/  msvcrt_mlock_set_entry_initialized (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void msvcrt_initialize_mlock( int locknum )
{
  InitializeCriticalSection( &(lock_table[ locknum ].crit) );
  msvcrt_mlock_set_entry_initialized( locknum, TRUE );
}