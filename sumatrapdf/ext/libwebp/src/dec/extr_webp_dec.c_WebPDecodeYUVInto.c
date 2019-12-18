#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {TYPE_4__* output; } ;
typedef  TYPE_3__ WebPDecParams ;
struct TYPE_8__ {int y_stride; size_t y_size; int u_stride; size_t u_size; int v_stride; size_t v_size; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; } ;
struct TYPE_9__ {TYPE_1__ YUVA; } ;
struct TYPE_11__ {int is_external_memory; TYPE_2__ u; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_4__ WebPDecBuffer ;

/* Variables and functions */
 scalar_t__ DecodeInto (int /*<<< orphan*/  const*,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  MODE_YUV ; 
 scalar_t__ VP8_STATUS_OK ; 
 int /*<<< orphan*/  WebPInitDecBuffer (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPResetDecParams (TYPE_3__*) ; 

uint8_t* WebPDecodeYUVInto(const uint8_t* data, size_t data_size,
                           uint8_t* luma, size_t luma_size, int luma_stride,
                           uint8_t* u, size_t u_size, int u_stride,
                           uint8_t* v, size_t v_size, int v_stride) {
  WebPDecParams params;
  WebPDecBuffer output;
  if (luma == NULL) return NULL;
  WebPInitDecBuffer(&output);
  WebPResetDecParams(&params);
  params.output = &output;
  output.colorspace      = MODE_YUV;
  output.u.YUVA.y        = luma;
  output.u.YUVA.y_stride = luma_stride;
  output.u.YUVA.y_size   = luma_size;
  output.u.YUVA.u        = u;
  output.u.YUVA.u_stride = u_stride;
  output.u.YUVA.u_size   = u_size;
  output.u.YUVA.v        = v;
  output.u.YUVA.v_stride = v_stride;
  output.u.YUVA.v_size   = v_size;
  output.is_external_memory = 1;
  if (DecodeInto(data, data_size, &params) != VP8_STATUS_OK) {
    return NULL;
  }
  return luma;
}