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

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOLATILE_OVERLAY ; 
 int /*<<< orphan*/  VOLATILE_YES ; 
 int /*<<< orphan*/  arg_read_only ; 
 int /*<<< orphan*/  arg_volatile_mode ; 

__attribute__((used)) static bool etc_writable(void) {
        return !arg_read_only || IN_SET(arg_volatile_mode, VOLATILE_YES, VOLATILE_OVERLAY);
}