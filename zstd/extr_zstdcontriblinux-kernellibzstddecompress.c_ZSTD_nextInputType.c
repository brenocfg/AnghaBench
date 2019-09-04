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
typedef  int /*<<< orphan*/  ZSTD_nextInputType_e ;
struct TYPE_3__ {int stage; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
#define  ZSTDds_checkChecksum 135 
#define  ZSTDds_decodeBlockHeader 134 
#define  ZSTDds_decodeFrameHeader 133 
#define  ZSTDds_decodeSkippableHeader 132 
#define  ZSTDds_decompressBlock 131 
#define  ZSTDds_decompressLastBlock 130 
#define  ZSTDds_getFrameHeaderSize 129 
#define  ZSTDds_skipFrame 128 
 int /*<<< orphan*/  ZSTDnit_block ; 
 int /*<<< orphan*/  ZSTDnit_blockHeader ; 
 int /*<<< orphan*/  ZSTDnit_checksum ; 
 int /*<<< orphan*/  ZSTDnit_frameHeader ; 
 int /*<<< orphan*/  ZSTDnit_lastBlock ; 
 int /*<<< orphan*/  ZSTDnit_skippableFrame ; 

ZSTD_nextInputType_e ZSTD_nextInputType(ZSTD_DCtx *dctx)
{
	switch (dctx->stage) {
	default: /* should not happen */
	case ZSTDds_getFrameHeaderSize:
	case ZSTDds_decodeFrameHeader: return ZSTDnit_frameHeader;
	case ZSTDds_decodeBlockHeader: return ZSTDnit_blockHeader;
	case ZSTDds_decompressBlock: return ZSTDnit_block;
	case ZSTDds_decompressLastBlock: return ZSTDnit_lastBlock;
	case ZSTDds_checkChecksum: return ZSTDnit_checksum;
	case ZSTDds_decodeSkippableHeader:
	case ZSTDds_skipFrame: return ZSTDnit_skippableFrame;
	}
}