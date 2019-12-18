#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* sector; struct TYPE_4__* psz_name; int /*<<< orphan*/ * fid; } ;
typedef  TYPE_1__ udf_dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_and_null (TYPE_1__*) ; 

bool
udf_dirent_free(udf_dirent_t *p_udf_dirent)
{
  if (p_udf_dirent) {
    p_udf_dirent->fid = NULL;
    free_and_null(p_udf_dirent->psz_name);
    free_and_null(p_udf_dirent->sector);
    free_and_null(p_udf_dirent);
  }
  return true;
}