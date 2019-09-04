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
struct dec3n {int x; int y; int z; int w; } ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static struct dec3n dword_to_dec3n(DWORD d)
{
    struct dec3n v;

    v.x = d & 0x3ff;
    v.y = (d & 0xffc00) >> 10;
    v.z = (d & 0x3ff00000) >> 20;
    v.w = (d & 0xc0000000) >> 30;

    return v;
}