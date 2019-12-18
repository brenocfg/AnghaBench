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
struct ks_list {scalar_t__ i_max; scalar_t__ i_count; int /*<<< orphan*/ * p_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_keystore_release_entries (int /*<<< orphan*/ *,scalar_t__) ; 

void
ks_list_free(struct ks_list *p_list)
{
    vlc_keystore_release_entries(p_list->p_entries, p_list->i_count);
    p_list->p_entries = NULL;
    p_list->i_count = 0;
    p_list->i_max = 0;
}