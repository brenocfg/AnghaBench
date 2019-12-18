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
typedef  int /*<<< orphan*/  sd_device ;
typedef  int /*<<< orphan*/  UdevRules ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  log_rule_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  log_rule_error_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,char const*,char const*) ; 

__attribute__((used)) static void log_unknown_owner(sd_device *dev, UdevRules *rules, int error, const char *entity, const char *name) {
        if (IN_SET(abs(error), ENOENT, ESRCH))
                log_rule_error(dev, rules, "Unknown %s '%s', ignoring", entity, name);
        else
                log_rule_error_errno(dev, rules, error, "Failed to resolve %s '%s', ignoring: %m", entity, name);
}