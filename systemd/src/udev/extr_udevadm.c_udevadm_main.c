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
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 138 
#define  builtin_main 137 
#define  control_main 136 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  help_main 135 
#define  hwdb_main 134 
#define  info_main 133 
#define  monitor_main 132 
#define  settle_main 131 
#define  test_main 130 
#define  trigger_main 129 
#define  version_main 128 

__attribute__((used)) static int udevadm_main(int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "info",         VERB_ANY, VERB_ANY, 0, info_main    },
                { "trigger",      VERB_ANY, VERB_ANY, 0, trigger_main },
                { "settle",       VERB_ANY, VERB_ANY, 0, settle_main  },
                { "control",      VERB_ANY, VERB_ANY, 0, control_main },
                { "monitor",      VERB_ANY, VERB_ANY, 0, monitor_main },
                { "hwdb",         VERB_ANY, VERB_ANY, 0, hwdb_main    },
                { "test",         VERB_ANY, VERB_ANY, 0, test_main    },
                { "test-builtin", VERB_ANY, VERB_ANY, 0, builtin_main },
                { "version",      VERB_ANY, VERB_ANY, 0, version_main },
                { "help",         VERB_ANY, VERB_ANY, 0, help_main    },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}