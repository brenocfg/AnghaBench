#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_4__ {size_t bytes_left; size_t offset; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/  inflate; } ;
struct ar_archive_zip_uncomp {TYPE_2__ input; TYPE_1__ state; } ;

/* Variables and functions */
 int EOF ; 
 size_t ERR_UNCOMP ; 
 int inflate_process (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,void*,size_t*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static uint32_t zip_uncompress_data_deflate64(struct ar_archive_zip_uncomp *uncomp, void *buffer, uint32_t buffer_size, bool is_last_chunk)
{
    size_t avail_in = uncomp->input.bytes_left;
    size_t avail_out = buffer_size;

    int result = inflate_process(uncomp->state.inflate, &uncomp->input.data[uncomp->input.offset], &avail_in, buffer, &avail_out);

    uncomp->input.offset += uncomp->input.bytes_left - (uint16_t)avail_in;
    uncomp->input.bytes_left = (uint16_t)avail_in;

    if (result && result != EOF) {
        warn("Unexpected Inflate error %d", result);
        return ERR_UNCOMP;
    }
    if (result == EOF && (!is_last_chunk || avail_out)) {
        warn("Premature EOS in Deflate stream");
        return ERR_UNCOMP;
    }

    return buffer_size - (uint32_t)avail_out;
}