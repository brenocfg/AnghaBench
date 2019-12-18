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
struct TYPE_3__ {char* member_0; int const member_1; int const member_2; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 159 
#define  VERB_DEFAULT 158 
#define  bind_mount 157 
#define  cancel_transfer 156 
#define  clean_images 155 
#define  clone_image 154 
#define  copy_files 153 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  enable_machine 152 
#define  export_raw 151 
#define  export_tar 150 
#define  help 149 
#define  import_fs 148 
#define  import_raw 147 
#define  import_tar 146 
#define  kill_machine 145 
#define  list_images 144 
#define  list_machines 143 
#define  list_transfers 142 
#define  login_machine 141 
#define  poweroff_machine 140 
#define  pull_raw 139 
#define  pull_tar 138 
#define  read_only_image 137 
#define  reboot_machine 136 
#define  remove_image 135 
#define  rename_image 134 
#define  set_limit 133 
#define  shell_machine 132 
#define  show_image 131 
#define  show_machine 130 
#define  start_machine 129 
#define  terminate_machine 128 

__attribute__((used)) static int machinectl_main(int argc, char *argv[], sd_bus *bus) {

        static const Verb verbs[] = {
                { "help",            VERB_ANY, VERB_ANY, 0,            help              },
                { "list",            VERB_ANY, 1,        VERB_DEFAULT, list_machines     },
                { "list-images",     VERB_ANY, 1,        0,            list_images       },
                { "status",          2,        VERB_ANY, 0,            show_machine      },
                { "image-status",    VERB_ANY, VERB_ANY, 0,            show_image        },
                { "show",            VERB_ANY, VERB_ANY, 0,            show_machine      },
                { "show-image",      VERB_ANY, VERB_ANY, 0,            show_image        },
                { "terminate",       2,        VERB_ANY, 0,            terminate_machine },
                { "reboot",          2,        VERB_ANY, 0,            reboot_machine    },
                { "poweroff",        2,        VERB_ANY, 0,            poweroff_machine  },
                { "stop",            2,        VERB_ANY, 0,            poweroff_machine  }, /* Convenience alias */
                { "kill",            2,        VERB_ANY, 0,            kill_machine      },
                { "login",           VERB_ANY, 2,        0,            login_machine     },
                { "shell",           VERB_ANY, VERB_ANY, 0,            shell_machine     },
                { "bind",            3,        4,        0,            bind_mount        },
                { "copy-to",         3,        4,        0,            copy_files        },
                { "copy-from",       3,        4,        0,            copy_files        },
                { "remove",          2,        VERB_ANY, 0,            remove_image      },
                { "rename",          3,        3,        0,            rename_image      },
                { "clone",           3,        3,        0,            clone_image       },
                { "read-only",       2,        3,        0,            read_only_image   },
                { "start",           2,        VERB_ANY, 0,            start_machine     },
                { "enable",          2,        VERB_ANY, 0,            enable_machine    },
                { "disable",         2,        VERB_ANY, 0,            enable_machine    },
                { "import-tar",      2,        3,        0,            import_tar        },
                { "import-raw",      2,        3,        0,            import_raw        },
                { "import-fs",       2,        3,        0,            import_fs         },
                { "export-tar",      2,        3,        0,            export_tar        },
                { "export-raw",      2,        3,        0,            export_raw        },
                { "pull-tar",        2,        3,        0,            pull_tar          },
                { "pull-raw",        2,        3,        0,            pull_raw          },
                { "list-transfers",  VERB_ANY, 1,        0,            list_transfers    },
                { "cancel-transfer", 2,        VERB_ANY, 0,            cancel_transfer   },
                { "set-limit",       2,        3,        0,            set_limit         },
                { "clean",           VERB_ANY, 1,        0,            clean_images      },
                {}
        };

        return dispatch_verb(argc, argv, verbs, bus);
}