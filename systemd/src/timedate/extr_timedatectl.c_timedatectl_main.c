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
struct TYPE_3__ {char* member_0; int const member_1; int member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 141 
#define  VERB_DEFAULT 140 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  list_timezones 139 
#define  set_local_rtc 138 
#define  set_ntp 137 
#define  set_time 136 
#define  set_timezone 135 
#define  show_properties 134 
#define  show_status 133 
#define  show_timesync 132 
#define  show_timesync_status 131 
#define  verb_help 130 
#define  verb_ntp_servers 129 
#define  verb_revert 128 

__attribute__((used)) static int timedatectl_main(sd_bus *bus, int argc, char *argv[]) {
        static const Verb verbs[] = {
                { "status",          VERB_ANY, 1,        VERB_DEFAULT, show_status          },
                { "show",            VERB_ANY, 1,        0,            show_properties      },
                { "set-time",        2,        2,        0,            set_time             },
                { "set-timezone",    2,        2,        0,            set_timezone         },
                { "list-timezones",  VERB_ANY, 1,        0,            list_timezones       },
                { "set-local-rtc",   2,        2,        0,            set_local_rtc        },
                { "set-ntp",         2,        2,        0,            set_ntp              },
                { "timesync-status", VERB_ANY, 1,        0,            show_timesync_status },
                { "show-timesync",   VERB_ANY, 1,        0,            show_timesync        },
                { "ntp-servers",     3,        VERB_ANY, 0,            verb_ntp_servers     },
                { "revert",          2,        2,        0,            verb_revert          },
                { "help",            VERB_ANY, VERB_ANY, 0,            verb_help            }, /* Not documented, but supported since it is created. */
                {}
        };

        return dispatch_verb(argc, argv, verbs, bus);
}