#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_4__ {int /*<<< orphan*/  xmp_; int /*<<< orphan*/  exif_; int /*<<< orphan*/  anim_; int /*<<< orphan*/  iccp_; int /*<<< orphan*/  vp8x_; } ;
typedef  TYPE_1__ WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  size_t CHUNK_INDEX ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_ANIM ; 
 int /*<<< orphan*/  IDX_EXIF ; 
 int /*<<< orphan*/  IDX_ICCP ; 
 size_t IDX_UNKNOWN ; 
 int /*<<< orphan*/  IDX_VP8X ; 
 int /*<<< orphan*/  IDX_XMP ; 
 int /*<<< orphan*/  IsWPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ID_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  WebPDataInit (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* kChunks ; 

__attribute__((used)) static WebPMuxError MuxGet(const WebPMux* const mux, CHUNK_INDEX idx,
                           uint32_t nth, WebPData* const data) {
  assert(mux != NULL);
  assert(!IsWPI(kChunks[idx].id));
  WebPDataInit(data);

  SWITCH_ID_LIST(IDX_VP8X, mux->vp8x_);
  SWITCH_ID_LIST(IDX_ICCP, mux->iccp_);
  SWITCH_ID_LIST(IDX_ANIM, mux->anim_);
  SWITCH_ID_LIST(IDX_EXIF, mux->exif_);
  SWITCH_ID_LIST(IDX_XMP, mux->xmp_);
  assert(idx != IDX_UNKNOWN);
  return WEBP_MUX_NOT_FOUND;
}