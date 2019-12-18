#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ WebPHeaderStructure ;
typedef  scalar_t__ VP8StatusCode ;

/* Variables and functions */
 scalar_t__ ParseHeadersInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,TYPE_1__* const) ; 
 scalar_t__ volatile VP8_STATUS_NOT_ENOUGH_DATA ; 
 scalar_t__ volatile VP8_STATUS_OK ; 
 scalar_t__ VP8_STATUS_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

VP8StatusCode WebPParseHeaders(WebPHeaderStructure* const headers) {
  // status is marked volatile as a workaround for a clang-3.8 (aarch64) bug
  volatile VP8StatusCode status;
  int has_animation = 0;
  assert(headers != NULL);
  // fill out headers, ignore width/height/has_alpha.
  status = ParseHeadersInternal(headers->data, headers->data_size,
                                NULL, NULL, NULL, &has_animation,
                                NULL, headers);
  if (status == VP8_STATUS_OK || status == VP8_STATUS_NOT_ENOUGH_DATA) {
    // The WebPDemux API + libwebp can be used to decode individual
    // uncomposited frames or the WebPAnimDecoder can be used to fully
    // reconstruct them (see webp/demux.h).
    if (has_animation) {
      status = VP8_STATUS_UNSUPPORTED_FEATURE;
    }
  }
  return status;
}