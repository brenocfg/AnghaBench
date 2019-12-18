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
struct TYPE_8__ {int stride; size_t size; int /*<<< orphan*/ * rgba; } ;
struct TYPE_9__ {TYPE_1__ RGBA; } ;
struct TYPE_11__ {int is_external_memory; TYPE_2__ u; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_4__ WebPDecBuffer ;
typedef  int /*<<< orphan*/  WEBP_CSP_MODE ;

/* Variables and functions */
 scalar_t__ DecodeInto (int /*<<< orphan*/  const* const,size_t,TYPE_3__*) ; 
 scalar_t__ VP8_STATUS_OK ; 
 int /*<<< orphan*/  WebPInitDecBuffer (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPResetDecParams (TYPE_3__*) ; 

__attribute__((used)) static uint8_t* DecodeIntoRGBABuffer(WEBP_CSP_MODE colorspace,
                                     const uint8_t* const data,
                                     size_t data_size,
                                     uint8_t* const rgba,
                                     int stride, size_t size) {
  WebPDecParams params;
  WebPDecBuffer buf;
  if (rgba == NULL) {
    return NULL;
  }
  WebPInitDecBuffer(&buf);
  WebPResetDecParams(&params);
  params.output = &buf;
  buf.colorspace    = colorspace;
  buf.u.RGBA.rgba   = rgba;
  buf.u.RGBA.stride = stride;
  buf.u.RGBA.size   = size;
  buf.is_external_memory = 1;
  if (DecodeInto(data, data_size, &params) != VP8_STATUS_OK) {
    return NULL;
  }
  return rgba;
}