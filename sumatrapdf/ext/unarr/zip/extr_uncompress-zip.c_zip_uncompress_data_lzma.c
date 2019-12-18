#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {int bytes_left; scalar_t__* data; int offset; scalar_t__ at_eof; } ;
struct TYPE_10__ {int /*<<< orphan*/  dic; } ;
struct TYPE_7__ {TYPE_4__ dec; int /*<<< orphan*/  finish; int /*<<< orphan*/  alloc; } ;
struct TYPE_8__ {TYPE_1__ lzma; } ;
struct ar_archive_zip_uncomp {TYPE_3__ input; TYPE_2__ state; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  scalar_t__ ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;

/* Variables and functions */
 scalar_t__ ERR_UNCOMP ; 
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 scalar_t__ LZMA_STATUS_FINISHED_WITH_MARK ; 
 scalar_t__ LzmaDec_Allocate (TYPE_4__*,scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaDec_DecodeToBuf (TYPE_4__*,void*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  LzmaDec_Init (TYPE_4__*) ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static uint32_t zip_uncompress_data_lzma(struct ar_archive_zip_uncomp *uncomp, void *buffer, uint32_t buffer_size, bool is_last_chunk)
{
    SizeT srclen, dstlen;
    ELzmaStatus status;
    ELzmaFinishMode finish;
    SRes res;

    if (!uncomp->state.lzma.dec.dic) {
        uint8_t propsize;
        if (uncomp->input.bytes_left < 9) {
            warn("Insufficient data in compressed stream");
            return ERR_UNCOMP;
        }
        propsize = uncomp->input.data[uncomp->input.offset + 2];
        if (uncomp->input.data[uncomp->input.offset + 3] != 0 || uncomp->input.bytes_left < 4 + propsize) {
            warn("Insufficient data in compressed stream");
            return ERR_UNCOMP;
        }
        res = LzmaDec_Allocate(&uncomp->state.lzma.dec, &uncomp->input.data[uncomp->input.offset + 4], propsize, &uncomp->state.lzma.alloc);
        uncomp->input.offset += 4 + propsize;
        uncomp->input.bytes_left -= 4 + propsize;
        if (res != SZ_OK)
            return ERR_UNCOMP;
        LzmaDec_Init(&uncomp->state.lzma.dec);
    }

    srclen = uncomp->input.bytes_left;
    dstlen = buffer_size;
    finish = uncomp->input.at_eof && is_last_chunk ? uncomp->state.lzma.finish : LZMA_FINISH_ANY;
    res = LzmaDec_DecodeToBuf(&uncomp->state.lzma.dec, buffer, &dstlen, &uncomp->input.data[uncomp->input.offset], &srclen, finish, &status);

    uncomp->input.offset += (uint16_t)srclen;
    uncomp->input.bytes_left -= (uint16_t)srclen;

    if (res != SZ_OK || (srclen == 0 && dstlen == 0)) {
        warn("Unexpected LZMA error %d", res);
        return ERR_UNCOMP;
    }
    if (status == LZMA_STATUS_FINISHED_WITH_MARK && (!is_last_chunk || dstlen != buffer_size)) {
        warn("Premature EOS in LZMA stream");
        return ERR_UNCOMP;
    }

    return (uint32_t)dstlen;
}