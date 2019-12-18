#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ psz_symlink; } ;
struct TYPE_6__ {TYPE_1__ rr; } ;
typedef  TYPE_2__ iso9660_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDIO_FREE_IF_NOT_NULL (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void
iso9660_stat_free(iso9660_stat_t *p_stat)
{
  if (p_stat != NULL) {
    if (p_stat->rr.psz_symlink) {
      CDIO_FREE_IF_NOT_NULL(p_stat->rr.psz_symlink);
    }
    free(p_stat);
  }
}