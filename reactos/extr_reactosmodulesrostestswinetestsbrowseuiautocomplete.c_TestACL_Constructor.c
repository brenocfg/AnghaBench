#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; int limit; char const** data; int /*<<< orphan*/  expret; TYPE_2__ IACList_iface; TYPE_1__ IEnumString_iface; } ;
typedef  TYPE_3__ TestACL ;

/* Variables and functions */
 TYPE_3__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TestACLVtbl ; 
 int /*<<< orphan*/  TestACL_ACListVtbl ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

__attribute__((used)) static TestACL *TestACL_Constructor(int limit, const char **strings)
{
    TestACL *This = CoTaskMemAlloc(sizeof(TestACL));
    ZeroMemory(This, sizeof(*This));
    This->IEnumString_iface.lpVtbl = &TestACLVtbl;
    This->IACList_iface.lpVtbl = &TestACL_ACListVtbl;
    This->ref = 1;
    This->expret = S_OK;
    This->limit = limit;
    This->data = strings;
    return This;
}