#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num; int /*<<< orphan*/  display; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ vdp_instance_t ;

/* Variables and functions */
 int XDefaultScreen (int /*<<< orphan*/ ) ; 
 int strnullcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vicmp(const char *name, int num, const vdp_instance_t *vi)
{
    int val = strnullcmp(name, vi->name);
    if (val)
        return val;

    if (num < 0)
        num = XDefaultScreen(vi->display);
    return num - vi->num;
}