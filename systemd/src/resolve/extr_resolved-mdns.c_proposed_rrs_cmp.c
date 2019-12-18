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
typedef  int /*<<< orphan*/  DnsResourceRecord ;

/* Variables and functions */
 int CMP (unsigned int,unsigned int) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 int mdns_rr_compare (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int proposed_rrs_cmp(DnsResourceRecord **x, unsigned x_size, DnsResourceRecord **y, unsigned y_size) {
        unsigned m;
        int r;

        m = MIN(x_size, y_size);
        for (unsigned i = 0; i < m; i++) {
                r = mdns_rr_compare(&x[i], &y[i]);
                if (r != 0)
                        return r;
        }

        return CMP(x_size, y_size);
}