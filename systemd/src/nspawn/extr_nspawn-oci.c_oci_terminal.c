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
struct TYPE_2__ {int /*<<< orphan*/  console_mode; } ;
typedef  TYPE_1__ Settings ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_PIPE ; 
 int /*<<< orphan*/  _CONSOLE_MODE_INVALID ; 
 scalar_t__ json_variant_boolean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_terminal(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        Settings *s = userdata;

        /* If not specified, or set to true, we'll default to either an interactive or a read-only
         * console. If specified as false, we'll forcibly move to "pipe" mode though. */
        s->console_mode = json_variant_boolean(v) ? _CONSOLE_MODE_INVALID : CONSOLE_PIPE;
        return 0;
}