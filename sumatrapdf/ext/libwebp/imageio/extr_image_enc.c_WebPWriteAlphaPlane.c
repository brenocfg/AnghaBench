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
struct TYPE_5__ {int a_stride; int /*<<< orphan*/ * a; } ;
struct TYPE_6__ {TYPE_1__ YUVA; } ;
struct TYPE_7__ {int width; int height; TYPE_2__ u; } ;
typedef  TYPE_3__ WebPDecBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const,int const) ; 
 int fwrite (int /*<<< orphan*/  const*,int const,int,int /*<<< orphan*/ *) ; 

int WebPWriteAlphaPlane(FILE* fout, const WebPDecBuffer* const buffer) {
  if (fout == NULL || buffer == NULL) {
    return 0;
  } else {
    const uint32_t width = buffer->width;
    const uint32_t height = buffer->height;
    const uint8_t* a = buffer->u.YUVA.a;
    const int a_stride = buffer->u.YUVA.a_stride;
    uint32_t y;

    if (a == NULL) return 0;

    fprintf(fout, "P5\n%u %u\n255\n", width, height);
    for (y = 0; y < height; ++y) {
      if (fwrite(a, width, 1, fout) != 1) return 0;
      a += a_stride;
    }
    return 1;
  }
}