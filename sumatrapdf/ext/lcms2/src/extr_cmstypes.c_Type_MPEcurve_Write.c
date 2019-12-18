#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_7__ {scalar_t__ InputChannels; scalar_t__ Data; } ;
typedef  TYPE_1__ cmsStage ;
struct TYPE_8__ {scalar_t__ (* Tell ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsTagBase ;
typedef  int /*<<< orphan*/  _cmsStageToneCurvesData ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteMPECurve ; 
 int /*<<< orphan*/  WritePositionTable (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static
cmsBool  Type_MPEcurve_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsUInt32Number BaseOffset;
    cmsStage* mpe = (cmsStage*) Ptr;
    _cmsStageToneCurvesData* Curves = (_cmsStageToneCurvesData*) mpe ->Data;

    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    // Write the header. Since those are curves, input and output channels are same
    if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) mpe ->InputChannels)) return FALSE;
    if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) mpe ->InputChannels)) return FALSE;

    if (!WritePositionTable(ContextID, self, io, 0,
                                mpe ->InputChannels, BaseOffset, Curves, WriteMPECurve)) return FALSE;


    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
}