#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  event; void* reply; void* current; void* output_buffer; void* input_buffer; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* json_variant_unref (void*) ; 
 void* mfree (void*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varlink_detach_event_sources (TYPE_1__*) ; 

__attribute__((used)) static void varlink_clear(Varlink *v) {
        assert(v);

        varlink_detach_event_sources(v);

        v->fd = safe_close(v->fd);

        v->input_buffer = mfree(v->input_buffer);
        v->output_buffer = mfree(v->output_buffer);

        v->current = json_variant_unref(v->current);
        v->reply = json_variant_unref(v->reply);

        v->event = sd_event_unref(v->event);
}