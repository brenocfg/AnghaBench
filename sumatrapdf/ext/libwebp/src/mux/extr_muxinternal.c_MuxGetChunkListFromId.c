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
struct TYPE_3__ {int /*<<< orphan*/  unknown_; int /*<<< orphan*/  xmp_; int /*<<< orphan*/  exif_; int /*<<< orphan*/  anim_; int /*<<< orphan*/  iccp_; int /*<<< orphan*/  vp8x_; } ;
typedef  TYPE_1__ WebPMux ;
typedef  int WebPChunkId ;
typedef  int /*<<< orphan*/  WebPChunk ;

/* Variables and functions */
#define  WEBP_CHUNK_ANIM 132 
#define  WEBP_CHUNK_EXIF 131 
#define  WEBP_CHUNK_ICCP 130 
#define  WEBP_CHUNK_VP8X 129 
#define  WEBP_CHUNK_XMP 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

WebPChunk** MuxGetChunkListFromId(const WebPMux* mux, WebPChunkId id) {
  assert(mux != NULL);
  switch (id) {
    case WEBP_CHUNK_VP8X:    return (WebPChunk**)&mux->vp8x_;
    case WEBP_CHUNK_ICCP:    return (WebPChunk**)&mux->iccp_;
    case WEBP_CHUNK_ANIM:    return (WebPChunk**)&mux->anim_;
    case WEBP_CHUNK_EXIF:    return (WebPChunk**)&mux->exif_;
    case WEBP_CHUNK_XMP:     return (WebPChunk**)&mux->xmp_;
    default:                 return (WebPChunk**)&mux->unknown_;
  }
}