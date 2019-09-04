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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL seen_dir( struct dirstack *dirstack, const WCHAR *path )
{
    UINT i;
    for (i = 0; i < dirstack->num_dirs; i++) if (!strcmpW( dirstack->dirs[i], path )) return TRUE;
    return FALSE;
}