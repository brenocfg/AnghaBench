#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {TYPE_1__* header_; } ;
typedef  TYPE_2__ WebPMuxImage ;
struct TYPE_11__ {int x_offset; int y_offset; int duration; int /*<<< orphan*/  bitstream; int /*<<< orphan*/  id; int /*<<< orphan*/  blend_method; int /*<<< orphan*/  dispose_method; } ;
typedef  TYPE_3__ WebPMuxFrameInfo ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_12__ {scalar_t__ size; int* bytes; } ;
typedef  TYPE_4__ WebPData ;
struct TYPE_13__ {scalar_t__ tag; scalar_t__ size; } ;
struct TYPE_9__ {scalar_t__ tag_; TYPE_4__ data_; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkGetIdFromTag (scalar_t__) ; 
 int GetLE24 (int*) ; 
 size_t IDX_ANMF ; 
 int /*<<< orphan*/  SynthesizeBitstream (TYPE_2__ const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_MUX_BAD_DATA ; 
 int /*<<< orphan*/  WEBP_MUX_BLEND ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_BACKGROUND ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_NONE ; 
 int /*<<< orphan*/  WEBP_MUX_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  WEBP_MUX_NO_BLEND ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* kChunks ; 

__attribute__((used)) static WebPMuxError MuxGetFrameInternal(const WebPMuxImage* const wpi,
                                        WebPMuxFrameInfo* const frame) {
  const int is_frame = (wpi->header_->tag_ == kChunks[IDX_ANMF].tag);
  const WebPData* frame_data;
  if (!is_frame) return WEBP_MUX_INVALID_ARGUMENT;
  assert(wpi->header_ != NULL);  // Already checked by WebPMuxGetFrame().
  // Get frame chunk.
  frame_data = &wpi->header_->data_;
  if (frame_data->size < kChunks[IDX_ANMF].size) return WEBP_MUX_BAD_DATA;
  // Extract info.
  frame->x_offset = 2 * GetLE24(frame_data->bytes + 0);
  frame->y_offset = 2 * GetLE24(frame_data->bytes + 3);
  {
    const uint8_t bits = frame_data->bytes[15];
    frame->duration = GetLE24(frame_data->bytes + 12);
    frame->dispose_method =
        (bits & 1) ? WEBP_MUX_DISPOSE_BACKGROUND : WEBP_MUX_DISPOSE_NONE;
    frame->blend_method = (bits & 2) ? WEBP_MUX_NO_BLEND : WEBP_MUX_BLEND;
  }
  frame->id = ChunkGetIdFromTag(wpi->header_->tag_);
  return SynthesizeBitstream(wpi, &frame->bitstream);
}