#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  text; } ;
struct control_event {scalar_t__ type; TYPE_1__ text_event; } ;

/* Variables and functions */
 scalar_t__ CONTROL_EVENT_TYPE_TEXT ; 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 

void
control_event_destroy(struct control_event *event) {
    if (event->type == CONTROL_EVENT_TYPE_TEXT) {
        SDL_free(event->text_event.text);
    }
}