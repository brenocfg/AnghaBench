#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ WebPOutputFileFormat ;
struct TYPE_10__ {int scaled_width; int scaled_height; int crop_width; int crop_height; scalar_t__ use_cropping; scalar_t__ use_scaling; } ;
struct TYPE_9__ {int width; int height; } ;
struct TYPE_12__ {int y_stride; int y_size; int a_stride; int a_size; int u_stride; int u_size; int v_stride; int v_size; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * a; int /*<<< orphan*/ * y; } ;
struct TYPE_11__ {int stride; int size; int /*<<< orphan*/ * rgba; } ;
struct TYPE_13__ {TYPE_4__ YUVA; TYPE_3__ RGBA; } ;
struct TYPE_15__ {int is_external_memory; TYPE_5__ u; int /*<<< orphan*/  colorspace; } ;
struct TYPE_14__ {TYPE_2__ options; TYPE_1__ input; TYPE_7__ output; } ;
typedef  TYPE_6__ WebPDecoderConfig ;
typedef  TYPE_7__ WebPDecBuffer ;

/* Variables and functions */
 scalar_t__ BGR ; 
 scalar_t__ RGB ; 
 scalar_t__ RGBA_4444 ; 
 scalar_t__ RGB_565 ; 
 int WebPIsAlphaMode (int /*<<< orphan*/ ) ; 
 scalar_t__ WebPMalloc (int) ; 
 scalar_t__ YUV ; 
 scalar_t__ YUVA ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ rgbA_4444 ; 

__attribute__((used)) static uint8_t* AllocateExternalBuffer(WebPDecoderConfig* config,
                                       WebPOutputFileFormat format,
                                       int use_external_memory) {
  uint8_t* external_buffer = NULL;
  WebPDecBuffer* const output_buffer = &config->output;
  int w = config->input.width;
  int h = config->input.height;
  if (config->options.use_scaling) {
    w = config->options.scaled_width;
    h = config->options.scaled_height;
  } else if (config->options.use_cropping) {
    w = config->options.crop_width;
    h = config->options.crop_height;
  }
  if (format >= RGB && format <= rgbA_4444) {
    const int bpp = (format == RGB || format == BGR) ? 3
                  : (format == RGBA_4444 || format == rgbA_4444 ||
                     format == RGB_565) ? 2
                  : 4;
    uint32_t stride = bpp * w + 7;   // <- just for exercising
    external_buffer = (uint8_t*)WebPMalloc(stride * h);
    if (external_buffer == NULL) return NULL;
    output_buffer->u.RGBA.stride = stride;
    output_buffer->u.RGBA.size = stride * h;
    output_buffer->u.RGBA.rgba = external_buffer;
  } else {    // YUV and YUVA
    const int has_alpha = WebPIsAlphaMode(output_buffer->colorspace);
    uint8_t* tmp;
    uint32_t stride = w + 3;
    uint32_t uv_stride = (w + 1) / 2 + 13;
    uint32_t total_size = stride * h * (has_alpha ? 2 : 1)
                        + 2 * uv_stride * (h + 1) / 2;
    assert(format >= YUV && format <= YUVA);
    external_buffer = (uint8_t*)WebPMalloc(total_size);
    if (external_buffer == NULL) return NULL;
    tmp = external_buffer;
    output_buffer->u.YUVA.y = tmp;
    output_buffer->u.YUVA.y_stride = stride;
    output_buffer->u.YUVA.y_size = stride * h;
    tmp += output_buffer->u.YUVA.y_size;
    if (has_alpha) {
      output_buffer->u.YUVA.a = tmp;
      output_buffer->u.YUVA.a_stride = stride;
      output_buffer->u.YUVA.a_size = stride * h;
      tmp += output_buffer->u.YUVA.a_size;
    } else {
      output_buffer->u.YUVA.a = NULL;
      output_buffer->u.YUVA.a_stride = 0;
    }
    output_buffer->u.YUVA.u = tmp;
    output_buffer->u.YUVA.u_stride = uv_stride;
    output_buffer->u.YUVA.u_size = uv_stride * (h + 1) / 2;
    tmp += output_buffer->u.YUVA.u_size;

    output_buffer->u.YUVA.v = tmp;
    output_buffer->u.YUVA.v_stride = uv_stride;
    output_buffer->u.YUVA.v_size = uv_stride * (h + 1) / 2;
    tmp += output_buffer->u.YUVA.v_size;
    assert(tmp <= external_buffer + total_size);
  }
  output_buffer->is_external_memory = use_external_memory;
  return external_buffer;
}