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
typedef  int /*<<< orphan*/  dispex_data_t ;
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_dispex_static_data ; 
 int /*<<< orphan*/ * preprocess_dispex_data (TYPE_2__*) ; 

__attribute__((used)) static dispex_data_t *get_dispex_data(DispatchEx *This)
{
    if(This->data->data)
        return This->data->data;

    EnterCriticalSection(&cs_dispex_static_data);

    if(!This->data->data)
        This->data->data = preprocess_dispex_data(This);

    LeaveCriticalSection(&cs_dispex_static_data);

    return This->data->data;
}