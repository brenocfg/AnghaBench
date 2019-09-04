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
 char* CNV_PARTS_SO_FAR () ; 
 int /*<<< orphan*/  clear_lfn_slots (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 char get_key (char*,char*) ; 
 scalar_t__ interactive ; 
 scalar_t__ lfn_parts ; 
 int /*<<< orphan*/  lfn_reset () ; 
 int lfn_slot ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void lfn_check_orphaned(void)
{
    char *long_name;

    if (lfn_slot == -1)
	return;

    long_name = CNV_PARTS_SO_FAR();
    printf("Orphaned long file name part \"%s\"\n", long_name);
    free(long_name);
    if (interactive)
	printf("1: Delete.\n2: Leave it.\n");
#ifdef __REACTOS__
    else if (rw)
#else
    else
#endif
	printf("  Auto-deleting.\n");
#ifdef __REACTOS__
    if ((!interactive && rw) || (interactive && get_key("12", "?") == '1')) {
#else
    if (!interactive || get_key("12", "?") == '1') {
#endif
	clear_lfn_slots(0, lfn_parts - 1);
    }
    lfn_reset();
}