#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int perpetual; int default_dependencies; scalar_t__ description; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_8__ {int /*<<< orphan*/  std_input; int /*<<< orphan*/  std_output; } ;
struct TYPE_10__ {TYPE_1__ exec_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_INPUT_NULL ; 
 int /*<<< orphan*/  EXEC_OUTPUT_NULL ; 
 TYPE_6__* MOUNT (TYPE_2__*) ; 
 int /*<<< orphan*/  SPECIAL_ROOT_MOUNT ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ strdup (char*) ; 
 int /*<<< orphan*/  unit_has_name (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_load_root_mount(Unit *u) {
        assert(u);

        if (!unit_has_name(u, SPECIAL_ROOT_MOUNT))
                return;

        u->perpetual = true;
        u->default_dependencies = false;

        /* The stdio/kmsg bridge socket is on /, in order to avoid a dep loop, don't use kmsg logging for -.mount */
        MOUNT(u)->exec_context.std_output = EXEC_OUTPUT_NULL;
        MOUNT(u)->exec_context.std_input = EXEC_INPUT_NULL;

        if (!u->description)
                u->description = strdup("Root Mount");
}