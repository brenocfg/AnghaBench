#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_event ;

/* Variables and functions */
 int /*<<< orphan*/ * SD_EVENT_DEFAULT ; 
 int /*<<< orphan*/ * default_event ; 

__attribute__((used)) static sd_event *event_resolve(sd_event *e) {
        return e == SD_EVENT_DEFAULT ? default_event : e;
}