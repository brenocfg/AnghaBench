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
struct _cms_typehandler_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int cmsUInt32Number ;
struct TYPE_5__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static
void *Type_ColorantOrderType_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsUInt8Number* ColorantOrder;
    cmsUInt32Number Count;
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;
    if (!_cmsReadUInt32Number(ContextID, io, &Count)) return NULL;
    if (Count > cmsMAXCHANNELS) return NULL;

    ColorantOrder = (cmsUInt8Number*) _cmsCalloc(ContextID, cmsMAXCHANNELS, sizeof(cmsUInt8Number));
    if (ColorantOrder == NULL) return NULL;

    // We use FF as end marker
    memset(ColorantOrder, 0xFF, cmsMAXCHANNELS * sizeof(cmsUInt8Number));

    if (io ->Read(ContextID, io, ColorantOrder, sizeof(cmsUInt8Number), Count) != Count) {

        _cmsFree(ContextID, (void*) ColorantOrder);
        return NULL;
    }

    *nItems = 1;
    return (void*) ColorantOrder;

    cmsUNUSED_PARAMETER(SizeOfTag);
}