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
struct TYPE_2__ {int /*<<< orphan*/  bind_to_device; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 scalar_t__ free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ifname_valid (char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_socket_bindtodevice(
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

        Socket *s = data;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue) || streq(rvalue, "*")) {
                s->bind_to_device = mfree(s->bind_to_device);
                return 0;
        }

        if (!ifname_valid(rvalue)) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Invalid interface name, ignoring: %s", rvalue);
                return 0;
        }

        if (free_and_strdup(&s->bind_to_device, rvalue) < 0)
                return log_oom();

        return 0;
}