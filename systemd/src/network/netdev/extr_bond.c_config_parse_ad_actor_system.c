#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ether_addr {int* ether_addr_octet; } ;
struct TYPE_2__ {struct ether_addr ad_actor_system; } ;
typedef  TYPE_1__ Bond ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int ether_addr_from_string (char const*,struct ether_addr*) ; 
 scalar_t__ ether_addr_is_null (struct ether_addr*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 

int config_parse_ad_actor_system(
                const char *unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {
        Bond *b = userdata;
        struct ether_addr n;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = ether_addr_from_string(rvalue, &n);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Not a valid MAC address %s. Ignoring assignment: %m",
                           rvalue);
                return 0;
        }
        if (ether_addr_is_null(&n) || (n.ether_addr_octet[0] & 0x01)) {
                log_syntax(unit, LOG_ERR, filename, line, 0,
                           "Not a valid MAC address %s, can not be null or multicast. Ignoring assignment.",
                           rvalue);
                return 0;
        }

        b->ad_actor_system = n;

        return 0;
}