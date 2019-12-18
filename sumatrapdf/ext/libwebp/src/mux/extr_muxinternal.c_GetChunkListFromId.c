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
struct TYPE_3__ {int /*<<< orphan*/  img_; int /*<<< orphan*/  alpha_; int /*<<< orphan*/  header_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  int WebPChunkId ;
typedef  int /*<<< orphan*/  WebPChunk ;

/* Variables and functions */
#define  WEBP_CHUNK_ALPHA 130 
#define  WEBP_CHUNK_ANMF 129 
#define  WEBP_CHUNK_IMAGE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WebPChunk** GetChunkListFromId(const WebPMuxImage* const wpi,
                                      WebPChunkId id) {
  assert(wpi != NULL);
  switch (id) {
    case WEBP_CHUNK_ANMF:  return (WebPChunk**)&wpi->header_;
    case WEBP_CHUNK_ALPHA: return (WebPChunk**)&wpi->alpha_;
    case WEBP_CHUNK_IMAGE: return (WebPChunk**)&wpi->img_;
    default: return NULL;
  }
}