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
struct TYPE_3__ {char* member_0; int const member_1; int const member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 137 
#define  VERB_DEFAULT 136 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  link_delete 135 
#define  link_lldp_status 134 
#define  link_renew 133 
#define  link_status 132 
#define  list_address_labels 131 
#define  list_links 130 
#define  verb_reconfigure 129 
#define  verb_reload 128 

__attribute__((used)) static int networkctl_main(int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "list",        VERB_ANY, VERB_ANY, VERB_DEFAULT, list_links          },
                { "status",      VERB_ANY, VERB_ANY, 0,            link_status         },
                { "lldp",        VERB_ANY, VERB_ANY, 0,            link_lldp_status    },
                { "label",       VERB_ANY, VERB_ANY, 0,            list_address_labels },
                { "delete",      2,        VERB_ANY, 0,            link_delete         },
                { "renew",       2,        VERB_ANY, 0,            link_renew          },
                { "reconfigure", 2,        VERB_ANY, 0,            verb_reconfigure    },
                { "reload",      1,        1,        0,            verb_reload         },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}