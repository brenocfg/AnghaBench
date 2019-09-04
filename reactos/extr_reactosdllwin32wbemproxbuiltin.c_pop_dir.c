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
struct dirstack {size_t num_dirs; int /*<<< orphan*/ ** dirs; scalar_t__* len_dirs; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;

/* Variables and functions */

__attribute__((used)) static WCHAR *pop_dir( struct dirstack *dirstack, UINT *len )
{
    if (!dirstack->num_dirs)
    {
        *len = 0;
        return NULL;
    }
    dirstack->num_dirs--;
    *len = dirstack->len_dirs[dirstack->num_dirs];
    return dirstack->dirs[dirstack->num_dirs];
}