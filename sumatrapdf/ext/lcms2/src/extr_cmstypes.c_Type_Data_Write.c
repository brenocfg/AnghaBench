#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  struct _cms_typehandler_struct* cmsUInt32Number ;
struct TYPE_6__ {int /*<<< orphan*/  (* Write ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  flag; } ;
typedef  TYPE_2__ cmsICCData ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsBool Type_Data_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
   cmsICCData* BinData = (cmsICCData*) Ptr;

   if (!_cmsWriteUInt32Number(ContextID, io, BinData ->flag)) return FALSE;

   return io ->Write(ContextID, io, BinData ->len, BinData ->data);

   cmsUNUSED_PARAMETER(nItems);
   cmsUNUSED_PARAMETER(self);
}