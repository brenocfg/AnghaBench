#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_7__ {double Y; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {double Y; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {double Y; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_3__ Blue; TYPE_2__ Green; TYPE_1__ Red; } ;
typedef  TYPE_4__ cmsCIExyYTRIPLE ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsRead15Fixed16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int) ; 

__attribute__((used)) static
void *Type_Chromaticity_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsCIExyYTRIPLE* chrm;
    cmsUInt16Number nChans, Table;
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;
    chrm =  (cmsCIExyYTRIPLE*) _cmsMallocZero(ContextID, sizeof(cmsCIExyYTRIPLE));
    if (chrm == NULL) return NULL;

    if (!_cmsReadUInt16Number(ContextID, io, &nChans)) goto Error;

    // Let's recover from a bug introduced in early versions of lcms1
    if (nChans == 0 && SizeOfTag == 32) {

        if (!_cmsReadUInt16Number(ContextID, io, NULL)) goto Error;
        if (!_cmsReadUInt16Number(ContextID, io, &nChans)) goto Error;
    }

    if (nChans != 3) goto Error;

    if (!_cmsReadUInt16Number(ContextID, io, &Table)) goto Error;

    if (!_cmsRead15Fixed16Number(ContextID, io, &chrm ->Red.x)) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io, &chrm ->Red.y)) goto Error;

    chrm ->Red.Y = 1.0;

    if (!_cmsRead15Fixed16Number(ContextID, io, &chrm ->Green.x)) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io, &chrm ->Green.y)) goto Error;

    chrm ->Green.Y = 1.0;

    if (!_cmsRead15Fixed16Number(ContextID, io, &chrm ->Blue.x)) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io, &chrm ->Blue.y)) goto Error;

    chrm ->Blue.Y = 1.0;

    *nItems = 1;
    return (void*) chrm;

Error:
    _cmsFree(ContextID, (void*) chrm);
    return NULL;

    cmsUNUSED_PARAMETER(SizeOfTag);
}