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
typedef  scalar_t__ VOID ;
typedef  scalar_t__ UINTN ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_add_char (int /*<<< orphan*/ ,scalar_t__) ; 

UINT32 crc32_exclude_offset(
                UINT32 seed,
                const VOID *buf,
                UINTN len,
                UINTN exclude_off,
                UINTN exclude_len) {

        const UINT8 *p = buf;
        UINT32 crc = seed;
        UINTN i;

        for (i = 0; i < len; i++) {
                UINT8 x = *p++;

                if (i >= exclude_off && i < exclude_off + exclude_len)
                        x = 0;

                crc = crc32_add_char(crc, x);
        }

        return crc;
}