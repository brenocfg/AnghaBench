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
struct global_info {int /*<<< orphan*/  ntas; int /*<<< orphan*/  domains; int /*<<< orphan*/  fallback_dns; int /*<<< orphan*/  dns; int /*<<< orphan*/  current_dns; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void global_info_clear(struct global_info *p) {
        free(p->current_dns);
        strv_free(p->dns);
        strv_free(p->fallback_dns);
        strv_free(p->domains);
        strv_free(p->ntas);
}