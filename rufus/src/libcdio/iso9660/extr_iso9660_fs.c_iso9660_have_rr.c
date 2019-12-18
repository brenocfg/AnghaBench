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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  iso9660_t ;
typedef  char iso9660_stat_t ;
typedef  int bool_3way_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 char* _ifs_stat_root (int /*<<< orphan*/ *) ; 
 int dunno ; 
 int /*<<< orphan*/  free (char*) ; 
 int iso_have_rr_traverse (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 
 int nope ; 
 char* strdup (char*) ; 

extern bool_3way_t
iso9660_have_rr(iso9660_t *p_iso, uint64_t u_file_limit)
{
  iso9660_stat_t *p_root;
  char *p_psz_splitpath[2] = {strdup("/"), strdup("")};
  bool_3way_t is_rr = nope;

  if (!p_iso) return false;

  p_root = _ifs_stat_root (p_iso);
  if (!p_root) return dunno;

  if (u_file_limit == 0) u_file_limit = UINT64_MAX;

  is_rr = iso_have_rr_traverse (p_iso, p_root, p_psz_splitpath, &u_file_limit);
  free(p_root);
  free(p_psz_splitpath[0]);
  free(p_psz_splitpath[1]);

  return is_rr;
}