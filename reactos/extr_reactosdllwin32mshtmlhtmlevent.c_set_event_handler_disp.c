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
typedef  size_t eventid_t ;
struct TYPE_6__ {TYPE_1__** event_table; } ;
typedef  TYPE_2__ event_target_t ;
struct TYPE_5__ {int /*<<< orphan*/ * handler_prop; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EventTarget ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  alloc_handler_vector (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_event (int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* get_event_target_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_event_handler (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static HRESULT set_event_handler_disp(EventTarget *event_target, eventid_t eid, IDispatch *disp)
{
    event_target_t *data;

    remove_event_handler(event_target, eid);
    if(!disp)
        return S_OK;

    data = get_event_target_data(event_target, TRUE);
    if(!data)
        return E_OUTOFMEMORY;

    if(!alloc_handler_vector(data, eid, 0))
        return E_OUTOFMEMORY;

    data->event_table[eid]->handler_prop = disp;
    IDispatch_AddRef(disp);

    bind_event(event_target, eid);
    return S_OK;
}