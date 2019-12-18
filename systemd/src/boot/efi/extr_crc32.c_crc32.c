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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ UINTN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_add_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT32 crc32(UINT32 seed, const VOID *buf, UINTN len) {
        const UINT8 *p = buf;
        UINT32 crc = seed;

        while (len > 0) {
                crc = crc32_add_char(crc, *p++);
                len--;
        }

        return crc;
}