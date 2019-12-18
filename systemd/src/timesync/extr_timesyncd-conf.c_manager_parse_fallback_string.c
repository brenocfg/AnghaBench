#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ have_fallbacks; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  SERVER_FALLBACK ; 
 int manager_parse_server_string (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

int manager_parse_fallback_string(Manager *m, const char *string) {
        if (m->have_fallbacks)
                return 0;

        return manager_parse_server_string(m, SERVER_FALLBACK, string);
}