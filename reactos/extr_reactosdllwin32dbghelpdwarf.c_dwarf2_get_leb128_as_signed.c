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

/* Variables and functions */
 unsigned char dwarf2_get_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long dwarf2_get_leb128_as_signed(const unsigned char* ptr, const unsigned char** end)
{
    long ret = 0;
    unsigned char byte;
    unsigned shift = 0;
    const unsigned size = sizeof(int) * 8;

    do
    {
        byte = dwarf2_get_byte(ptr++);
        ret |= (byte & 0x7f) << shift;
        shift += 7;
    } while (byte & 0x80);
    if (end) *end = ptr;

    /* as spec: sign bit of byte is 2nd high order bit (80x40)
     *  -> 0x80 is used as flag.
     */
    if ((shift < size) && (byte & 0x40))
    {
        ret |= - (1 << shift);
    }
    return ret;
}