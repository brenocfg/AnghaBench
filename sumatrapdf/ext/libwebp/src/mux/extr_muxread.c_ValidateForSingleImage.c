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
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_3__ {int /*<<< orphan*/  images_; } ;
typedef  TYPE_1__ WebPMux ;

/* Variables and functions */
 int MuxImageCount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_CHUNK_ANMF ; 
 int /*<<< orphan*/  WEBP_CHUNK_IMAGE ; 
 int /*<<< orphan*/  WEBP_MUX_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 

__attribute__((used)) static WebPMuxError ValidateForSingleImage(const WebPMux* const mux) {
  const int num_images = MuxImageCount(mux->images_, WEBP_CHUNK_IMAGE);
  const int num_frames = MuxImageCount(mux->images_, WEBP_CHUNK_ANMF);

  if (num_images == 0) {
    // No images in mux.
    return WEBP_MUX_NOT_FOUND;
  } else if (num_images == 1 && num_frames == 0) {
    // Valid case (single image).
    return WEBP_MUX_OK;
  } else {
    // Frame case OR an invalid mux.
    return WEBP_MUX_INVALID_ARGUMENT;
  }
}