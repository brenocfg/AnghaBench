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
typedef  int gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ SDEventSource ;
typedef  int /*<<< orphan*/  GSource ;

/* Variables and functions */
 scalar_t__ sd_event_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean event_check(GSource *source) {
  return sd_event_wait(((SDEventSource *)source)->event, 0) > 0;
}