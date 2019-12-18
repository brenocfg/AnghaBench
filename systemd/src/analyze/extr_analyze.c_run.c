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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
#define  VERB_ANY 154 
#define  VERB_DEFAULT 153 
#define  analyze_blame 152 
#define  analyze_critical_chain 151 
#define  analyze_plot 150 
#define  analyze_time 149 
#define  cat_config 148 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  do_condition 147 
#define  do_security 146 
#define  do_unit_files 145 
#define  do_verify 144 
#define  dot 143 
#define  dump 142 
#define  dump_exit_status 141 
#define  dump_syscall_filters 140 
#define  dump_timespan 139 
#define  dump_unit_paths 138 
#define  get_log_level 137 
#define  get_log_target 136 
#define  get_or_set_log_level 135 
#define  get_or_set_log_target 134 
#define  help 133 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_show_color (int) ; 
 int parse_argv (int,char**) ; 
#define  service_watchdogs 132 
#define  set_log_level 131 
#define  set_log_target 130 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
#define  test_calendar 129 
#define  test_timestamp 128 

__attribute__((used)) static int run(int argc, char *argv[]) {

        static const Verb verbs[] = {
                { "help",              VERB_ANY, VERB_ANY, 0,            help                   },
                { "time",              VERB_ANY, 1,        VERB_DEFAULT, analyze_time           },
                { "blame",             VERB_ANY, 1,        0,            analyze_blame          },
                { "critical-chain",    VERB_ANY, VERB_ANY, 0,            analyze_critical_chain },
                { "plot",              VERB_ANY, 1,        0,            analyze_plot           },
                { "dot",               VERB_ANY, VERB_ANY, 0,            dot                    },
                { "log-level",         VERB_ANY, 2,        0,            get_or_set_log_level   },
                { "log-target",        VERB_ANY, 2,        0,            get_or_set_log_target  },
                /* The following four verbs are deprecated aliases */
                { "set-log-level",     2,        2,        0,            set_log_level          },
                { "get-log-level",     VERB_ANY, 1,        0,            get_log_level          },
                { "set-log-target",    2,        2,        0,            set_log_target         },
                { "get-log-target",    VERB_ANY, 1,        0,            get_log_target         },
                { "dump",              VERB_ANY, 1,        0,            dump                   },
                { "cat-config",        2,        VERB_ANY, 0,            cat_config             },
                { "unit-files",        VERB_ANY, VERB_ANY, 0,            do_unit_files          },
                { "unit-paths",        1,        1,        0,            dump_unit_paths        },
                { "exit-status",       VERB_ANY, VERB_ANY, 0,            dump_exit_status       },
                { "syscall-filter",    VERB_ANY, VERB_ANY, 0,            dump_syscall_filters   },
                { "condition",         2,        VERB_ANY, 0,            do_condition           },
                { "verify",            2,        VERB_ANY, 0,            do_verify              },
                { "calendar",          2,        VERB_ANY, 0,            test_calendar          },
                { "timestamp",         2,        VERB_ANY, 0,            test_timestamp         },
                { "timespan",          2,        VERB_ANY, 0,            dump_timespan          },
                { "service-watchdogs", VERB_ANY, 2,        0,            service_watchdogs      },
                { "security",          VERB_ANY, VERB_ANY, 0,            do_security            },
                {}
        };

        int r;

        setlocale(LC_ALL, "");
        setlocale(LC_NUMERIC, "C"); /* we want to format/parse floats in C style */

        log_show_color(true);
        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        return dispatch_verb(argc, argv, verbs, NULL);
}