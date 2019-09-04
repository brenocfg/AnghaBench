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
struct dirstack {size_t num_dirs; int /*<<< orphan*/ * dirs; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_dirstack( struct dirstack *dirstack )
{
    UINT i;
    for (i = 0; i < dirstack->num_dirs; i++) heap_free( dirstack->dirs[i] );
    dirstack->num_dirs = 0;
}