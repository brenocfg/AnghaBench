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
typedef  int /*<<< orphan*/  iso9660_t ;
typedef  int /*<<< orphan*/  iso9660_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cdio_strfreev (char**) ; 
 char** _cdio_strsplit (char const*,char) ; 
 int /*<<< orphan*/ * _fs_iso_stat_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * _ifs_stat_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

iso9660_stat_t *
iso9660_ifs_stat (iso9660_t *p_iso, const char psz_path[])
{
  iso9660_stat_t *p_root;
  char **splitpath;
  iso9660_stat_t *stat;

  if (!p_iso)    return NULL;
  if (!psz_path) return NULL;

  p_root = _ifs_stat_root (p_iso);
  if (!p_root) return NULL;

  splitpath = _cdio_strsplit (psz_path, '/');
  stat = _fs_iso_stat_traverse (p_iso, p_root, splitpath);
  free(p_root);
  _cdio_strfreev (splitpath);

  return stat;
}