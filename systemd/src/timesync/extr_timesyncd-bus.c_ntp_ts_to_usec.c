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
struct ntp_ts {int /*<<< orphan*/  frac; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int OFFSET_1900_1970 ; 
 int USEC_PER_SEC ; 
 int be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t ntp_ts_to_usec(const struct ntp_ts *ts) {
        return (be32toh(ts->sec) - OFFSET_1900_1970) * USEC_PER_SEC + (be32toh(ts->frac) * USEC_PER_SEC) / (usec_t) 0x100000000ULL;
}