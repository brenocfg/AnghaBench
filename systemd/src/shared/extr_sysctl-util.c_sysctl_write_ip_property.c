#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 char const* IN_SET (int,int,int /*<<< orphan*/ ) ; 
 int WRITE_STRING_FILE_DISABLE_BUFFER ; 
 int WRITE_STRING_FILE_VERIFY_ON_FAILURE ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strempty (char const*) ; 
 char* strjoina (char*,char*,char*,int /*<<< orphan*/ ,char*,char const*) ; 
 int write_string_file (char const*,char const*,int) ; 

int sysctl_write_ip_property(int af, const char *ifname, const char *property, const char *value) {
        const char *p;

        assert(IN_SET(af, AF_INET, AF_INET6));
        assert(property);
        assert(value);

        p = strjoina("/proc/sys/net/ipv", af == AF_INET ? "4" : "6",
                     ifname ? "/conf/" : "", strempty(ifname),
                     property[0] == '/' ? "" : "/", property);

        log_debug("Setting '%s' to '%s'", p, value);

        return write_string_file(p, value, WRITE_STRING_FILE_VERIFY_ON_FAILURE | WRITE_STRING_FILE_DISABLE_BUFFER);
}