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
 int* _u2a ; 

__attribute__((used)) static inline unsigned char
ulaw2alaw(unsigned char uval)
{
    uval &= 0xff;
    return (unsigned char) ((uval & 0x80) ? (0xD5 ^ (_u2a[0xFF ^ uval] - 1)) :
                            (unsigned char) (0x55 ^ (_u2a[0x7F ^ uval] - 1)));
}