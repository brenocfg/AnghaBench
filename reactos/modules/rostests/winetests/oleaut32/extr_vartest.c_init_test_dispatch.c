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
typedef  int /*<<< orphan*/  VARTYPE ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  result; int /*<<< orphan*/  vt; TYPE_1__ IDispatch_iface; } ;
typedef  TYPE_2__ DummyDispatch ;

/* Variables and functions */
 int /*<<< orphan*/  DummyDispatch_VTable ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static void init_test_dispatch(VARTYPE vt, DummyDispatch *dispatch)
{
    dispatch->IDispatch_iface.lpVtbl = &DummyDispatch_VTable;
    dispatch->vt = vt;
    dispatch->result = S_OK;
}