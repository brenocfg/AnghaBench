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
typedef  int /*<<< orphan*/  CdioDataFree_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cdio_list_free (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ iso9660_stat_free ; 

void
iso9660_filelist_free(CdioISO9660FileList_t *p_filelist) {
  _cdio_list_free(p_filelist, true, (CdioDataFree_t) iso9660_stat_free);
}