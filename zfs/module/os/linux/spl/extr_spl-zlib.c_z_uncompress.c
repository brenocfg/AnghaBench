#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ avail_in; size_t total_out; int /*<<< orphan*/  workspace; void* avail_out; void* next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  void* uInt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int Z_BUF_ERROR ; 
 int Z_DATA_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_MEM_ERROR ; 
 int Z_NEED_DICT ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int zlib_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int zlib_inflateEnd (TYPE_1__*) ; 
 int zlib_inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_workspace_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_workspace_free (int /*<<< orphan*/ ) ; 

int
z_uncompress(void *dest, size_t *destLen, const void *source, size_t sourceLen)
{
	z_stream stream;
	int err;

	stream.next_in = (Byte *)source;
	stream.avail_in = (uInt)sourceLen;
	stream.next_out = dest;
	stream.avail_out = (uInt)*destLen;

	if ((size_t)stream.avail_out != *destLen)
		return (Z_BUF_ERROR);

	stream.workspace = zlib_workspace_alloc(KM_SLEEP);
	if (!stream.workspace)
		return (Z_MEM_ERROR);

	err = zlib_inflateInit(&stream);
	if (err != Z_OK) {
		zlib_workspace_free(stream.workspace);
		return (err);
	}

	err = zlib_inflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END) {
		zlib_inflateEnd(&stream);
		zlib_workspace_free(stream.workspace);

		if (err == Z_NEED_DICT ||
		    (err == Z_BUF_ERROR && stream.avail_in == 0))
			return (Z_DATA_ERROR);

		return (err);
	}
	*destLen = stream.total_out;

	err = zlib_inflateEnd(&stream);
	zlib_workspace_free(stream.workspace);

	return (err);
}