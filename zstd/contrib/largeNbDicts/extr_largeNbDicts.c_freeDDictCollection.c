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
struct TYPE_3__ {size_t nbDDict; int /*<<< orphan*/ * ddicts; } ;
typedef  TYPE_1__ ddict_collection_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeDDict (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void freeDDictCollection(ddict_collection_t ddictc)
{
    for (size_t dictNb=0; dictNb < ddictc.nbDDict; dictNb++) {
        ZSTD_freeDDict(ddictc.ddicts[dictNb]);
    }
    free(ddictc.ddicts);
}