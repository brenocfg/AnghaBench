#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  udf_fileid_desc_t ;
struct TYPE_3__ {int /*<<< orphan*/  fid; } ;
typedef  TYPE_1__ udf_dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool udf_get_fileid_descriptor(const udf_dirent_t *p_udf_dirent, 
			       /*out*/ udf_fileid_desc_t *p_udf_fid)
{
  
  if (!p_udf_dirent) return false;
  if (!p_udf_dirent->fid) {
    /* FIXME do something about trying to get the descriptor. */
    return false;
  }
  memcpy(p_udf_fid, p_udf_dirent->fid, sizeof(udf_fileid_desc_t));
  return true;
}