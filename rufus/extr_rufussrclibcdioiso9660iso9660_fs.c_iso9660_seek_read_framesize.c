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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int lsn_t ;
struct TYPE_3__ {int i_fuzzy_offset; int i_datastart; int /*<<< orphan*/  stream; scalar_t__ i_framesize; } ;
typedef  TYPE_1__ iso9660_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 long cdio_stream_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,long) ; 
 long cdio_stream_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long int
iso9660_seek_read_framesize (const iso9660_t *p_iso, void *ptr,
			     lsn_t start, long int size,
			     uint16_t i_framesize)
{
  long int ret;
  int64_t i_byte_offset;

  if (!p_iso) return 0;
  i_byte_offset = (start * (int64_t)(p_iso->i_framesize))
    + p_iso->i_fuzzy_offset + p_iso->i_datastart;

  ret = cdio_stream_seek (p_iso->stream, i_byte_offset, SEEK_SET);
  if (ret!=0) return 0;
  return cdio_stream_read (p_iso->stream, ptr, i_framesize, size);
}