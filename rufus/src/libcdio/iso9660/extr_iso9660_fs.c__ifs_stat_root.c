#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  root_directory_record; } ;
struct TYPE_5__ {int /*<<< orphan*/  root_directory_record; } ;
struct TYPE_7__ {int /*<<< orphan*/  u_joliet_level; int /*<<< orphan*/  b_xa; TYPE_2__ pvd; TYPE_1__ svd; } ;
typedef  TYPE_3__ iso9660_t ;
typedef  int /*<<< orphan*/  iso9660_stat_t ;
typedef  int /*<<< orphan*/  iso9660_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _iso9660_dir_to_statbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static iso9660_stat_t *
_ifs_stat_root (iso9660_t *p_iso)
{
  iso9660_stat_t *p_stat;
  iso9660_dir_t *p_iso9660_dir;

#ifdef HAVE_JOLIET
  p_iso9660_dir = p_iso->u_joliet_level
    ? &(p_iso->svd.root_directory_record)
    : &(p_iso->pvd.root_directory_record) ;
#else
  p_iso9660_dir = &(p_iso->pvd.root_directory_record) ;
#endif

  p_stat = _iso9660_dir_to_statbuf (p_iso9660_dir, NULL,
				    p_iso->b_xa,
				    p_iso->u_joliet_level);
  return p_stat;
}