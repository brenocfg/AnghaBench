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
 size_t const fwrite (int /*<<< orphan*/  const*,int const,size_t const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int WritePPMPAM(FILE* fout, const WebPDecBuffer* const buffer,
                       int alpha) {
  if (fout == NULL || buffer == NULL) {
    return 0;
  } else {
    const uint32_t width = buffer->width;
    const uint32_t height = buffer->height;
    const uint8_t* row = buffer->u.RGBA.rgba;
    const int stride = buffer->u.RGBA.stride;
    const size_t bytes_per_px = alpha ? 4 : 3;
    uint32_t y;

    if (row == NULL) return 0;

    if (alpha) {
      fprintf(fout, "P7\nWIDTH %u\nHEIGHT %u\nDEPTH 4\nMAXVAL 255\n"
                    "TUPLTYPE RGB_ALPHA\nENDHDR\n", width, height);
    } else {
      fprintf(fout, "P6\n%u %u\n255\n", width, height);
    }
    for (y = 0; y < height; ++y) {
      if (fwrite(row, width, bytes_per_px, fout) != bytes_per_px) {
        return 0;
      }
      row += stride;
    }
  }
  return 1;
}