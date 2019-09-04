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
typedef  int /*<<< orphan*/  ole_priv_data ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_2__ IEnumFORMATETC_iface; int /*<<< orphan*/  pos; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ enum_fmtetc ;
typedef  int /*<<< orphan*/  UINT ;
typedef  TYPE_2__ IEnumFORMATETC ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  efvt ; 

__attribute__((used)) static HRESULT enum_fmtetc_construct(ole_priv_data *data, UINT pos, IEnumFORMATETC **obj)
{
  enum_fmtetc* ef;

  *obj = NULL;
  ef = HeapAlloc(GetProcessHeap(), 0, sizeof(*ef));
  if (!ef) return E_OUTOFMEMORY;

  ef->ref = 1;
  ef->IEnumFORMATETC_iface.lpVtbl = &efvt;
  ef->data = data;
  ef->pos = pos;

  TRACE("(%p)->()\n", ef);
  *obj = &ef->IEnumFORMATETC_iface;
  return S_OK;
}