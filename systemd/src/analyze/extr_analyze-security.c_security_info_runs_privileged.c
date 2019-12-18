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
struct security_info {int /*<<< orphan*/  user; scalar_t__ dynamic_user; } ;

/* Variables and functions */
 scalar_t__ STRPTR_IN_SET (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  assert (struct security_info const*) ; 
 int isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool security_info_runs_privileged(const struct security_info *i)  {
        assert(i);

        if (STRPTR_IN_SET(i->user, "0", "root"))
                return true;

        if (i->dynamic_user)
                return false;

        return isempty(i->user);
}