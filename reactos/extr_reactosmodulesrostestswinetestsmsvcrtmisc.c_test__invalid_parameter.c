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
 int /*<<< orphan*/  p__invalid_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__invalid_parameter(void)
{
    if(!p__invalid_parameter) {
        win_skip("_invalid_parameter not available\n");
        return;
    }

    p__invalid_parameter(NULL, NULL, NULL, 0, 0);
}