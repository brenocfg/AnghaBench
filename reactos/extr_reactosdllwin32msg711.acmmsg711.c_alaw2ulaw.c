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
 int* _a2u ; 

__attribute__((used)) static inline unsigned char
alaw2ulaw(unsigned char aval)
{
    aval &= 0xff;
    return (unsigned char) ((aval & 0x80) ? (0xFF ^ _a2u[aval ^ 0xD5]) :
                            (0x7F ^ _a2u[aval ^ 0x55]));
}