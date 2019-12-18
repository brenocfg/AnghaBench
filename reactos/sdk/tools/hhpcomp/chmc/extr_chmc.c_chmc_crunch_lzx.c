#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct chmcLzxInfo {int fd; TYPE_3__* section; struct chmcFile* chm; scalar_t__ fd_offset; scalar_t__ eof; scalar_t__ error; int /*<<< orphan*/  pos; int /*<<< orphan*/  todo; scalar_t__ done; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct chmcFile {TYPE_1__ entries_list; TYPE_3__** sections; } ;
typedef  int /*<<< orphan*/  lzx_results ;
typedef  int /*<<< orphan*/  lzx_data ;
struct TYPE_5__ {int /*<<< orphan*/  block_count; } ;
struct TYPE_6__ {TYPE_2__ reset_table_header; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int CHMC_EINVAL ; 
 int CHMC_NOERR ; 
 int /*<<< orphan*/  _lzx_at_eof (struct chmcLzxInfo*) ; 
 int /*<<< orphan*/  _lzx_get_bytes ; 
 int /*<<< orphan*/  _lzx_mark_frame ; 
 int /*<<< orphan*/  _lzx_put_bytes ; 
 int /*<<< orphan*/  assert (struct chmcFile*) ; 
 int /*<<< orphan*/  chmc_compressed_add_mark (struct chmcFile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lzx_compress_block (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lzx_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzx_init (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,struct chmcLzxInfo*,int /*<<< orphan*/  (*) (struct chmcLzxInfo*),int /*<<< orphan*/ ,struct chmcLzxInfo*,int /*<<< orphan*/ ,struct chmcLzxInfo*) ; 
 int /*<<< orphan*/  lzx_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int chmc_crunch_lzx(struct chmcFile *chm, int sect_id)
{
	struct chmcLzxInfo lzx_info;

	lzx_data *lzxd;
	int subd_ok = 1;
	int do_reset = 1;
	int block_size;
	lzx_results lzxr;
	int wsize_code = 16;

	assert(chm);

	if ((wsize_code < 15) || (wsize_code > 21)) {
		fprintf(stderr, "window size must be between 15 and 21 inclusive\n");
		return CHMC_EINVAL;
	}

	lzx_info.chm = chm;
	lzx_info.section = chm->sections[sect_id];
	lzx_info.done = 0;
	lzx_info.todo = lzx_info.section->offset;
	lzx_info.pos = chm->entries_list.next;
	lzx_info.error = 0;
	lzx_info.eof = 0;

	lzx_info.fd = -1;
	lzx_info.fd_offset = 0;

	chmc_compressed_add_mark(lzx_info.chm, 0);
	lzx_info.section->reset_table_header.block_count++;

	/* undocumented fact, according to Caie --
	   block size cannot exceed window size.  (why not?) */
	/* The block size must not be larger than the window size.
	   While the compressor will create apparently-valid LZX files
	   if this restriction is violated, some decompressors
	   will not handle them. */

	block_size = 1 << wsize_code;

	//  lzx_info.section->control_data.windowSize = wsize_code;
	//  lzx_info.section->control_data.windowsPerReset = block_size;

	lzx_init(&lzxd, wsize_code,
	         _lzx_get_bytes, &lzx_info, _lzx_at_eof,
	         _lzx_put_bytes, &lzx_info,
	         _lzx_mark_frame, &lzx_info);

	while(! _lzx_at_eof(&lzx_info)) {
		if (do_reset)
			lzx_reset(lzxd);
		lzx_compress_block(lzxd, block_size, subd_ok);
	}
	lzx_finish(lzxd, &lzxr);

	return CHMC_NOERR;
}