#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  cDims; TYPE_1__* rgsabound; } ;
struct TYPE_4__ {int cElements; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  TYPE_2__ SAFEARRAY ;

/* Variables and functions */

__attribute__((used)) static ULONG get_cell_count(const SAFEARRAY *psa)
{
    const SAFEARRAYBOUND* psab = psa->rgsabound;
    USHORT cCount = psa->cDims;
    ULONG ulNumCells = 1;

    while (cCount--)
    {
         if (!psab->cElements)
            return 0;
        ulNumCells *= psab->cElements;
        psab++;
    }
    return ulNumCells;
}