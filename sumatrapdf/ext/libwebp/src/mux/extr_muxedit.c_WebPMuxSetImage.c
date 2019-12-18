#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_6__ {int /*<<< orphan*/ * images_; } ;
typedef  TYPE_1__ WebPMux ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_2__ WebPData ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAllImages (int /*<<< orphan*/ **) ; 
 scalar_t__ MAX_CHUNK_PAYLOAD ; 
 int /*<<< orphan*/  MuxImageInit (int /*<<< orphan*/ *) ; 
 scalar_t__ MuxImagePush (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MuxImageRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ SetAlphaAndImageChunks (TYPE_2__ const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_OK ; 

WebPMuxError WebPMuxSetImage(WebPMux* mux, const WebPData* bitstream,
                             int copy_data) {
  WebPMuxImage wpi;
  WebPMuxError err;

  // Sanity checks.
  if (mux == NULL || bitstream == NULL || bitstream->bytes == NULL ||
      bitstream->size > MAX_CHUNK_PAYLOAD) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  if (mux->images_ != NULL) {
    // Only one 'simple image' can be added in mux. So, remove present images.
    DeleteAllImages(&mux->images_);
  }

  MuxImageInit(&wpi);
  err = SetAlphaAndImageChunks(bitstream, copy_data, &wpi);
  if (err != WEBP_MUX_OK) goto Err;

  // Add this WebPMuxImage to mux.
  err = MuxImagePush(&wpi, &mux->images_);
  if (err != WEBP_MUX_OK) goto Err;

  // All is well.
  return WEBP_MUX_OK;

 Err:  // Something bad happened.
  MuxImageRelease(&wpi);
  return err;
}