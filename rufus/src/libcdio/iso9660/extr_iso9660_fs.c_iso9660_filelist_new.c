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
typedef  int /*<<< orphan*/  CdioISO9660FileList_t ;

/* Variables and functions */
 scalar_t__ _cdio_list_new () ; 

CdioISO9660FileList_t *
iso9660_filelist_new(void) {
  return (CdioISO9660FileList_t *) _cdio_list_new ();
}