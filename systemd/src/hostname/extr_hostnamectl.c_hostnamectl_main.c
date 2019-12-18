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
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_3__ {char* member_0; int member_1; int member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 136 
#define  VERB_DEFAULT 135 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  set_chassis 134 
#define  set_deployment 133 
#define  set_hostname 132 
#define  set_icon_name 131 
#define  set_location 130 
#define  show_status 129 
#define  verb_help 128 

__attribute__((used)) static int hostnamectl_main(sd_bus *bus, int argc, char *argv[]) {

        static const Verb verbs[] = {
                { "status",         VERB_ANY, 1,        VERB_DEFAULT, show_status    },
                { "set-hostname",   2,        2,        0,            set_hostname   },
                { "set-icon-name",  2,        2,        0,            set_icon_name  },
                { "set-chassis",    2,        2,        0,            set_chassis    },
                { "set-deployment", 2,        2,        0,            set_deployment },
                { "set-location",   2,        2,        0,            set_location   },
                { "help",           VERB_ANY, VERB_ANY, 0,            verb_help      }, /* Not documented, but supported since it is created. */
                {}
        };

        return dispatch_verb(argc, argv, verbs, bus);
}