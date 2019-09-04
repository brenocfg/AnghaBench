#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_3__ {size_t unique_actions_count; int /*<<< orphan*/ * unique_actions; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

BOOL msi_action_is_unique( const MSIPACKAGE *package, const WCHAR *action )
{
    UINT i;

    for (i = 0; i < package->unique_actions_count; i++)
    {
        if (!strcmpW( package->unique_actions[i], action )) return TRUE;
    }
    return FALSE;
}