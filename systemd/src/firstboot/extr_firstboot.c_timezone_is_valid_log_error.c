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
 int /*<<< orphan*/  LOG_ERR ; 
 int timezone_is_valid (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool timezone_is_valid_log_error(const char *name) {
        return timezone_is_valid(name, LOG_ERR);
}