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
struct TYPE_4__ {char** data; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 char* FALLBACK_HOSTNAME ; 
 size_t PROP_HOSTNAME ; 
 size_t PROP_STATIC_HOSTNAME ; 
 int /*<<< orphan*/  STRV_MAKE (char*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 scalar_t__ hostname_is_useful (char const*) ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 int /*<<< orphan*/  nscd_flush_cache (int /*<<< orphan*/ ) ; 
 scalar_t__ sethostname_idempotent (char const*) ; 

__attribute__((used)) static int context_update_kernel_hostname(Context *c) {
        const char *static_hn;
        const char *hn;

        assert(c);

        static_hn = c->data[PROP_STATIC_HOSTNAME];

        /* /etc/hostname with something other than "localhost"
         * has the highest preference ... */
        if (hostname_is_useful(static_hn))
                hn = static_hn;

        /* ... the transient host name, (ie: DHCP) comes next ... */
        else if (!isempty(c->data[PROP_HOSTNAME]))
                hn = c->data[PROP_HOSTNAME];

        /* ... fallback to static "localhost.*" ignored above ... */
        else if (!isempty(static_hn))
                hn = static_hn;

        /* ... and the ultimate fallback */
        else
                hn = FALLBACK_HOSTNAME;

        if (sethostname_idempotent(hn) < 0)
                return -errno;

        (void) nscd_flush_cache(STRV_MAKE("hosts"));

        return 0;
}