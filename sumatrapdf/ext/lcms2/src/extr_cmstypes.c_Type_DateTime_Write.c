#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
struct _cms_typehandler_struct {int dummy; } ;
typedef  struct _cms_typehandler_struct* cmsUInt32Number ;
struct TYPE_4__ {int /*<<< orphan*/  (* Write ) (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsDateTimeNumber ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsEncodeDateTimeNumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool  Type_DateTime_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    struct tm * DateTime = (struct tm*) Ptr;
    cmsDateTimeNumber timestamp;

    _cmsEncodeDateTimeNumber(ContextID, &timestamp, DateTime);
    if (!io ->Write(ContextID, io, sizeof(cmsDateTimeNumber), &timestamp)) return FALSE;

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
    cmsUNUSED_PARAMETER(self);
}