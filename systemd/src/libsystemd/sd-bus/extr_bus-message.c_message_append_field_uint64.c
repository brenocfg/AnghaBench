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
typedef  char uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 scalar_t__ BUS_MESSAGE_IS_GVARIANT (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 char* message_extend_fields (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int message_append_field_uint64(sd_bus_message *m, uint64_t h, uint64_t x) {
        uint8_t *p;

        assert(m);

        /* dbus1 only allows 8bit header field ids */
        if (h > 0xFF)
                return -EINVAL;

        if (BUS_MESSAGE_IS_GVARIANT(m)) {
                /* (field id 64bit + ((value + NUL + signature string 't') */

                p = message_extend_fields(m, 8, 8 + 8 + 1 + 1, true);
                if (!p)
                        return -ENOMEM;

                *((uint64_t*) p) = h;
                *((uint64_t*) (p + 8)) = x;
                p[16] = 0;
                p[17] = 't';
        } else {
                /* (field id byte + (signature length + signature 't' + NUL) + 4 byte padding + value) */
                p = message_extend_fields(m, 8, 4 + 4 + 8, false);
                if (!p)
                        return -ENOMEM;

                p[0] = (uint8_t) h;
                p[1] = 1;
                p[2] = 't';
                p[3] = 0;
                p[4] = 0;
                p[5] = 0;
                p[6] = 0;
                p[7] = 0;

                ((uint64_t*) p)[1] = x;
        }

        return 0;
}