#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
union in_addr_union {TYPE_1__ in; } ;
typedef  void* uint32_t ;
struct TYPE_4__ {void* okey; void* ikey; void* key; } ;
typedef  TYPE_2__ Tunnel ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* be32toh (int /*<<< orphan*/ ) ; 
 int in_addr_from_string (int /*<<< orphan*/ ,char const*,union in_addr_union*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 
 int safe_atou32 (char const*,void**) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_tunnel_key(const char *unit,
                            const char *filename,
                            unsigned line,
                            const char *section,
                            unsigned section_line,
                            const char *lvalue,
                            int ltype,
                            const char *rvalue,
                            void *data,
                            void *userdata) {
        union in_addr_union buffer;
        Tunnel *t = userdata;
        uint32_t k;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = in_addr_from_string(AF_INET, rvalue, &buffer);
        if (r < 0) {
                r = safe_atou32(rvalue, &k);
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, 0, "Failed to parse tunnel key ignoring assignment: %s", rvalue);
                        return 0;
                }
        } else
                k = be32toh(buffer.in.s_addr);

        if (streq(lvalue, "Key"))
                t->key = k;
        else if (streq(lvalue, "InputKey"))
                t->ikey = k;
        else
                t->okey = k;

        return 0;
}