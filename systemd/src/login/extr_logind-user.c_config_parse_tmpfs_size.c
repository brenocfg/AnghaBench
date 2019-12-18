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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_permille (char const*) ; 
 int parse_size (char const*,int,scalar_t__*) ; 
 scalar_t__ physical_memory_scale (int,unsigned int) ; 

int config_parse_tmpfs_size(
                const char* unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        uint64_t *sz = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        /* First, try to parse as percentage */
        r = parse_permille(rvalue);
        if (r > 0 && r < 1000)
                *sz = physical_memory_scale(r, 1000U);
        else {
                uint64_t k;

                /* If the passed argument was not a percentage, or out of range, parse as byte size */

                r = parse_size(rvalue, 1024, &k);
                if (r >= 0 && (k <= 0 || (uint64_t) (size_t) k != k))
                        r = -ERANGE;
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse size value '%s', ignoring: %m", rvalue);
                        return 0;
                }

                *sz = PAGE_ALIGN((size_t) k);
        }

        return 0;
}