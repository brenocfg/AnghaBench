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
typedef  int /*<<< orphan*/  vlc_keystore_entry ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_keystore_release_entry (int /*<<< orphan*/ *) ; 

void
vlc_keystore_release_entries(vlc_keystore_entry *p_entries, unsigned int i_count)
{
    for (unsigned int i = 0; i < i_count; ++i)
        vlc_keystore_release_entry(&p_entries[i]);
    free(p_entries);
}