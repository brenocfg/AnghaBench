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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ id; } ;
typedef  TYPE_1__ Geneve ;

/* Variables and functions */
 scalar_t__ GENEVE_VID_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int safe_atou32 (char const*,scalar_t__*) ; 

int config_parse_geneve_vni(const char *unit,
                           const char *filename,
                           unsigned line,
                           const char *section,
                           unsigned section_line,
                           const char *lvalue,
                           int ltype,
                           const char *rvalue,
                           void *data,
                           void *userdata) {
        Geneve *v = userdata;
        uint32_t f;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = safe_atou32(rvalue, &f);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse Geneve VNI '%s'.", rvalue);
                return 0;
        }

        if (f > GENEVE_VID_MAX){
                log_syntax(unit, LOG_ERR, filename, line, r, "Geneve VNI out is of range '%s'.", rvalue);
                return 0;
        }

        v->id = f;

        return 0;
}