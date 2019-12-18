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
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
struct TYPE_5__ {int Flag; int nChannels; TYPE_1__* Channels; } ;
typedef  TYPE_2__ cmsScreening ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_4__ {int SpotShape; int /*<<< orphan*/  ScreenAngle; int /*<<< orphan*/  Frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsRead15Fixed16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (size_t) ; 

__attribute__((used)) static
void *Type_Screening_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsScreening* sc = NULL;
    cmsUInt32Number i;

    sc = (cmsScreening*) _cmsMallocZero(ContextID, sizeof(cmsScreening));
    if (sc == NULL) return NULL;

    *nItems = 0;

    if (!_cmsReadUInt32Number(ContextID, io, &sc ->Flag)) goto Error;
    if (!_cmsReadUInt32Number(ContextID, io, &sc ->nChannels)) goto Error;

    if (sc ->nChannels > cmsMAXCHANNELS - 1)
        sc ->nChannels = cmsMAXCHANNELS - 1;

    for (i=0; i < sc ->nChannels; i++) {

        if (!_cmsRead15Fixed16Number(ContextID, io, &sc ->Channels[i].Frequency)) goto Error;
        if (!_cmsRead15Fixed16Number(ContextID, io, &sc ->Channels[i].ScreenAngle)) goto Error;
        if (!_cmsReadUInt32Number(ContextID, io, &sc ->Channels[i].SpotShape)) goto Error;
    }


    *nItems = 1;

    return (void*) sc;

Error:
    if (sc != NULL)
        _cmsFree(ContextID, sc);

    return NULL;
    cmsUNUSED_PARAMETER(self);
    cmsUNUSED_PARAMETER(SizeOfTag);
}