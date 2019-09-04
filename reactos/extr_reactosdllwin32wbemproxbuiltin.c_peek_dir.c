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
struct dirstack {int num_dirs; int /*<<< orphan*/  const** dirs; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */

__attribute__((used)) static const WCHAR *peek_dir( struct dirstack *dirstack )
{
    if (!dirstack->num_dirs) return NULL;
    return dirstack->dirs[dirstack->num_dirs - 1];
}