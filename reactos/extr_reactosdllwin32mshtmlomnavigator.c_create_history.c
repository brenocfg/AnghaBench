#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; int /*<<< orphan*/ * window; TYPE_1__ IOmHistory_iface; int /*<<< orphan*/  dispex; } ;
typedef  TYPE_2__ OmHistory ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  OmHistoryVtbl ; 
 int /*<<< orphan*/  OmHistory_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT create_history(HTMLInnerWindow *window, OmHistory **ret)
{
    OmHistory *history;

    history = heap_alloc_zero(sizeof(*history));
    if(!history)
        return E_OUTOFMEMORY;

    init_dispex(&history->dispex, (IUnknown*)&history->IOmHistory_iface, &OmHistory_dispex);
    history->IOmHistory_iface.lpVtbl = &OmHistoryVtbl;
    history->ref = 1;

    history->window = window;

    *ret = history;
    return S_OK;
}