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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int use_br_vlan; int /*<<< orphan*/  br_untagged_bitmap; int /*<<< orphan*/  br_vid_bitmap; } ;
typedef  TYPE_1__ Network ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_vid_range (char const*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

int config_parse_brvlan_untagged(const char *unit, const char *filename,
                                 unsigned line, const char *section,
                                 unsigned section_line, const char *lvalue,
                                 int ltype, const char *rvalue, void *data,
                                 void *userdata) {
        Network *network = userdata;
        int r;
        uint16_t vid, vid_end;

        assert(filename);
        assert(section);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = parse_vid_range(rvalue, &vid, &vid_end);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Could not parse VLAN: %s", rvalue);
                return 0;
        }

        for (; vid <= vid_end; vid++) {
                set_bit(vid, network->br_vid_bitmap);
                set_bit(vid, network->br_untagged_bitmap);
        }

        network->use_br_vlan = true;
        return 0;
}