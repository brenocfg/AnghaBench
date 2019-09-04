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
struct TYPE_5__ {scalar_t__ id; } ;
typedef  TYPE_1__ sink_entry_t ;
struct TYPE_6__ {int handlers_cnt; TYPE_1__* handlers; } ;
typedef  TYPE_2__ PHEventSink ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */

__attribute__((used)) static sink_entry_t *find_sink_entry(PHEventSink *sink, DISPID id)
{
    sink_entry_t *iter;

    for(iter = sink->handlers; iter < sink->handlers+sink->handlers_cnt; iter++) {
        if(iter->id == id)
            return iter;
    }

    return NULL;
}