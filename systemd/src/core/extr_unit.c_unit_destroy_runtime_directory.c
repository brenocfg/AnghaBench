#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_10__ {scalar_t__ runtime_directory_preserve_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/ * prefix; } ;
typedef  TYPE_3__ ExecContext ;

/* Variables and functions */
 size_t EXEC_DIRECTORY_RUNTIME ; 
 scalar_t__ EXEC_PRESERVE_NO ; 
 scalar_t__ EXEC_PRESERVE_RESTART ; 
 int /*<<< orphan*/  exec_context_destroy_runtime_directory (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_will_restart (TYPE_2__*) ; 

void unit_destroy_runtime_directory(Unit *u, const ExecContext *context) {
        if (context->runtime_directory_preserve_mode == EXEC_PRESERVE_NO ||
            (context->runtime_directory_preserve_mode == EXEC_PRESERVE_RESTART && !unit_will_restart(u)))
                exec_context_destroy_runtime_directory(context, u->manager->prefix[EXEC_DIRECTORY_RUNTIME]);
}