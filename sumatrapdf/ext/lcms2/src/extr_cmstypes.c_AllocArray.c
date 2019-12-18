#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {int /*<<< orphan*/  DisplayValue; int /*<<< orphan*/  DisplayName; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ _cmsDICarray ;

/* Variables and functions */
 int /*<<< orphan*/  AllocElem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeArray (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsBool AllocArray(cmsContext ContextID, _cmsDICarray* a, cmsUInt32Number Count, cmsUInt32Number Length)
{
    // Empty values
    memset(a, 0, sizeof(_cmsDICarray));

    // On depending on record size, create column arrays
    if (!AllocElem(ContextID, &a ->Name, Count)) goto Error;
    if (!AllocElem(ContextID, &a ->Value, Count)) goto Error;

    if (Length > 16) {
        if (!AllocElem(ContextID, &a -> DisplayName, Count)) goto Error;

    }
    if (Length > 24) {
        if (!AllocElem(ContextID, &a ->DisplayValue, Count)) goto Error;
    }
    return TRUE;

Error:
    FreeArray(ContextID, a);
    return FALSE;
}