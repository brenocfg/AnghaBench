#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; } ;
struct TYPE_14__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {TYPE_3__ output; TYPE_11__ input; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ WebPDecoderConfig ;
struct TYPE_16__ {TYPE_3__* output; int /*<<< orphan*/ * options; } ;
typedef  TYPE_2__ WebPDecParams ;
typedef  TYPE_3__ WebPDecBuffer ;
typedef  scalar_t__ VP8StatusCode ;

/* Variables and functions */
 scalar_t__ DecodeInto (int /*<<< orphan*/  const*,size_t,TYPE_2__*) ; 
 scalar_t__ GetFeatures (int /*<<< orphan*/  const*,size_t,TYPE_11__*) ; 
 scalar_t__ VP8_STATUS_BITSTREAM_ERROR ; 
 scalar_t__ VP8_STATUS_INVALID_PARAM ; 
 scalar_t__ VP8_STATUS_NOT_ENOUGH_DATA ; 
 scalar_t__ VP8_STATUS_OK ; 
 scalar_t__ WebPAvoidSlowMemory (TYPE_3__*,TYPE_11__*) ; 
 scalar_t__ WebPCopyDecBufferPixels (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  WebPFreeDecBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  WebPInitDecBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  WebPResetDecParams (TYPE_2__*) ; 

VP8StatusCode WebPDecode(const uint8_t* data, size_t data_size,
                         WebPDecoderConfig* config) {
  WebPDecParams params;
  VP8StatusCode status;

  if (config == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }

  status = GetFeatures(data, data_size, &config->input);
  if (status != VP8_STATUS_OK) {
    if (status == VP8_STATUS_NOT_ENOUGH_DATA) {
      return VP8_STATUS_BITSTREAM_ERROR;  // Not-enough-data treated as error.
    }
    return status;
  }

  WebPResetDecParams(&params);
  params.options = &config->options;
  params.output = &config->output;
  if (WebPAvoidSlowMemory(params.output, &config->input)) {
    // decoding to slow memory: use a temporary in-mem buffer to decode into.
    WebPDecBuffer in_mem_buffer;
    WebPInitDecBuffer(&in_mem_buffer);
    in_mem_buffer.colorspace = config->output.colorspace;
    in_mem_buffer.width = config->input.width;
    in_mem_buffer.height = config->input.height;
    params.output = &in_mem_buffer;
    status = DecodeInto(data, data_size, &params);
    if (status == VP8_STATUS_OK) {  // do the slow-copy
      status = WebPCopyDecBufferPixels(&in_mem_buffer, &config->output);
    }
    WebPFreeDecBuffer(&in_mem_buffer);
  } else {
    status = DecodeInto(data, data_size, &params);
  }

  return status;
}