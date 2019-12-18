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
struct TYPE_3__ {char* member_0; int member_1; int member_2; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 137 
#define  VERB_DEFAULT 136 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  list_locales 135 
#define  list_vconsole_keymaps 134 
#define  list_x11_keymaps 133 
#define  set_locale 132 
#define  set_vconsole_keymap 131 
#define  set_x11_keymap 130 
#define  show_status 129 
#define  verb_help 128 

__attribute__((used)) static int localectl_main(sd_bus *bus, int argc, char *argv[]) {

        static const Verb verbs[] = {
                { "status",                   VERB_ANY, 1,        VERB_DEFAULT, show_status           },
                { "set-locale",               2,        VERB_ANY, 0,            set_locale            },
                { "list-locales",             VERB_ANY, 1,        0,            list_locales          },
                { "set-keymap",               2,        3,        0,            set_vconsole_keymap   },
                { "list-keymaps",             VERB_ANY, 1,        0,            list_vconsole_keymaps },
                { "set-x11-keymap",           2,        5,        0,            set_x11_keymap        },
                { "list-x11-keymap-models",   VERB_ANY, 1,        0,            list_x11_keymaps      },
                { "list-x11-keymap-layouts",  VERB_ANY, 1,        0,            list_x11_keymaps      },
                { "list-x11-keymap-variants", VERB_ANY, 2,        0,            list_x11_keymaps      },
                { "list-x11-keymap-options",  VERB_ANY, 1,        0,            list_x11_keymaps      },
                { "help",                     VERB_ANY, VERB_ANY, 0,            verb_help             }, /* Not documented, but supported since it is created. */
                {}
        };

        return dispatch_verb(argc, argv, verbs, bus);
}