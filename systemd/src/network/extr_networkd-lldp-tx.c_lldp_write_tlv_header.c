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
typedef  int uint8_t ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  assert (int**) ; 

__attribute__((used)) static int lldp_write_tlv_header(uint8_t **p, uint8_t id, size_t sz) {
        assert(p);

        if (id > 127)
                return -EBADMSG;
        if (sz > 511)
                return -ENOBUFS;

        (*p)[0] = (id << 1) | !!(sz & 256);
        (*p)[1] = sz & 255;

        *p = *p + 2;
        return 0;
}