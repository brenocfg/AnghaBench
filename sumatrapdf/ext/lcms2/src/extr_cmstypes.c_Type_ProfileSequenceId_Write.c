#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
struct TYPE_8__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ cmsSEQ ;
struct TYPE_9__ {scalar_t__ (* Tell ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsTagBase ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WritePositionTable (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteSeqID ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static
cmsBool  Type_ProfileSequenceId_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsSEQ* Seq = (cmsSEQ*) Ptr;
    cmsUInt32Number BaseOffset;

    // Keep the base offset
    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    // This is the table count
    if (!_cmsWriteUInt32Number(ContextID, io, Seq ->n)) return FALSE;

    // This is the position table and content
    if (!WritePositionTable(ContextID, self, io, 0, Seq ->n, BaseOffset, Seq, WriteSeqID)) return FALSE;

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
}