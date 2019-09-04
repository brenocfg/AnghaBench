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
typedef  int /*<<< orphan*/  DOS_FS ;

/* Variables and functions */
 int strlen (char*) ; 
 int /*<<< orphan*/  write_boot_label (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_volume_label (int /*<<< orphan*/ *,char*) ; 

void write_label(DOS_FS * fs, char *label)
{
    int l = strlen(label);

    while (l < 11)
	label[l++] = ' ';

    write_boot_label(fs, label);
    write_volume_label(fs, label);
}