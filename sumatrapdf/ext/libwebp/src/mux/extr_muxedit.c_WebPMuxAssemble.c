#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_9__ {int /*<<< orphan*/  unknown_; int /*<<< orphan*/  xmp_; int /*<<< orphan*/  exif_; int /*<<< orphan*/  images_; int /*<<< orphan*/  anim_; int /*<<< orphan*/  iccp_; int /*<<< orphan*/  vp8x_; } ;
typedef  TYPE_1__ WebPMux ;
struct TYPE_10__ {size_t size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_2__ WebPData ;

/* Variables and functions */
 size_t ChunkListDiskSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ChunkListEmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateVP8XChunk (TYPE_1__*) ; 
 size_t ImageListDiskSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ImageListEmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MuxCleanup (TYPE_1__*) ; 
 int /*<<< orphan*/ * MuxEmitRiffHeader (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ MuxValidate (TYPE_1__*) ; 
 size_t RIFF_HEADER_SIZE ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_MEMORY_ERROR ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

WebPMuxError WebPMuxAssemble(WebPMux* mux, WebPData* assembled_data) {
  size_t size = 0;
  uint8_t* data = NULL;
  uint8_t* dst = NULL;
  WebPMuxError err;

  if (assembled_data == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  // Clean up returned data, in case something goes wrong.
  memset(assembled_data, 0, sizeof(*assembled_data));

  if (mux == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  // Finalize mux.
  err = MuxCleanup(mux);
  if (err != WEBP_MUX_OK) return err;
  err = CreateVP8XChunk(mux);
  if (err != WEBP_MUX_OK) return err;

  // Allocate data.
  size = ChunkListDiskSize(mux->vp8x_) + ChunkListDiskSize(mux->iccp_)
       + ChunkListDiskSize(mux->anim_) + ImageListDiskSize(mux->images_)
       + ChunkListDiskSize(mux->exif_) + ChunkListDiskSize(mux->xmp_)
       + ChunkListDiskSize(mux->unknown_) + RIFF_HEADER_SIZE;

  data = (uint8_t*)WebPSafeMalloc(1ULL, size);
  if (data == NULL) return WEBP_MUX_MEMORY_ERROR;

  // Emit header & chunks.
  dst = MuxEmitRiffHeader(data, size);
  dst = ChunkListEmit(mux->vp8x_, dst);
  dst = ChunkListEmit(mux->iccp_, dst);
  dst = ChunkListEmit(mux->anim_, dst);
  dst = ImageListEmit(mux->images_, dst);
  dst = ChunkListEmit(mux->exif_, dst);
  dst = ChunkListEmit(mux->xmp_, dst);
  dst = ChunkListEmit(mux->unknown_, dst);
  assert(dst == data + size);

  // Validate mux.
  err = MuxValidate(mux);
  if (err != WEBP_MUX_OK) {
    WebPSafeFree(data);
    data = NULL;
    size = 0;
  }

  // Finalize data.
  assembled_data->bytes = data;
  assembled_data->size = size;

  return err;
}