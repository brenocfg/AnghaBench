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
 int /*<<< orphan*/  W16 (unsigned char*,short) ; 
 int /*<<< orphan*/  W8 (unsigned char*,short) ; 

__attribute__((used)) static inline void W8_16(unsigned char* dst, short s, int bytes)
{
    if(bytes == 1)
        W8(dst, s);
    else
        W16(dst, s);
}