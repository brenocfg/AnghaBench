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
struct TYPE_3__ {char* member_0; int const member_1; int const member_2; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 138 
#define  VERB_DEFAULT 137 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  help 136 
#define  verb_install 135 
#define  verb_is_installed 134 
#define  verb_list 133 
#define  verb_random_seed 132 
#define  verb_remove 131 
#define  verb_set_default 130 
#define  verb_status 129 
#define  verb_system_options 128 

__attribute__((used)) static int bootctl_main(int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "help",           VERB_ANY, VERB_ANY, 0,            help                },
                { "status",         VERB_ANY, 1,        VERB_DEFAULT, verb_status         },
                { "install",        VERB_ANY, 1,        0,            verb_install        },
                { "update",         VERB_ANY, 1,        0,            verb_install        },
                { "remove",         VERB_ANY, 1,        0,            verb_remove         },
                { "is-installed",   VERB_ANY, 1,        0,            verb_is_installed   },
                { "list",           VERB_ANY, 1,        0,            verb_list           },
                { "set-default",    2,        2,        0,            verb_set_default    },
                { "set-oneshot",    2,        2,        0,            verb_set_default    },
                { "random-seed",    VERB_ANY, 1,        0,            verb_random_seed    },
                { "system-options", VERB_ANY, 2,        0,            verb_system_options },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}