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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t *
ascii_to_utf16le(uint16_t *dst, const char *src)
{
    uint8_t *p = (uint8_t *)dst;
    char c;

    do {
	c = *src++;
	*p++ = c;
	*p++ = 0;
    } while (c);

    return (uint16_t *)p;
}