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
struct TYPE_3__ {char* member_0; int const member_1; int member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 140 
#define  VERB_DEFAULT 139 
#define  call 138 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  emit_signal 137 
#define  get_property 136 
#define  introspect 135 
#define  list_bus_names 134 
#define  set_property 133 
#define  status 132 
#define  tree 131 
#define  verb_capture 130 
#define  verb_help 129 
#define  verb_monitor 128 

__attribute__((used)) static int busctl_main(int argc, char *argv[]) {

        static const Verb verbs[] = {
                { "list",         VERB_ANY, 1,        VERB_DEFAULT, list_bus_names },
                { "status",       VERB_ANY, 2,        0,            status         },
                { "monitor",      VERB_ANY, VERB_ANY, 0,            verb_monitor   },
                { "capture",      VERB_ANY, VERB_ANY, 0,            verb_capture   },
                { "tree",         VERB_ANY, VERB_ANY, 0,            tree           },
                { "introspect",   3,        4,        0,            introspect     },
                { "call",         5,        VERB_ANY, 0,            call           },
                { "emit",         4,        VERB_ANY, 0,            emit_signal    },
                { "get-property", 5,        VERB_ANY, 0,            get_property   },
                { "set-property", 6,        VERB_ANY, 0,            set_property   },
                { "help",         VERB_ANY, VERB_ANY, 0,            verb_help      },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}