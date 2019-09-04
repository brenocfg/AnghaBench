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
typedef  size_t UINT ;
struct TYPE_3__ {size_t num_langids; scalar_t__* langids; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  scalar_t__ LANGID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL match_language( MSIPACKAGE *package, LANGID langid )
{
    UINT i;

    if (!package->num_langids || !langid) return TRUE;
    for (i = 0; i < package->num_langids; i++)
    {
        if (package->langids[i] == langid) return TRUE;
    }
    return FALSE;
}