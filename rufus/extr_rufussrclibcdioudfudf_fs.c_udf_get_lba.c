#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  pos; } ;
typedef  TYPE_5__ udf_short_ad_t ;
struct TYPE_11__ {int /*<<< orphan*/  lba; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; TYPE_2__ loc; } ;
typedef  TYPE_6__ udf_long_ad_t ;
struct TYPE_12__ {int ext_attr; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  i_extended_attr; TYPE_3__ u; TYPE_1__ icb_tag; int /*<<< orphan*/  i_alloc_descs; } ;
typedef  TYPE_7__ udf_file_entry_t ;
struct TYPE_13__ {int /*<<< orphan*/  lba; } ;
struct TYPE_17__ {int /*<<< orphan*/  len; TYPE_4__ ext_loc; } ;
typedef  TYPE_8__ udf_ext_ad_t ;

/* Variables and functions */
#define  ICBTAG_FLAG_AD_EXTENDED 130 
#define  ICBTAG_FLAG_AD_LONG 129 
 int ICBTAG_FLAG_AD_MASK ; 
#define  ICBTAG_FLAG_AD_SHORT 128 
 int UDF_BLOCKSIZE ; 
 int UDF_LENGTH_MASK ; 
 int uint32_from_le (int /*<<< orphan*/ ) ; 

bool
udf_get_lba(const udf_file_entry_t *p_udf_fe,
	    /*out*/ uint32_t *start, /*out*/ uint32_t *end)
{
  if (! p_udf_fe->i_alloc_descs)
    return false;

  switch (p_udf_fe->icb_tag.flags & ICBTAG_FLAG_AD_MASK) {
  case ICBTAG_FLAG_AD_SHORT:
    {
      /* The allocation descriptor field is filled with short_ad's. */
      udf_short_ad_t *p_ad = (udf_short_ad_t *)
	(p_udf_fe->u.ext_attr + uint32_from_le(p_udf_fe->i_extended_attr));

      *start = uint32_from_le(p_ad->pos);
      *end = *start +
	((uint32_from_le(p_ad->len) & UDF_LENGTH_MASK) - 1) / UDF_BLOCKSIZE;
      return true;
    }
    break;
  case ICBTAG_FLAG_AD_LONG:
    {
      /* The allocation descriptor field is filled with long_ad's */
      udf_long_ad_t *p_ad = (udf_long_ad_t *)
	(p_udf_fe->u.ext_attr + uint32_from_le(p_udf_fe->i_extended_attr));

      *start = uint32_from_le(p_ad->loc.lba); /* ignore partition number */
      *end = *start +
	((uint32_from_le(p_ad->len) & UDF_LENGTH_MASK) - 1) / UDF_BLOCKSIZE;
      return true;
    }
    break;
  case ICBTAG_FLAG_AD_EXTENDED:
    {
      udf_ext_ad_t *p_ad = (udf_ext_ad_t *)
	(p_udf_fe->u.ext_attr + uint32_from_le(p_udf_fe->i_extended_attr));

      *start = uint32_from_le(p_ad->ext_loc.lba); /* ignore partition number */
      *end = *start +
	((uint32_from_le(p_ad->len) & UDF_LENGTH_MASK) - 1) / UDF_BLOCKSIZE;
      return true;
    }
    break;
  default:
    return false;
  }
  return false;
}