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
typedef  int /*<<< orphan*/  iso9660_stat_t ;
typedef  int /*<<< orphan*/  CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cdio_strfreev (char**) ; 
 char** _cdio_strsplit (char const*,char) ; 
 int /*<<< orphan*/ * _fs_stat_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _fs_stat_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

iso9660_stat_t *
iso9660_fs_stat (CdIo_t *p_cdio, const char psz_path[])
{
  iso9660_stat_t *p_root;
  char **p_psz_splitpath;
  iso9660_stat_t *p_stat;

  if (!p_cdio)   return NULL;
  if (!psz_path) return NULL;

  p_root = _fs_stat_root (p_cdio);

  if (!p_root)   return NULL;

  p_psz_splitpath = _cdio_strsplit (psz_path, '/');
  p_stat = _fs_stat_traverse (p_cdio, p_root, p_psz_splitpath);
  free(p_root);
  _cdio_strfreev (p_psz_splitpath);

  return p_stat;
}