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
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_3__ {int /*<<< orphan*/  DisplayValue; int /*<<< orphan*/  DisplayName; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ _cmsDICarray ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ReadOneElem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
cmsBool ReadOffsetArray(cmsContext ContextID, cmsIOHANDLER* io,  _cmsDICarray* a, cmsUInt32Number Count, cmsUInt32Number Length, cmsUInt32Number BaseOffset)
{
    cmsUInt32Number i;

    // Read column arrays
    for (i=0; i < Count; i++) {

        if (!ReadOneElem(ContextID, io, &a -> Name, i, BaseOffset)) return FALSE;
        if (!ReadOneElem(ContextID, io, &a -> Value, i, BaseOffset)) return FALSE;

        if (Length > 16) {

            if (!ReadOneElem(ContextID, io, &a ->DisplayName, i, BaseOffset)) return FALSE;

        }

        if (Length > 24) {

            if (!ReadOneElem(ContextID, io, & a -> DisplayValue, i, BaseOffset)) return FALSE;
        }
    }
    return TRUE;
}