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
typedef  int uint32_t ;
typedef  size_t sd_bus_message ;

/* Variables and functions */
 scalar_t__ BUS_MESSAGE_IS_GVARIANT (size_t*) ; 
 int EBADMSG ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  assert (size_t*) ; 
 int message_peek_field_uint32 (size_t*,size_t*,int,int*) ; 
 int message_peek_fields (size_t*,size_t*,int,int,void**) ; 
 int /*<<< orphan*/  validate_nul (void*,int) ; 
 int /*<<< orphan*/  validate_string (void*,int) ; 

__attribute__((used)) static int message_peek_field_string(
                sd_bus_message *m,
                bool (*validate)(const char *p),
                size_t *ri,
                size_t item_size,
                const char **ret) {

        uint32_t l;
        int r;
        void *q;

        assert(m);
        assert(ri);

        if (BUS_MESSAGE_IS_GVARIANT(m)) {

                if (item_size <= 0)
                        return -EBADMSG;

                r = message_peek_fields(m, ri, 1, item_size, &q);
                if (r < 0)
                        return r;

                l = item_size - 1;
        } else {
                r = message_peek_field_uint32(m, ri, 4, &l);
                if (r < 0)
                        return r;

                if (l == UINT32_MAX)
                        /* avoid overflow right below */
                        return -EBADMSG;

                r = message_peek_fields(m, ri, 1, l+1, &q);
                if (r < 0)
                        return r;
        }

        if (validate) {
                if (!validate_nul(q, l))
                        return -EBADMSG;

                if (!validate(q))
                        return -EBADMSG;
        } else {
                if (!validate_string(q, l))
                        return -EBADMSG;
        }

        if (ret)
                *ret = q;

        return 0;
}