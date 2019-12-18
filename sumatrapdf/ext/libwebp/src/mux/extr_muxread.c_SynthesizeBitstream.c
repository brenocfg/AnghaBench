#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_5__* img_; TYPE_5__* alpha_; int /*<<< orphan*/  height_; int /*<<< orphan*/  width_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_8__ {size_t size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_2__ WebPData ;
struct TYPE_9__ {int /*<<< orphan*/ * next_; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_FLAG ; 
 size_t CHUNK_HEADER_SIZE ; 
 size_t const ChunkDiskSize (TYPE_5__*) ; 
 int /*<<< orphan*/ * ChunkListEmit (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EmitVP8XChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MuxEmitRiffHeader (int /*<<< orphan*/ * const,size_t const) ; 
 size_t const RIFF_HEADER_SIZE ; 
 size_t VP8X_CHUNK_SIZE ; 
 int /*<<< orphan*/  WEBP_MUX_MEMORY_ERROR ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static WebPMuxError SynthesizeBitstream(const WebPMuxImage* const wpi,
                                        WebPData* const bitstream) {
  uint8_t* dst;

  // Allocate data.
  const int need_vp8x = (wpi->alpha_ != NULL);
  const size_t vp8x_size = need_vp8x ? CHUNK_HEADER_SIZE + VP8X_CHUNK_SIZE : 0;
  const size_t alpha_size = need_vp8x ? ChunkDiskSize(wpi->alpha_) : 0;
  // Note: No need to output ANMF chunk for a single image.
  const size_t size = RIFF_HEADER_SIZE + vp8x_size + alpha_size +
                      ChunkDiskSize(wpi->img_);
  uint8_t* const data = (uint8_t*)WebPSafeMalloc(1ULL, size);
  if (data == NULL) return WEBP_MUX_MEMORY_ERROR;

  // There should be at most one alpha_ chunk and exactly one img_ chunk.
  assert(wpi->alpha_ == NULL || wpi->alpha_->next_ == NULL);
  assert(wpi->img_ != NULL && wpi->img_->next_ == NULL);

  // Main RIFF header.
  dst = MuxEmitRiffHeader(data, size);

  if (need_vp8x) {
    dst = EmitVP8XChunk(dst, wpi->width_, wpi->height_, ALPHA_FLAG);  // VP8X.
    dst = ChunkListEmit(wpi->alpha_, dst);       // ALPH.
  }

  // Bitstream.
  dst = ChunkListEmit(wpi->img_, dst);
  assert(dst == data + size);

  // Output.
  bitstream->bytes = data;
  bitstream->size = size;
  return WEBP_MUX_OK;
}