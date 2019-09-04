#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct workspace {int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem; int /*<<< orphan*/  window_size; } ;
struct squashfs_sb_info {scalar_t__ devblksize; } ;
struct squashfs_page_actor {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ pos; int /*<<< orphan*/ * dst; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {scalar_t__ pos; scalar_t__ size; scalar_t__ src; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_DStream ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ERROR (char*,...) ; 
 void* PAGE_SIZE ; 
 size_t ZSTD_decompressStream (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ ZSTD_getErrorCode (size_t) ; 
 int /*<<< orphan*/ * ZSTD_initDStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  squashfs_finish_page (struct squashfs_page_actor*) ; 
 int /*<<< orphan*/ * squashfs_first_page (struct squashfs_page_actor*) ; 
 int /*<<< orphan*/ * squashfs_next_page (struct squashfs_page_actor*) ; 

__attribute__((used)) static int zstd_uncompress(struct squashfs_sb_info *msblk, void *strm,
	struct buffer_head **bh, int b, int offset, int length,
	struct squashfs_page_actor *output)
{
	struct workspace *wksp = strm;
	ZSTD_DStream *stream;
	size_t total_out = 0;
	size_t zstd_err;
	int k = 0;
	ZSTD_inBuffer in_buf = { NULL, 0, 0 };
	ZSTD_outBuffer out_buf = { NULL, 0, 0 };

	stream = ZSTD_initDStream(wksp->window_size, wksp->mem, wksp->mem_size);

	if (!stream) {
		ERROR("Failed to initialize zstd decompressor\n");
		goto out;
	}

	out_buf.size = PAGE_SIZE;
	out_buf.dst = squashfs_first_page(output);

	do {
		if (in_buf.pos == in_buf.size && k < b) {
			int avail = min(length, msblk->devblksize - offset);

			length -= avail;
			in_buf.src = bh[k]->b_data + offset;
			in_buf.size = avail;
			in_buf.pos = 0;
			offset = 0;
		}

		if (out_buf.pos == out_buf.size) {
			out_buf.dst = squashfs_next_page(output);
			if (out_buf.dst == NULL) {
				/* Shouldn't run out of pages
				 * before stream is done.
				 */
				squashfs_finish_page(output);
				goto out;
			}
			out_buf.pos = 0;
			out_buf.size = PAGE_SIZE;
		}

		total_out -= out_buf.pos;
		zstd_err = ZSTD_decompressStream(stream, &out_buf, &in_buf);
		total_out += out_buf.pos; /* add the additional data produced */

		if (in_buf.pos == in_buf.size && k < b)
			put_bh(bh[k++]);
	} while (zstd_err != 0 && !ZSTD_isError(zstd_err));

	squashfs_finish_page(output);

	if (ZSTD_isError(zstd_err)) {
		ERROR("zstd decompression error: %d\n",
				(int)ZSTD_getErrorCode(zstd_err));
		goto out;
	}

	if (k < b)
		goto out;

	return (int)total_out;

out:
	for (; k < b; k++)
		put_bh(bh[k]);

	return -EIO;
}