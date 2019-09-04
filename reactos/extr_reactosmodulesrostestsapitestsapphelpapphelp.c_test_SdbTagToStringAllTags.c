#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ min_ver; scalar_t__ max_ver; int /*<<< orphan*/  line; int /*<<< orphan*/  upper_limit; int /*<<< orphan*/  tags; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WINVER_ANY ; 
 TYPE_1__* data ; 
 scalar_t__ g_WinVersion ; 
 int /*<<< orphan*/  test_tag (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_SdbTagToStringAllTags(void)
{
    int n;
    for (n = 0; data[n].base; ++n)
    {
        if ((data[n].min_ver == WINVER_ANY || g_WinVersion >= data[n].min_ver) &&
            (data[n].max_ver == WINVER_ANY || g_WinVersion <= data[n].max_ver))
        {
            test_tag(data[n].base, data[n].tags, data[n].upper_limit, data[n].line);
        }
    }
}