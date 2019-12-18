#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {int /*<<< orphan*/  u_joliet_level; int /*<<< orphan*/  b_xa; } ;
typedef  TYPE_1__ iso9660_t ;
struct TYPE_16__ {scalar_t__ type; size_t* secsize; int /*<<< orphan*/ * lsn; } ;
typedef  TYPE_2__ iso9660_stat_t ;
struct TYPE_17__ {int file_flags; } ;
typedef  TYPE_3__ iso9660_dir_t ;
typedef  int /*<<< orphan*/  CdioList_t ;
typedef  int /*<<< orphan*/  CdioISO9660FileList_t ;
typedef  int /*<<< orphan*/ * CdioDataFree_t ;

/* Variables and functions */
 size_t ISO_BLOCKSIZE ; 
 int ISO_MULTIEXTENT ; 
 scalar_t__ _STAT_DIR ; 
 int /*<<< orphan*/  _cdio_list_append (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  _cdio_list_free (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _cdio_list_new () ; 
 TYPE_2__* _iso9660_dir_to_statbuf (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int,size_t const) ; 
 int /*<<< orphan*/  cdio_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ iso9660_check_dir_block_end (TYPE_3__*,unsigned int*) ; 
 scalar_t__ iso9660_get_dir_len (TYPE_3__*) ; 
 TYPE_2__* iso9660_ifs_stat (TYPE_1__*,char const*) ; 
 long iso9660_iso_seek_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iso9660_stat_free (TYPE_2__*) ; 

CdioISO9660FileList_t *
iso9660_ifs_readdir (iso9660_t *p_iso, const char psz_path[])
{
  iso9660_dir_t *p_iso9660_dir;
  iso9660_stat_t *p_iso9660_stat = NULL;
  iso9660_stat_t *p_stat;

  if (!p_iso)    return NULL;
  if (!psz_path) return NULL;

  p_stat = iso9660_ifs_stat (p_iso, psz_path);
  if (!p_stat)   return NULL;

  if (p_stat->type != _STAT_DIR) {
    iso9660_stat_free(p_stat);
    return NULL;
  }

  {
    long int ret;
    unsigned offset = 0;
    uint8_t *_dirbuf = NULL;
    CdioList_t *retval = _cdio_list_new ();
    const size_t dirbuf_len = p_stat->secsize[0] * ISO_BLOCKSIZE;


    if (!dirbuf_len)
      {
        cdio_warn("Invalid directory buffer sector size %u", p_stat->secsize[0]);
	iso9660_stat_free(p_stat);
	_cdio_list_free (retval, true, NULL);
        return NULL;
      }

    _dirbuf = calloc(1, dirbuf_len);
    if (!_dirbuf)
      {
        cdio_warn("Couldn't calloc(1, %lu)", (unsigned long)dirbuf_len);
	iso9660_stat_free(p_stat);
	_cdio_list_free (retval, true, NULL);
        return NULL;
      }

    ret = iso9660_iso_seek_read (p_iso, _dirbuf, p_stat->lsn[0], p_stat->secsize[0]);
    if (ret != dirbuf_len) 	  {
      _cdio_list_free (retval, true, NULL);
      iso9660_stat_free(p_stat);
      free (_dirbuf);
      return NULL;
    }

    while (offset < (dirbuf_len))
      {
	p_iso9660_dir = (void *) &_dirbuf[offset];

	if (iso9660_check_dir_block_end(p_iso9660_dir, &offset))
	  continue;

	p_iso9660_stat = _iso9660_dir_to_statbuf(p_iso9660_dir,
						 p_iso9660_stat,
						 p_iso->b_xa,
						 p_iso->u_joliet_level);
	if ((p_iso9660_stat) &&
	    ((p_iso9660_dir->file_flags & ISO_MULTIEXTENT) == 0))
	  {
	    _cdio_list_append(retval, p_iso9660_stat);
	    p_iso9660_stat = NULL;
	  }

	offset += iso9660_get_dir_len(p_iso9660_dir);
      }

    free (_dirbuf);
    iso9660_stat_free(p_stat);

    if (offset != dirbuf_len) {
      _cdio_list_free (retval, true, (CdioDataFree_t) iso9660_stat_free);
      return NULL;
    }

    return retval;
  }
}