#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/ * header_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  int /*<<< orphan*/  WebPMuxFrameInfo ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_9__ {int /*<<< orphan*/  images_; } ;
typedef  TYPE_2__ WebPMux ;

/* Variables and functions */
 scalar_t__ MuxGetFrameInternal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MuxGetImageInternal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MuxImageGetNth (TYPE_1__ const**,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_OK ; 

WebPMuxError WebPMuxGetFrame(
    const WebPMux* mux, uint32_t nth, WebPMuxFrameInfo* frame) {
  WebPMuxError err;
  WebPMuxImage* wpi;

  // Sanity checks.
  if (mux == NULL || frame == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  // Get the nth WebPMuxImage.
  err = MuxImageGetNth((const WebPMuxImage**)&mux->images_, nth, &wpi);
  if (err != WEBP_MUX_OK) return err;

  // Get frame info.
  if (wpi->header_ == NULL) {
    return MuxGetImageInternal(wpi, frame);
  } else {
    return MuxGetFrameInternal(wpi, frame);
  }
}