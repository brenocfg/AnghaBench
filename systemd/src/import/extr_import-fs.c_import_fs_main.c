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
struct TYPE_3__ {char* member_0; int member_1; int const member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 130 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  help 129 
#define  import_fs 128 

__attribute__((used)) static int import_fs_main(int argc, char *argv[]) {

        static const Verb verbs[] = {
                { "help", VERB_ANY, VERB_ANY, 0, help      },
                { "run",  2,        3,        0, import_fs },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}