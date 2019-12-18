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
typedef  int usec_t ;
struct ntp_ts_short {int /*<<< orphan*/  frac; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int USEC_PER_SEC ; 
 int be16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t ntp_ts_short_to_usec(const struct ntp_ts_short *ts) {
        return be16toh(ts->sec) * USEC_PER_SEC + (be16toh(ts->frac) * USEC_PER_SEC) / (usec_t) 0x10000ULL;
}