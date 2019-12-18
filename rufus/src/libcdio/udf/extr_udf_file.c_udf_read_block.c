#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_position; } ;
typedef  TYPE_1__ udf_t ;
struct TYPE_7__ {TYPE_1__* p_udf; } ;
typedef  TYPE_2__ udf_dirent_t ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ lba_t ;
typedef  scalar_t__ driver_return_code_t ;

/* Variables and functions */
 scalar_t__ CDIO_INVALID_LBA ; 
 size_t CEILING (size_t,size_t) ; 
 scalar_t__ DRIVER_OP_ERROR ; 
 scalar_t__ DRIVER_OP_SUCCESS ; 
 scalar_t__ MIN (size_t,size_t) ; 
 size_t UDF_BLOCKSIZE ; 
 int /*<<< orphan*/  cdio_warn (char*,unsigned int,...) ; 
 scalar_t__ i_lba ; 
 scalar_t__ offset_to_lba (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ udf_read_sectors (TYPE_1__*,void*,scalar_t__,size_t) ; 

ssize_t
udf_read_block(const udf_dirent_t *p_udf_dirent, void * buf, size_t count)
{
  if (count == 0) return 0;
  else {
    driver_return_code_t ret;
    uint32_t i_max_size=0;
    udf_t *p_udf = p_udf_dirent->p_udf;
    lba_t i_lba = offset_to_lba(p_udf_dirent, p_udf->i_position, &i_lba, 
				&i_max_size);
    if (i_lba != CDIO_INVALID_LBA) {
      uint32_t i_max_blocks = CEILING(i_max_size, UDF_BLOCKSIZE);
      if ( i_max_blocks < count ) {
	  cdio_warn("read count %u is larger than %u extent size.",
		  (unsigned int)count, i_max_blocks);
	  cdio_warn("read count truncated to %u", (unsigned int)count);
	  count = i_max_blocks;
      }
      ret = udf_read_sectors(p_udf, buf, i_lba, count);
      if (DRIVER_OP_SUCCESS == ret) {
	ssize_t i_read_len = MIN(i_max_size, count * UDF_BLOCKSIZE);
	p_udf->i_position += i_read_len;
	return i_read_len;
      }
      return ret;
    } else {
      return DRIVER_OP_ERROR;
    }
  }
}