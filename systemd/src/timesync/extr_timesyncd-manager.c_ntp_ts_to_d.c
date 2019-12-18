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
struct ntp_ts {int /*<<< orphan*/  frac; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 double UINT_MAX ; 
 double be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double ntp_ts_to_d(const struct ntp_ts *ts) {
        return be32toh(ts->sec) + ((double)be32toh(ts->frac) / UINT_MAX);
}