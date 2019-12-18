#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {TYPE_5__* output; } ;
typedef  TYPE_4__ WebPDecParams ;
struct TYPE_13__ {int /*<<< orphan*/ * y; } ;
struct TYPE_12__ {int /*<<< orphan*/ * rgba; } ;
struct TYPE_14__ {TYPE_2__ YUVA; TYPE_1__ RGBA; } ;
struct TYPE_16__ {int width; int height; TYPE_3__ u; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_5__ WebPDecBuffer ;
typedef  int /*<<< orphan*/  WEBP_CSP_MODE ;

/* Variables and functions */
 scalar_t__ DecodeInto (int /*<<< orphan*/  const* const,size_t,TYPE_4__*) ; 
 scalar_t__ VP8_STATUS_OK ; 
 int /*<<< orphan*/  WebPCopyDecBuffer (TYPE_5__*,TYPE_5__* const) ; 
 int /*<<< orphan*/  WebPGetInfo (int /*<<< orphan*/  const* const,size_t,int*,int*) ; 
 int /*<<< orphan*/  WebPInitDecBuffer (TYPE_5__*) ; 
 scalar_t__ WebPIsRGBMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPResetDecParams (TYPE_4__*) ; 

__attribute__((used)) static uint8_t* Decode(WEBP_CSP_MODE mode, const uint8_t* const data,
                       size_t data_size, int* const width, int* const height,
                       WebPDecBuffer* const keep_info) {
  WebPDecParams params;
  WebPDecBuffer output;

  WebPInitDecBuffer(&output);
  WebPResetDecParams(&params);
  params.output = &output;
  output.colorspace = mode;

  // Retrieve (and report back) the required dimensions from bitstream.
  if (!WebPGetInfo(data, data_size, &output.width, &output.height)) {
    return NULL;
  }
  if (width != NULL) *width = output.width;
  if (height != NULL) *height = output.height;

  // Decode
  if (DecodeInto(data, data_size, &params) != VP8_STATUS_OK) {
    return NULL;
  }
  if (keep_info != NULL) {    // keep track of the side-info
    WebPCopyDecBuffer(&output, keep_info);
  }
  // return decoded samples (don't clear 'output'!)
  return WebPIsRGBMode(mode) ? output.u.RGBA.rgba : output.u.YUVA.y;
}