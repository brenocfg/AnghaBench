#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ ExecCommand ;

/* Variables and functions */
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int log_unit_error_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_executable(Unit *u, ExecCommand *exec) {
        if (!exec)
                return 0;

        if (access(exec->path, X_OK) < 0)
                return log_unit_error_errno(u, errno, "Command %s is not executable: %m", exec->path);

        return 0;
}