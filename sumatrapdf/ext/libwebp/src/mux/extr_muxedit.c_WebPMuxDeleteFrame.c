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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_3__ {int /*<<< orphan*/  images_; } ;
typedef  TYPE_1__ WebPMux ;

/* Variables and functions */
 int /*<<< orphan*/  MuxImageDeleteNth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_MUX_INVALID_ARGUMENT ; 

WebPMuxError WebPMuxDeleteFrame(WebPMux* mux, uint32_t nth) {
  if (mux == NULL) return WEBP_MUX_INVALID_ARGUMENT;
  return MuxImageDeleteNth(&mux->images_, nth);
}