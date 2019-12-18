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
struct TYPE_3__ {char* member_0; int const member_1; int const member_2; int member_3; int /*<<< orphan*/  const member_4; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 163 
#define  VERB_DEFAULT 162 
#define  VERB_ONLINE_ONLY 161 
#define  add_dependency 160 
#define  cancel_job 159 
#define  cat 158 
#define  check_unit_active 157 
#define  check_unit_failed 156 
#define  clean_unit 155 
#define  daemon_reload 154 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  edit 153 
#define  enable_unit 152 
#define  get_default 151 
#define  import_environment 150 
#define  is_system_running 149 
#define  kill_unit 148 
#define  list_dependencies 147 
#define  list_jobs 146 
#define  list_machines 145 
#define  list_sockets 144 
#define  list_timers 143 
#define  list_unit_files 142 
#define  list_units 141 
#define  preset_all 140 
#define  reset_failed 139 
#define  set_default 138 
#define  set_environment 137 
#define  set_property 136 
#define  show 135 
#define  show_environment 134 
#define  start_special 133 
#define  start_system_special 132 
#define  start_unit 131 
#define  switch_root 130 
#define  trivial_method 129 
#define  unit_is_enabled 128 

__attribute__((used)) static int systemctl_main(int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "list-units",            VERB_ANY, VERB_ANY, VERB_DEFAULT|VERB_ONLINE_ONLY, list_units },
                { "list-unit-files",       VERB_ANY, VERB_ANY, 0,                list_unit_files      },
                { "list-sockets",          VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, list_sockets         },
                { "list-timers",           VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, list_timers          },
                { "list-jobs",             VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, list_jobs            },
                { "list-machines",         VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, list_machines        },
                { "clear-jobs",            VERB_ANY, 1,        VERB_ONLINE_ONLY, trivial_method       },
                { "cancel",                VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, cancel_job           },
                { "start",                 2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "stop",                  2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "condstop",              2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           }, /* For compatibility with ALTLinux */
                { "reload",                2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "restart",               2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "try-restart",           2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "reload-or-restart",     2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "reload-or-try-restart", 2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           }, /* For compatibility with old systemctl <= 228 */
                { "try-reload-or-restart", 2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           },
                { "force-reload",          2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           }, /* For compatibility with SysV */
                { "condreload",            2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           }, /* For compatibility with ALTLinux */
                { "condrestart",           2,        VERB_ANY, VERB_ONLINE_ONLY, start_unit           }, /* For compatibility with RH */
                { "isolate",               2,        2,        VERB_ONLINE_ONLY, start_unit           },
                { "kill",                  2,        VERB_ANY, VERB_ONLINE_ONLY, kill_unit            },
                { "clean",                 2,        VERB_ANY, VERB_ONLINE_ONLY, clean_unit           },
                { "is-active",             2,        VERB_ANY, VERB_ONLINE_ONLY, check_unit_active    },
                { "check",                 2,        VERB_ANY, VERB_ONLINE_ONLY, check_unit_active    }, /* deprecated alias of is-active */
                { "is-failed",             2,        VERB_ANY, VERB_ONLINE_ONLY, check_unit_failed    },
                { "show",                  VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, show                 },
                { "cat",                   2,        VERB_ANY, VERB_ONLINE_ONLY, cat                  },
                { "status",                VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, show                 },
                { "help",                  VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, show                 },
                { "daemon-reload",         VERB_ANY, 1,        VERB_ONLINE_ONLY, daemon_reload        },
                { "daemon-reexec",         VERB_ANY, 1,        VERB_ONLINE_ONLY, daemon_reload        },
                { "show-environment",      VERB_ANY, 1,        VERB_ONLINE_ONLY, show_environment     },
                { "set-environment",       2,        VERB_ANY, VERB_ONLINE_ONLY, set_environment      },
                { "unset-environment",     2,        VERB_ANY, VERB_ONLINE_ONLY, set_environment      },
                { "import-environment",    VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, import_environment   },
                { "halt",                  VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "poweroff",              VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "reboot",                VERB_ANY, 2,        VERB_ONLINE_ONLY, start_system_special },
                { "kexec",                 VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "suspend",               VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "hibernate",             VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "hybrid-sleep",          VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "suspend-then-hibernate",VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "default",               VERB_ANY, 1,        VERB_ONLINE_ONLY, start_special        },
                { "rescue",                VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "emergency",             VERB_ANY, 1,        VERB_ONLINE_ONLY, start_system_special },
                { "exit",                  VERB_ANY, 2,        VERB_ONLINE_ONLY, start_special        },
                { "reset-failed",          VERB_ANY, VERB_ANY, VERB_ONLINE_ONLY, reset_failed         },
                { "enable",                2,        VERB_ANY, 0,                enable_unit          },
                { "disable",               2,        VERB_ANY, 0,                enable_unit          },
                { "is-enabled",            2,        VERB_ANY, 0,                unit_is_enabled      },
                { "reenable",              2,        VERB_ANY, 0,                enable_unit          },
                { "preset",                2,        VERB_ANY, 0,                enable_unit          },
                { "preset-all",            VERB_ANY, 1,        0,                preset_all           },
                { "mask",                  2,        VERB_ANY, 0,                enable_unit          },
                { "unmask",                2,        VERB_ANY, 0,                enable_unit          },
                { "link",                  2,        VERB_ANY, 0,                enable_unit          },
                { "revert",                2,        VERB_ANY, 0,                enable_unit          },
                { "switch-root",           2,        VERB_ANY, VERB_ONLINE_ONLY, switch_root          },
                { "list-dependencies",     VERB_ANY, 2,        VERB_ONLINE_ONLY, list_dependencies    },
                { "set-default",           2,        2,        0,                set_default          },
                { "get-default",           VERB_ANY, 1,        0,                get_default          },
                { "set-property",          3,        VERB_ANY, VERB_ONLINE_ONLY, set_property         },
                { "is-system-running",     VERB_ANY, 1,        0,                is_system_running    },
                { "add-wants",             3,        VERB_ANY, 0,                add_dependency       },
                { "add-requires",          3,        VERB_ANY, 0,                add_dependency       },
                { "edit",                  2,        VERB_ANY, VERB_ONLINE_ONLY, edit                 },
                {}
        };

        return dispatch_verb(argc, argv, verbs, NULL);
}