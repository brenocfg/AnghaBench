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
struct ar_archive_rar_uncomp_v3 {int /*<<< orphan*/  lengthcode; int /*<<< orphan*/  lowoffsetcode; int /*<<< orphan*/  offsetcode; int /*<<< orphan*/  maincode; } ;
struct TYPE_2__ {int /*<<< orphan*/  v2; struct ar_archive_rar_uncomp_v3 v3; } ;
struct ar_archive_rar_uncomp {int version; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  rar_free_code (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rar_free_codes_v2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rar_free_codes(struct ar_archive_rar_uncomp *uncomp)
{
    struct ar_archive_rar_uncomp_v3 *uncomp_v3 = &uncomp->state.v3;

    if (uncomp->version == 2) {
        rar_free_codes_v2(&uncomp->state.v2);
        return;
    }

    rar_free_code(&uncomp_v3->maincode);
    rar_free_code(&uncomp_v3->offsetcode);
    rar_free_code(&uncomp_v3->lowoffsetcode);
    rar_free_code(&uncomp_v3->lengthcode);
}