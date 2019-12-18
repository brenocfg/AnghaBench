#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  line; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ NetworkConfigSection ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int network_config_compare_func(const NetworkConfigSection *x, const NetworkConfigSection *y) {
        int r;

        r = strcmp(x->filename, y->filename);
        if (r != 0)
                return r;

        return CMP(x->line, y->line);
}