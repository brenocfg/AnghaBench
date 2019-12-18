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
typedef  unsigned int uint_fast32_t ;
typedef  int uint8_t ;
typedef  int int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int_fast32_t hpack_decode_int(unsigned n,
                                     const uint8_t **restrict datap,
                                     size_t *restrict lengthp)
{
    const uint8_t *p = *datap;
    size_t length = *lengthp;

    assert(n >= 1 && n <= 8);
    assert(length >= 1);

    unsigned mask = (1 << n) - 1;
    uint_fast32_t i = *(p++) & mask;
    length--;

    if (i == mask)
    {
        unsigned shift = 0;
        uint8_t b;

        do
        {
            if (length-- < 1)
            {
                errno = EINVAL;
                return -1;
            }

            if (shift >= 28)
            {
                errno = ERANGE;
                return -1;
            }

            b = *(p++);
            i += (b & 0x7F) << shift;
            shift += 7;
        }
        while (b & 0x80);
    }

    *datap = p;
    *lengthp = length;
    return i;
}