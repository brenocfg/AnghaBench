#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  int WebPFeatureFlags ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  size_t CHUNK_INDEX ;

/* Variables and functions */
 scalar_t__ IsNotCompatible (int,int) ; 
 int NO_FLAG ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ const WEBP_MUX_OK ; 
 scalar_t__ WebPMuxNumChunks (int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* kChunks ; 

__attribute__((used)) static WebPMuxError ValidateChunk(const WebPMux* const mux, CHUNK_INDEX idx,
                                  WebPFeatureFlags feature,
                                  uint32_t vp8x_flags,
                                  int max, int* num) {
  const WebPMuxError err =
      WebPMuxNumChunks(mux, kChunks[idx].id, num);
  if (err != WEBP_MUX_OK) return err;
  if (max > -1 && *num > max) return WEBP_MUX_INVALID_ARGUMENT;
  if (feature != NO_FLAG && IsNotCompatible(vp8x_flags & feature, *num)) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  return WEBP_MUX_OK;
}