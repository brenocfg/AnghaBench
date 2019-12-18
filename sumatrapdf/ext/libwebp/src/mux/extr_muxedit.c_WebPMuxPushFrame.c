#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_16__ {TYPE_14__* header_; int /*<<< orphan*/  height_; int /*<<< orphan*/  width_; int /*<<< orphan*/ * img_; } ;
typedef  TYPE_1__ WebPMuxImage ;
struct TYPE_20__ {scalar_t__ size; int /*<<< orphan*/ * bytes; } ;
struct TYPE_17__ {scalar_t__ id; int x_offset; int y_offset; scalar_t__ duration; int dispose_method; TYPE_7__ bitstream; } ;
typedef  TYPE_2__ WebPMuxFrameInfo ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_18__ {TYPE_1__* images_; } ;
typedef  TYPE_3__ WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;
struct TYPE_19__ {scalar_t__ tag; } ;
struct TYPE_15__ {int /*<<< orphan*/  tag_; } ;

/* Variables and functions */
 scalar_t__ AddDataToChunkList (int /*<<< orphan*/ *,int,scalar_t__ const,TYPE_14__**) ; 
 scalar_t__ ChunkGetIdFromTag (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFrameData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t IDX_ANMF ; 
 scalar_t__ MAX_CHUNK_PAYLOAD ; 
 scalar_t__ MAX_DURATION ; 
 int MAX_POSITION_OFFSET ; 
 int /*<<< orphan*/  MuxImageInit (TYPE_1__*) ; 
 scalar_t__ MuxImagePush (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  MuxImageRelease (TYPE_1__*) ; 
 scalar_t__ SetAlphaAndImageChunks (TYPE_7__*,int,TYPE_1__*) ; 
 scalar_t__ WEBP_CHUNK_ANMF ; 
 scalar_t__ WEBP_CHUNK_IMAGE ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* kChunks ; 

WebPMuxError WebPMuxPushFrame(WebPMux* mux, const WebPMuxFrameInfo* info,
                              int copy_data) {
  WebPMuxImage wpi;
  WebPMuxError err;

  // Sanity checks.
  if (mux == NULL || info == NULL) return WEBP_MUX_INVALID_ARGUMENT;

  if (info->id != WEBP_CHUNK_ANMF) return WEBP_MUX_INVALID_ARGUMENT;

  if (info->bitstream.bytes == NULL ||
      info->bitstream.size > MAX_CHUNK_PAYLOAD) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  if (mux->images_ != NULL) {
    const WebPMuxImage* const image = mux->images_;
    const uint32_t image_id = (image->header_ != NULL) ?
        ChunkGetIdFromTag(image->header_->tag_) : WEBP_CHUNK_IMAGE;
    if (image_id != info->id) {
      return WEBP_MUX_INVALID_ARGUMENT;  // Conflicting frame types.
    }
  }

  MuxImageInit(&wpi);
  err = SetAlphaAndImageChunks(&info->bitstream, copy_data, &wpi);
  if (err != WEBP_MUX_OK) goto Err;
  assert(wpi.img_ != NULL);  // As SetAlphaAndImageChunks() was successful.

  {
    WebPData frame;
    const uint32_t tag = kChunks[IDX_ANMF].tag;
    WebPMuxFrameInfo tmp = *info;
    tmp.x_offset &= ~1;  // Snap offsets to even.
    tmp.y_offset &= ~1;
    if (tmp.x_offset < 0 || tmp.x_offset >= MAX_POSITION_OFFSET ||
        tmp.y_offset < 0 || tmp.y_offset >= MAX_POSITION_OFFSET ||
        (tmp.duration < 0 || tmp.duration >= MAX_DURATION) ||
        tmp.dispose_method != (tmp.dispose_method & 1)) {
      err = WEBP_MUX_INVALID_ARGUMENT;
      goto Err;
    }
    err = CreateFrameData(wpi.width_, wpi.height_, &tmp, &frame);
    if (err != WEBP_MUX_OK) goto Err;
    // Add frame chunk (with copy_data = 1).
    err = AddDataToChunkList(&frame, 1, tag, &wpi.header_);
    WebPDataClear(&frame);  // frame owned by wpi.header_ now.
    if (err != WEBP_MUX_OK) goto Err;
  }

  // Add this WebPMuxImage to mux.
  err = MuxImagePush(&wpi, &mux->images_);
  if (err != WEBP_MUX_OK) goto Err;

  // All is well.
  return WEBP_MUX_OK;

 Err:  // Something bad happened.
  MuxImageRelease(&wpi);
  return err;
}