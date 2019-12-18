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
struct machine_info {int /*<<< orphan*/  name; int /*<<< orphan*/  is_host; } ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_machine_info(const struct machine_info *a, const struct machine_info *b) {
        int r;

        r = CMP(b->is_host, a->is_host);
        if (r != 0)
                return r;

        return strcasecmp(a->name, b->name);
}