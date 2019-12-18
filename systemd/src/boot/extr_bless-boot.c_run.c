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
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
#define  VERB_ANY 132 
#define  VERB_DEFAULT 131 
 scalar_t__ detect_container () ; 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  help 130 
 int /*<<< orphan*/  is_efi_boot () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int parse_argv (int,char**) ; 
#define  verb_set 129 
#define  verb_status 128 

__attribute__((used)) static int run(int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "help",          VERB_ANY, VERB_ANY, 0,            help        },
                { "status",        VERB_ANY, 1,        VERB_DEFAULT, verb_status },
                { "good",          VERB_ANY, 1,        0,            verb_set    },
                { "bad",           VERB_ANY, 1,        0,            verb_set    },
                { "indeterminate", VERB_ANY, 1,        0,            verb_set    },
                {}
        };

        int r;

        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        if (detect_container() > 0)
                return log_error_errno(SYNTHETIC_ERRNO(EOPNOTSUPP),
                                       "Marking a boot is not supported in containers.");

        if (!is_efi_boot())
                return log_error_errno(SYNTHETIC_ERRNO(EOPNOTSUPP),
                                       "Marking a boot is only supported on EFI systems.");

        return dispatch_verb(argc, argv, verbs, NULL);
}