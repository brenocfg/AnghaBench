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
typedef  int uint32_t ;
struct TYPE_2__ {int rx_count; int rx_count_set; int tx_count; int tx_count_set; int other_count; int other_count_set; int combined_count; int combined_count_set; } ;
typedef  TYPE_1__ netdev_channels ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,...) ; 
 int safe_atou32 (char const*,int*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_channel(const char *unit,
                         const char *filename,
                         unsigned line,
                         const char *section,
                         unsigned section_line,
                         const char *lvalue,
                         int ltype,
                         const char *rvalue,
                         void *data,
                         void *userdata) {
        netdev_channels *channels = data;
        uint32_t k;
        int r;

        assert(filename);
        assert(section);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = safe_atou32(rvalue, &k);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse channel value, ignoring: %s", rvalue);
                return 0;
        }

        if (k < 1) {
                log_syntax(unit, LOG_ERR, filename, line, -EINVAL, "Invalid %s value, ignoring: %s", lvalue, rvalue);
                return 0;
        }

        if (streq(lvalue, "RxChannels")) {
                channels->rx_count = k;
                channels->rx_count_set = true;
        } else if (streq(lvalue, "TxChannels")) {
                channels->tx_count = k;
                channels->tx_count_set = true;
        } else if (streq(lvalue, "OtherChannels")) {
                channels->other_count = k;
                channels->other_count_set = true;
        } else if (streq(lvalue, "CombinedChannels")) {
                channels->combined_count = k;
                channels->combined_count_set = true;
        }

        return 0;
}