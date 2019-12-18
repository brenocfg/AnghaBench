#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {int is_partial_; int /*<<< orphan*/ * img_; int /*<<< orphan*/ * alpha_; int /*<<< orphan*/ * header_; TYPE_4__* unknown_; } ;
typedef  TYPE_2__ WebPMuxImage ;
struct TYPE_20__ {size_t const member_1; int /*<<< orphan*/  const* member_0; } ;
typedef  TYPE_3__ WebPData ;
struct TYPE_18__ {size_t size; int /*<<< orphan*/ * bytes; } ;
struct TYPE_21__ {scalar_t__ tag_; TYPE_1__ data_; } ;
typedef  TYPE_4__ WebPChunk ;
struct TYPE_22__ {scalar_t__ tag; } ;

/* Variables and functions */
 size_t ANMF_CHUNK_SIZE ; 
 size_t CHUNK_HEADER_SIZE ; 
 scalar_t__ ChunkAppend (TYPE_4__*,TYPE_4__***) ; 
 int /*<<< orphan*/  ChunkAssignData (TYPE_4__*,TYPE_3__ const*,int,scalar_t__) ; 
 size_t ChunkDiskSize (TYPE_4__*) ; 
 int ChunkGetIdFromTag (scalar_t__) ; 
 int /*<<< orphan*/  ChunkInit (TYPE_4__*) ; 
 int /*<<< orphan*/  ChunkRelease (TYPE_4__*) ; 
 scalar_t__ ChunkSetHead (TYPE_4__*,int /*<<< orphan*/ **) ; 
 scalar_t__ ChunkVerifyAndAssign (TYPE_4__*,int /*<<< orphan*/  const*,size_t,size_t,int) ; 
 size_t IDX_ANMF ; 
 int /*<<< orphan*/  MuxImageFinalize (TYPE_2__* const) ; 
#define  WEBP_CHUNK_ALPHA 130 
#define  WEBP_CHUNK_IMAGE 129 
#define  WEBP_CHUNK_UNKNOWN 128 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* kChunks ; 

__attribute__((used)) static int MuxImageParse(const WebPChunk* const chunk, int copy_data,
                         WebPMuxImage* const wpi) {
  const uint8_t* bytes = chunk->data_.bytes;
  size_t size = chunk->data_.size;
  const uint8_t* const last = bytes + size;
  WebPChunk subchunk;
  size_t subchunk_size;
  WebPChunk** unknown_chunk_list = &wpi->unknown_;
  ChunkInit(&subchunk);

  assert(chunk->tag_ == kChunks[IDX_ANMF].tag);
  assert(!wpi->is_partial_);

  // ANMF.
  {
    const size_t hdr_size = ANMF_CHUNK_SIZE;
    const WebPData temp = { bytes, hdr_size };
    // Each of ANMF chunk contain a header at the beginning. So, its size should
    // be at least 'hdr_size'.
    if (size < hdr_size) goto Fail;
    ChunkAssignData(&subchunk, &temp, copy_data, chunk->tag_);
  }
  ChunkSetHead(&subchunk, &wpi->header_);
  wpi->is_partial_ = 1;  // Waiting for ALPH and/or VP8/VP8L chunks.

  // Rest of the chunks.
  subchunk_size = ChunkDiskSize(&subchunk) - CHUNK_HEADER_SIZE;
  bytes += subchunk_size;
  size -= subchunk_size;

  while (bytes != last) {
    ChunkInit(&subchunk);
    if (ChunkVerifyAndAssign(&subchunk, bytes, size, size,
                             copy_data) != WEBP_MUX_OK) {
      goto Fail;
    }
    switch (ChunkGetIdFromTag(subchunk.tag_)) {
      case WEBP_CHUNK_ALPHA:
        if (wpi->alpha_ != NULL) goto Fail;  // Consecutive ALPH chunks.
        if (ChunkSetHead(&subchunk, &wpi->alpha_) != WEBP_MUX_OK) goto Fail;
        wpi->is_partial_ = 1;  // Waiting for a VP8 chunk.
        break;
      case WEBP_CHUNK_IMAGE:
        if (wpi->img_ != NULL) goto Fail;  // Only 1 image chunk allowed.
        if (ChunkSetHead(&subchunk, &wpi->img_) != WEBP_MUX_OK) goto Fail;
        if (!MuxImageFinalize(wpi)) goto Fail;
        wpi->is_partial_ = 0;  // wpi is completely filled.
        break;
      case WEBP_CHUNK_UNKNOWN:
        if (wpi->is_partial_) {
          goto Fail;  // Encountered an unknown chunk
                      // before some image chunks.
        }
        if (ChunkAppend(&subchunk, &unknown_chunk_list) != WEBP_MUX_OK) {
          goto Fail;
        }
        break;
      default:
        goto Fail;
        break;
    }
    subchunk_size = ChunkDiskSize(&subchunk);
    bytes += subchunk_size;
    size -= subchunk_size;
  }
  if (wpi->is_partial_) goto Fail;
  return 1;

 Fail:
  ChunkRelease(&subchunk);
  return 0;
}