#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cdio; int /*<<< orphan*/  stream; scalar_t__ b_stream; } ;
typedef  TYPE_1__ udf_t ;
typedef  int off_t ;
typedef  scalar_t__ lsn_t ;
typedef  scalar_t__ driver_return_code_t ;

/* Variables and functions */
 scalar_t__ DRIVER_OP_BAD_PARAMETER ; 
 scalar_t__ DRIVER_OP_ERROR ; 
 scalar_t__ DRIVER_OP_SUCCESS ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UDF_BLOCKSIZE ; 
 scalar_t__ cdio_read_data_sectors (int /*<<< orphan*/ ,void*,scalar_t__,int,long) ; 
 long cdio_stream_read (int /*<<< orphan*/ ,void*,int,long) ; 
 scalar_t__ cdio_stream_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdio_warn (char*) ; 

driver_return_code_t
udf_read_sectors (const udf_t *p_udf, void *ptr, lsn_t i_start,
		 long i_blocks)
{
  driver_return_code_t ret;
  long i_read;
  off_t i_byte_offset;

  if (!p_udf) return 0;
  /* Without the cast, i_start * UDF_BLOCKSIZE may be evaluated as 32 bit */
  i_byte_offset = ((off_t)i_start) * UDF_BLOCKSIZE;
  /* Since we're using SEEK_SET, the value must be positive */
  if (i_byte_offset < 0) {
    if (sizeof(off_t) <= 4)	/* probably missing LFS */
      cdio_warn("Large File Support is required to access streams of 2 GB or more");
    return DRIVER_OP_BAD_PARAMETER;
  }

  if (p_udf->b_stream) {
    ret = cdio_stream_seek (p_udf->stream, i_byte_offset, SEEK_SET);
    if (DRIVER_OP_SUCCESS != ret) return ret;
    i_read = cdio_stream_read (p_udf->stream, ptr, UDF_BLOCKSIZE, i_blocks);
    if (i_read) return DRIVER_OP_SUCCESS;
    return DRIVER_OP_ERROR;
  } else {
    return cdio_read_data_sectors(p_udf->cdio, ptr, i_start, UDF_BLOCKSIZE,
				  i_blocks);
  }
}