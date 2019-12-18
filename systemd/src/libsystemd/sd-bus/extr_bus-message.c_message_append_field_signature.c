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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 scalar_t__ BUS_MESSAGE_IS_GVARIANT (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t SD_BUS_MAXIMUM_SIGNATURE_LENGTH ; 
 int SD_BUS_TYPE_SIGNATURE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,size_t) ; 
 int message_append_field_string (int /*<<< orphan*/ *,int,char,char const*,char const**) ; 
 int* message_extend_fields (int /*<<< orphan*/ *,int,int,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int message_append_field_signature(
                sd_bus_message *m,
                uint64_t h,
                const char *s,
                const char **ret) {

        size_t l;
        uint8_t *p;

        assert(m);

        /* dbus1 only allows 8bit header field ids */
        if (h > 0xFF)
                return -EINVAL;

        /* dbus1 doesn't allow signatures over 8bit, let's enforce
         * this globally, to not risk convertability */
        l = strlen(s);
        if (l > SD_BUS_MAXIMUM_SIGNATURE_LENGTH)
                return -EINVAL;

        /* Signature "(yv)" where the variant contains "g" */

        if (BUS_MESSAGE_IS_GVARIANT(m))
                /* For gvariant the serialization is the same as for normal strings */
                return message_append_field_string(m, h, 'g', s, ret);
        else {
                /* (field id byte + (signature length + signature 'g' + NUL) + (string length + string + NUL)) */
                p = message_extend_fields(m, 8, 4 + 1 + l + 1, false);
                if (!p)
                        return -ENOMEM;

                p[0] = (uint8_t) h;
                p[1] = 1;
                p[2] = SD_BUS_TYPE_SIGNATURE;
                p[3] = 0;
                p[4] = l;
                memcpy(p + 5, s, l + 1);

                if (ret)
                        *ret = (const char*) p + 5;
        }

        return 0;
}