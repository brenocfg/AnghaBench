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
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static DWORD KeyDownData (int repeat, int scancode, int extended, int wasdown)
{
    return ((repeat & 0x0000FFFF) | ((scancode & 0x00FF) << 16) |
            (extended ? 0x01000000 : 0) | (wasdown ? 0x40000000 : 0));
}