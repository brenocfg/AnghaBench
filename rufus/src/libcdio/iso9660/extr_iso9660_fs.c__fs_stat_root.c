#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iso_extension_mask_t ;
typedef  int /*<<< orphan*/  iso9660_stat_t ;
typedef  int /*<<< orphan*/  iso9660_dir_t ;
struct TYPE_9__ {int /*<<< orphan*/  root_directory_record; } ;
struct TYPE_8__ {int /*<<< orphan*/  root_directory_record; } ;
struct TYPE_10__ {scalar_t__ u_joliet_level; TYPE_2__ pvd; TYPE_1__ svd; } ;
typedef  TYPE_3__ generic_img_private_t ;
typedef  int /*<<< orphan*/  bool_3way_t ;
struct TYPE_11__ {scalar_t__ env; } ;
typedef  TYPE_4__ CdIo_t ;

/* Variables and functions */
#define  CDIO_DISC_MODE_CD_DATA 129 
#define  CDIO_DISC_MODE_CD_XA 128 
 int /*<<< orphan*/  ISO_EXTENSION_ALL ; 
 int /*<<< orphan*/  ISO_EXTENSION_JOLIET ; 
 int /*<<< orphan*/ * _iso9660_dir_to_statbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int cdio_get_discmode (TYPE_4__*) ; 
 int /*<<< orphan*/  cdio_warn (char*) ; 
 int /*<<< orphan*/  dunno ; 
 int /*<<< orphan*/  iso9660_fs_read_superblock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nope ; 
 int /*<<< orphan*/  yep ; 

__attribute__((used)) static iso9660_stat_t *
_fs_stat_root (CdIo_t *p_cdio)
{

  if (!p_cdio) return NULL;

  {
    iso_extension_mask_t iso_extension_mask = ISO_EXTENSION_ALL;
    generic_img_private_t *p_env = (generic_img_private_t *) p_cdio->env;
    iso9660_dir_t *p_iso9660_dir;
    iso9660_stat_t *p_stat;
    bool_3way_t b_xa;

    if (!p_env->u_joliet_level)
      iso_extension_mask &= ~ISO_EXTENSION_JOLIET;

    /* FIXME try also with Joliet.*/
    if ( !iso9660_fs_read_superblock (p_cdio, iso_extension_mask) ) {
      cdio_warn("Could not read ISO-9660 Superblock.");
      return NULL;
    }

    switch(cdio_get_discmode(p_cdio)) {
    case CDIO_DISC_MODE_CD_XA:
      b_xa = yep;
      break;
    case CDIO_DISC_MODE_CD_DATA:
      b_xa = nope;
      break;
    default:
      b_xa = dunno;
    }

#ifdef HAVE_JOLIET
    p_iso9660_dir = p_env->u_joliet_level
      ? &(p_env->svd.root_directory_record)
      : &(p_env->pvd.root_directory_record) ;
#else
    p_iso9660_dir = &(p_env->pvd.root_directory_record) ;
#endif

    p_stat = _iso9660_dir_to_statbuf (p_iso9660_dir, NULL,
				      b_xa, p_env->u_joliet_level);
    return p_stat;
  }

}