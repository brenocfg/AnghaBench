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
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AKEYCODE_POWER ; 
 int /*<<< orphan*/  send_keycode (struct controller*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static inline void
action_power(struct controller *controller, int actions) {
    send_keycode(controller, AKEYCODE_POWER, actions, "POWER");
}