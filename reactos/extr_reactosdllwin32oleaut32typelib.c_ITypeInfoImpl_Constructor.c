#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* memidDestructor; void* memidConstructor; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int hreftype; int /*<<< orphan*/ * pcustdata_list; int /*<<< orphan*/  custdata_list; TYPE_4__ typeattr; scalar_t__ ref; TYPE_3__ ICreateTypeInfo2_iface; TYPE_2__ ITypeComp_iface; TYPE_1__ ITypeInfo2_iface; } ;
typedef  TYPE_5__ ITypeInfoImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTypeInfo2Vtbl ; 
 void* MEMBERID_NIL ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_5__*) ; 
 TYPE_5__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcompvt ; 
 int /*<<< orphan*/  tinfvt ; 

__attribute__((used)) static ITypeInfoImpl* ITypeInfoImpl_Constructor(void)
{
    ITypeInfoImpl *pTypeInfoImpl;

    pTypeInfoImpl = heap_alloc_zero(sizeof(ITypeInfoImpl));
    if (pTypeInfoImpl)
    {
      pTypeInfoImpl->ITypeInfo2_iface.lpVtbl = &tinfvt;
      pTypeInfoImpl->ITypeComp_iface.lpVtbl = &tcompvt;
      pTypeInfoImpl->ICreateTypeInfo2_iface.lpVtbl = &CreateTypeInfo2Vtbl;
      pTypeInfoImpl->ref = 0;
      pTypeInfoImpl->hreftype = -1;
      pTypeInfoImpl->typeattr.memidConstructor = MEMBERID_NIL;
      pTypeInfoImpl->typeattr.memidDestructor = MEMBERID_NIL;
      pTypeInfoImpl->pcustdata_list = &pTypeInfoImpl->custdata_list;
      list_init(pTypeInfoImpl->pcustdata_list);
    }
    TRACE("(%p)\n", pTypeInfoImpl);
    return pTypeInfoImpl;
}