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
struct ethtool_gstrings {unsigned int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENODATA ; 
 unsigned int ETH_GSTRING_LEN ; 
 scalar_t__ streq (char*,char const*) ; 

__attribute__((used)) static int find_feature_index(struct ethtool_gstrings *strings, const char *feature) {
        unsigned i;

        for (i = 0; i < strings->len; i++) {
                if (streq((char *) &strings->data[i * ETH_GSTRING_LEN], feature))
                        return i;
        }

        return -ENODATA;
}