#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ i_part_start; } ;
typedef  TYPE_5__ udf_t ;
struct TYPE_17__ {scalar_t__ file_type; } ;
struct TYPE_20__ {TYPE_3__ icb_tag; int /*<<< orphan*/  tag; } ;
typedef  TYPE_6__ udf_file_entry_t ;
struct TYPE_21__ {int /*<<< orphan*/  psz_name; TYPE_4__* fid; TYPE_5__* p_udf; int /*<<< orphan*/  b_parent; scalar_t__ b_dir; } ;
typedef  TYPE_7__ udf_dirent_t ;
typedef  scalar_t__ driver_return_code_t ;
struct TYPE_15__ {scalar_t__ lba; } ;
struct TYPE_16__ {TYPE_1__ loc; } ;
struct TYPE_18__ {TYPE_2__ icb; } ;

/* Variables and functions */
 scalar_t__ DRIVER_OP_SUCCESS ; 
 scalar_t__ ICBTAG_FILE_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  TAGID_FILE_ENTRY ; 
 int /*<<< orphan*/  udf_checktag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__* udf_new_dirent (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ udf_read_sectors (TYPE_5__*,TYPE_6__*,scalar_t__,int) ; 

udf_dirent_t *
udf_opendir(const udf_dirent_t *p_udf_dirent)
{
  if (p_udf_dirent->b_dir && !p_udf_dirent->b_parent && p_udf_dirent->fid) {
    udf_t *p_udf = p_udf_dirent->p_udf;
    udf_file_entry_t udf_fe;

    driver_return_code_t i_ret =
      udf_read_sectors(p_udf, &udf_fe, p_udf->i_part_start
		       + p_udf_dirent->fid->icb.loc.lba, 1);

    if (DRIVER_OP_SUCCESS == i_ret
	&& !udf_checktag(&udf_fe.tag, TAGID_FILE_ENTRY)) {

      if (ICBTAG_FILE_TYPE_DIRECTORY == udf_fe.icb_tag.file_type) {
	udf_dirent_t *p_udf_dirent_new =
	  udf_new_dirent(&udf_fe, p_udf, p_udf_dirent->psz_name, true, true);
	return p_udf_dirent_new;
      }
    }
  }
  return NULL;
}