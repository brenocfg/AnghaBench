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
#define  VERB_ANY 145 
#define  VERB_DEFAULT 144 
#define  activate 143 
#define  attach 142 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  enable_linger 141 
#define  flush_devices 140 
#define  help 139 
#define  kill_session 138 
#define  kill_user 137 
#define  list_seats 136 
#define  list_sessions 135 
#define  list_users 134 
#define  lock_sessions 133 
#define  show_seat 132 
#define  show_session 131 
#define  show_user 130 
#define  terminate_seat 129 
#define  terminate_user 128 

__attribute__((used)) static int loginctl_main(int argc, char *argv[], sd_bus *bus) {

        static const Verb verbs[] = {
                { "help",              VERB_ANY, VERB_ANY, 0,            help              },
                { "list-sessions",     VERB_ANY, 1,        VERB_DEFAULT, list_sessions     },
                { "session-status",    VERB_ANY, VERB_ANY, 0,            show_session      },
                { "show-session",      VERB_ANY, VERB_ANY, 0,            show_session      },
                { "activate",          VERB_ANY, 2,        0,            activate          },
                { "lock-session",      VERB_ANY, VERB_ANY, 0,            activate          },
                { "unlock-session",    VERB_ANY, VERB_ANY, 0,            activate          },
                { "lock-sessions",     VERB_ANY, 1,        0,            lock_sessions     },
                { "unlock-sessions",   VERB_ANY, 1,        0,            lock_sessions     },
                { "terminate-session", 2,        VERB_ANY, 0,            activate          },
                { "kill-session",      2,        VERB_ANY, 0,            kill_session      },
                { "list-users",        VERB_ANY, 1,        0,            list_users        },
                { "user-status",       VERB_ANY, VERB_ANY, 0,            show_user         },
                { "show-user",         VERB_ANY, VERB_ANY, 0,            show_user         },
                { "enable-linger",     VERB_ANY, VERB_ANY, 0,            enable_linger     },
                { "disable-linger",    VERB_ANY, VERB_ANY, 0,            enable_linger     },
                { "terminate-user",    2,        VERB_ANY, 0,            terminate_user    },
                { "kill-user",         2,        VERB_ANY, 0,            kill_user         },
                { "list-seats",        VERB_ANY, 1,        0,            list_seats        },
                { "seat-status",       VERB_ANY, VERB_ANY, 0,            show_seat         },
                { "show-seat",         VERB_ANY, VERB_ANY, 0,            show_seat         },
                { "attach",            3,        VERB_ANY, 0,            attach            },
                { "flush-devices",     VERB_ANY, 1,        0,            flush_devices     },
                { "terminate-seat",    2,        VERB_ANY, 0,            terminate_seat    },
                {}
        };

        return dispatch_verb(argc, argv, verbs, bus);
}