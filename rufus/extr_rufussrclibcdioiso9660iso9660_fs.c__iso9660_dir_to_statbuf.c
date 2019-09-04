#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_17__ {char* signature; } ;
typedef  TYPE_3__ iso9660_xa_t ;
struct TYPE_16__ {TYPE_4__* psz_symlink; int /*<<< orphan*/  b3_rock; } ;
struct TYPE_18__ {size_t extents; int b_xa; int filename; TYPE_3__ xa; int /*<<< orphan*/  tm; TYPE_2__ rr; void** extsize; int /*<<< orphan*/ * secsize; int /*<<< orphan*/  size; void** lsn; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ iso9660_stat_t ;
struct TYPE_15__ {char* str; int /*<<< orphan*/  len; } ;
struct TYPE_19__ {int file_flags; int /*<<< orphan*/  recording_time; TYPE_1__ filename; int /*<<< orphan*/  size; int /*<<< orphan*/  extent; } ;
typedef  TYPE_5__ iso9660_dir_t ;
typedef  int iso711_t ;
typedef  int /*<<< orphan*/  cdio_log_level_t ;
typedef  scalar_t__ bool_3way_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDIO_LOG_INFO ; 
 int /*<<< orphan*/  CDIO_LOG_WARN ; 
 int /*<<< orphan*/  ISO_BLOCKSIZE ; 
 int ISO_DIRECTORY ; 
 size_t ISO_MAX_MULTIEXTENT ; 
 int ISO_MULTIEXTENT ; 
 int /*<<< orphan*/  _STAT_DIR ; 
 int /*<<< orphan*/  _STAT_FILE ; 
 int /*<<< orphan*/  _cdio_len2blocks (void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  cdio_debug (char*,int,int,int,char,char,char,char) ; 
 int /*<<< orphan*/  cdio_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cdio_warn (char*,int) ; 
 int /*<<< orphan*/  dunno ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int from_711 (int /*<<< orphan*/ ) ; 
 void* from_733 (int /*<<< orphan*/ ) ; 
 int iso9660_get_dir_len (TYPE_5__*) ; 
 int /*<<< orphan*/  iso9660_get_dtime (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iso9660_stat_free (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,unsigned int) ; 
 scalar_t__ nope ; 
 scalar_t__ strcmp (int,char*) ; 
 int /*<<< orphan*/  strncpy (int,char*,int) ; 
 scalar_t__ yep ; 

__attribute__((used)) static iso9660_stat_t *
_iso9660_dir_to_statbuf (iso9660_dir_t *p_iso9660_dir,
			 iso9660_stat_t *last_p_stat,
			 bool_3way_t b_xa, uint8_t u_joliet_level)
{
  uint8_t dir_len= iso9660_get_dir_len(p_iso9660_dir);
  iso711_t i_fname;
  unsigned int stat_len;
  iso9660_stat_t *p_stat = last_p_stat;
  char rr_fname[256] = "";
  int  i_rr_fname;

  if (!dir_len) return NULL;

  i_fname  = from_711(p_iso9660_dir->filename.len);

  /* .. string in statbuf is one longer than in p_iso9660_dir's listing '\1' */
  stat_len      = sizeof(iso9660_stat_t)+i_fname+2;

  /* Reuse multiextent p_stat if not NULL */
  if (!p_stat)
    p_stat      = calloc(1, stat_len);
  if (!p_stat)
    {
    cdio_warn("Couldn't calloc(1, %d)", stat_len);
    return NULL;
    }
  p_stat->type    = (p_iso9660_dir->file_flags & ISO_DIRECTORY)
    ? _STAT_DIR : _STAT_FILE;
  p_stat->lsn[p_stat->extents] = from_733 (p_iso9660_dir->extent);
  p_stat->extsize[p_stat->extents] = from_733 (p_iso9660_dir->size);
  p_stat->size += p_stat->extsize[p_stat->extents];
  p_stat->secsize[p_stat->extents] = _cdio_len2blocks (p_stat->extsize[p_stat->extents], ISO_BLOCKSIZE);
  p_stat->rr.b3_rock = dunno; /*FIXME should do based on mask */
  p_stat->b_xa    = false;

  /* Only resolve the full filename when we're not dealing with extent */
  if ((p_iso9660_dir->file_flags & ISO_MULTIEXTENT) == 0)
  {
    /* Check if this is the last part of a multiextent file */
    if (p_stat->extents != 0) {
      if (strcmp(p_stat->filename, &p_iso9660_dir->filename.str[1]) != 0) {
	cdio_warn("Warning: Non consecutive multiextent file parts for '%s'", p_stat->filename);
	free(p_stat);
	return NULL;
      }
    }
    i_rr_fname =
#ifdef HAVE_ROCK
      get_rock_ridge_filename(p_iso9660_dir, rr_fname, p_stat);
#else
      0;
#endif

    if (i_rr_fname > 0) {
      if (i_rr_fname > i_fname) {
	/* realloc gives valgrind errors */
	iso9660_stat_t *p_stat_new =
	  calloc(1, sizeof(iso9660_stat_t)+i_rr_fname+2);
        if (!p_stat_new)
          {
          cdio_warn("Couldn't calloc(1, %d)", (int)(sizeof(iso9660_stat_t)+i_rr_fname+2));
	  free(p_stat);
          return NULL;
          }
	memcpy(p_stat_new, p_stat, stat_len);
	free(p_stat);
	p_stat = p_stat_new;
      }
      strncpy(p_stat->filename, rr_fname, i_rr_fname+1);
    } else {
      if ('\0' == p_iso9660_dir->filename.str[1] && 1 == i_fname)
	strncpy (p_stat->filename, ".", 2);
      else if ('\1' == p_iso9660_dir->filename.str[1] && 1 == i_fname)
	strncpy (p_stat->filename, "..", 3);
#ifdef HAVE_JOLIET
      else if (u_joliet_level) {
	int i_inlen = i_fname;
	cdio_utf8_t *p_psz_out = NULL;
	if (cdio_charset_to_utf8(&p_iso9660_dir->filename.str[1], i_inlen,
                             &p_psz_out, "UCS-2BE")) {
          strncpy(p_stat->filename, p_psz_out, i_fname);
          free(p_psz_out);
        }
        else {
          free(p_stat);
          return NULL;
        }
      }
#endif /*HAVE_JOLIET*/
      else {
	strncpy (p_stat->filename, &p_iso9660_dir->filename.str[1], i_fname);
      }
    }
  } else {
      /* Use the plain ISO-9660 name when dealing with a multiextent file part */
      strncpy(p_stat->filename, &p_iso9660_dir->filename.str[1], i_fname);
  }
  if (p_stat->extents >= ISO_MAX_MULTIEXTENT) {
      cdio_warn("Warning: Too many multiextent file parts for '%s'", p_stat->filename);
      free(p_stat->rr.psz_symlink);
      free(p_stat);
      return NULL;
  }
  p_stat->extents++;

  iso9660_get_dtime(&(p_iso9660_dir->recording_time), true, &(p_stat->tm));

  if (dir_len < sizeof (iso9660_dir_t)) {
    iso9660_stat_free(p_stat);
    return NULL;
  }


  {
    int su_length = iso9660_get_dir_len(p_iso9660_dir)
      - sizeof (iso9660_dir_t);
    su_length -= i_fname;

    if (su_length % 2)
      su_length--;

    if (su_length < 0 || su_length < sizeof (iso9660_xa_t))
      return p_stat;

    if (nope == b_xa) {
      return p_stat;
    } else {
      iso9660_xa_t *xa_data =
	(void *) (((char *) p_iso9660_dir)
		  + (iso9660_get_dir_len(p_iso9660_dir) - su_length));
      cdio_log_level_t loglevel = (yep == b_xa)
	? CDIO_LOG_WARN : CDIO_LOG_INFO;

      if (xa_data->signature[0] != 'X'
	  || xa_data->signature[1] != 'A')
	{
	  cdio_log (loglevel,
		    "XA signature not found in ISO9660's system use area;"
		     " ignoring XA attributes for this file entry.");
	  cdio_debug ("%d %d %d, '%c%c' (%d, %d)",
		      iso9660_get_dir_len(p_iso9660_dir),
		      i_fname,
		      su_length,
		      xa_data->signature[0], xa_data->signature[1],
		      xa_data->signature[0], xa_data->signature[1]);
	  return p_stat;
	}
      p_stat->b_xa = true;
      p_stat->xa   = *xa_data;
    }
  }
  return p_stat;

}