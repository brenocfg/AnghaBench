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
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 132 
#define  VERB_DEFAULT 131 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  dump_core 130 
#define  dump_list 129 
#define  run_debug 128 

__attribute__((used)) static int coredumpctl_main(int argc, char *argv[]) {

        static const Verb verbs[] = {
                { "list",  VERB_ANY, VERB_ANY, VERB_DEFAULT, dump_list },
                { "info",  VERB_ANY, VERB_ANY, 0,            dump_list },
                { "dump",  VERB_ANY, VERB_ANY, 0,            dump_core },
                { "debug", VERB_ANY, VERB_ANY, 0,            run_debug },
                { "gdb",   VERB_ANY, VERB_ANY, 0,            run_debug },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}