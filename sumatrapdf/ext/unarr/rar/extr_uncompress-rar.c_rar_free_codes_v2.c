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
struct ar_archive_rar_uncomp_v2 {int /*<<< orphan*/ * audiocode; int /*<<< orphan*/  lengthcode; int /*<<< orphan*/  offsetcode; int /*<<< orphan*/  maincode; } ;

/* Variables and functions */
 int /*<<< orphan*/  rar_free_code (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rar_free_codes_v2(struct ar_archive_rar_uncomp_v2 *uncomp_v2)
{
    int i;
    rar_free_code(&uncomp_v2->maincode);
    rar_free_code(&uncomp_v2->offsetcode);
    rar_free_code(&uncomp_v2->lengthcode);
    for (i = 0; i < 4; i++)
        rar_free_code(&uncomp_v2->audiocode[i]);
}