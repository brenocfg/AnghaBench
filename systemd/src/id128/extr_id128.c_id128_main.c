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
#define  VERB_ANY 133 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  verb_boot_id 132 
#define  verb_help 131 
#define  verb_invocation_id 130 
#define  verb_machine_id 129 
#define  verb_new 128 

__attribute__((used)) static int id128_main(int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "new",            VERB_ANY, 1,        0,  verb_new           },
                { "machine-id",     VERB_ANY, 1,        0,  verb_machine_id    },
                { "boot-id",        VERB_ANY, 1,        0,  verb_boot_id       },
                { "invocation-id",  VERB_ANY, 1,        0,  verb_invocation_id },
                { "help",           VERB_ANY, VERB_ANY, 0,  verb_help          },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}