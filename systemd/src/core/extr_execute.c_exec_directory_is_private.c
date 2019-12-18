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
struct TYPE_3__ {scalar_t__ runtime_directory_preserve_mode; int /*<<< orphan*/  dynamic_user; } ;
typedef  scalar_t__ ExecDirectoryType ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 scalar_t__ EXEC_DIRECTORY_CONFIGURATION ; 
 scalar_t__ EXEC_DIRECTORY_RUNTIME ; 
 scalar_t__ EXEC_PRESERVE_NO ; 

__attribute__((used)) static bool exec_directory_is_private(const ExecContext *context, ExecDirectoryType type) {
        if (!context->dynamic_user)
                return false;

        if (type == EXEC_DIRECTORY_CONFIGURATION)
                return false;

        if (type == EXEC_DIRECTORY_RUNTIME && context->runtime_directory_preserve_mode == EXEC_PRESERVE_NO)
                return false;

        return true;
}