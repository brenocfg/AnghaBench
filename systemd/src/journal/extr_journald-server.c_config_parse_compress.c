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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int enabled; scalar_t__ threshold_bytes; } ;
typedef  TYPE_1__ JournalCompressOptions ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,...) ; 
 int parse_boolean (char const*) ; 
 int parse_size (char const*,int,scalar_t__*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_compress(
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

        JournalCompressOptions* compress = data;
        int r;

        if (isempty(rvalue)) {
                compress->enabled = true;
                compress->threshold_bytes = (uint64_t) -1;
        } else if (streq(rvalue, "1")) {
                log_syntax(unit, LOG_WARNING, filename, line, 0,
                           "Compress= ambiguously specified as 1, enabling compression with default threshold");
                compress->enabled = true;
        } else if (streq(rvalue, "0")) {
                log_syntax(unit, LOG_WARNING, filename, line, 0,
                           "Compress= ambiguously specified as 0, disabling compression");
                compress->enabled = false;
        } else {
                r = parse_boolean(rvalue);
                if (r < 0) {
                        r = parse_size(rvalue, 1024, &compress->threshold_bytes);
                        if (r < 0)
                                log_syntax(unit, LOG_ERR, filename, line, r,
                                           "Failed to parse Compress= value, ignoring: %s", rvalue);
                        else
                                compress->enabled = true;
                } else
                        compress->enabled = r;
        }

        return 0;
}