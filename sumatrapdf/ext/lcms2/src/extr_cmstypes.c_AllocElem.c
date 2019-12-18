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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_3__ {int /*<<< orphan*/ * Offsets; int /*<<< orphan*/ * Sizes; } ;
typedef  TYPE_1__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool AllocElem(cmsContext ContextID, _cmsDICelem* e,  cmsUInt32Number Count)
{
    e->Offsets = (cmsUInt32Number *) _cmsCalloc(ContextID, Count, sizeof(cmsUInt32Number));
    if (e->Offsets == NULL) return FALSE;

    e->Sizes = (cmsUInt32Number *) _cmsCalloc(ContextID, Count, sizeof(cmsUInt32Number));
    if (e->Sizes == NULL) {

        _cmsFree(ContextID, e -> Offsets);
        return FALSE;
    }

    return TRUE;
}