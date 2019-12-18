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
struct window_pane {TYPE_1__* event; } ;
struct evbuffer {int dummy; } ;
struct TYPE_2__ {struct evbuffer* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_DATA (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_LENGTH (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_parse_buffer (struct window_pane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
input_parse(struct window_pane *wp)
{
	struct evbuffer		*evb = wp->event->input;

	input_parse_buffer(wp, EVBUFFER_DATA(evb), EVBUFFER_LENGTH(evb));
	evbuffer_drain(evb, EVBUFFER_LENGTH(evb));
}