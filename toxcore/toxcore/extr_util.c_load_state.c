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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int (* load_state_callback_func ) (void*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ;
typedef  int /*<<< orphan*/  length_sub ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lendian_to_host16 (scalar_t__) ; 
 int /*<<< orphan*/  lendian_to_host32 (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stderr ; 

int load_state(load_state_callback_func load_state_callback, void *outer,
               const uint8_t *data, uint32_t length, uint16_t cookie_inner)
{
    if (!load_state_callback || !data) {
#ifdef DEBUG
        fprintf(stderr, "load_state() called with invalid args.\n");
#endif
        return -1;
    }


    uint16_t type;
    uint32_t length_sub, cookie_type;
    uint32_t size_head = sizeof(uint32_t) * 2;

    while (length >= size_head) {
        lendian_to_host32(&length_sub, data);
        lendian_to_host32(&cookie_type, data + sizeof(length_sub));
        data += size_head;
        length -= size_head;

        if (length < length_sub) {
            /* file truncated */
#ifdef DEBUG
            fprintf(stderr, "state file too short: %u < %u\n", length, length_sub);
#endif
            return -1;
        }

        if (lendian_to_host16((cookie_type >> 16)) != cookie_inner) {
            /* something is not matching up in a bad way, give up */
#ifdef DEBUG
            fprintf(stderr, "state file garbeled: %04hx != %04hx\n", (cookie_type >> 16), cookie_inner);
#endif
            return -1;
        }

        type = lendian_to_host16(cookie_type & 0xFFFF);

        int ret = load_state_callback(outer, data, length_sub, type);

        if (ret == -1) {
            return -1;
        }

        /* -2 means end of save. */
        if (ret == -2)
            return 0;

        data += length_sub;
        length -= length_sub;
    }

    return length == 0 ? 0 : -1;
}