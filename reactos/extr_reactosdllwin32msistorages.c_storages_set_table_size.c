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
typedef  int UINT ;
struct TYPE_3__ {int max_storages; int /*<<< orphan*/  storages; } ;
typedef  int /*<<< orphan*/  STORAGE ;
typedef  TYPE_1__ MSISTORAGESVIEW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  msi_realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL storages_set_table_size(MSISTORAGESVIEW *sv, UINT size)
{
    if (size >= sv->max_storages)
    {
        sv->max_storages *= 2;
        sv->storages = msi_realloc(sv->storages, sv->max_storages * sizeof(STORAGE *));
        if (!sv->storages)
            return FALSE;
    }

    return TRUE;
}