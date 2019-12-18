#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int stride; int /*<<< orphan*/ * rgba; } ;
struct TYPE_6__ {TYPE_1__ RGBA; } ;
struct TYPE_7__ {int width; int height; TYPE_2__ u; } ;
typedef  TYPE_3__ WebPDecBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const,int const) ; 
 int const fwrite (int /*<<< orphan*/  const*,int const,int const,int /*<<< orphan*/ *) ; 

int WebPWrite16bAsPGM(FILE* fout, const WebPDecBuffer* const buffer) {
  const uint32_t width = buffer->width;
  const uint32_t height = buffer->height;
  const uint8_t* rgba = buffer->u.RGBA.rgba;
  const int stride = buffer->u.RGBA.stride;
  const uint32_t bytes_per_px = 2;
  uint32_t y;

  if (fout == NULL || buffer == NULL || rgba == NULL) return 0;

  fprintf(fout, "P5\n%u %u\n255\n", width * bytes_per_px, height);
  for (y = 0; y < height; ++y) {
    if (fwrite(rgba, width, bytes_per_px, fout) != bytes_per_px) {
      return 0;
    }
    rgba += stride;
  }
  return 1;
}