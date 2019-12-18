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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  a_stride; int /*<<< orphan*/  uv_stride; int /*<<< orphan*/  y_stride; int /*<<< orphan*/ * a; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; } ;
typedef  TYPE_1__ WebPPicture ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * WFOPEN (char const*,char*) ; 
 scalar_t__ WebPPictureHasTransparency (TYPE_1__ const* const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ * const,char*,int const,int const) ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 
 int fwrite (int /*<<< orphan*/  const*,int const,int,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static int DumpPicture(const WebPPicture* const picture, const char* PGM_name) {
  int y;
  const int uv_width = (picture->width + 1) / 2;
  const int uv_height = (picture->height + 1) / 2;
  const int stride = (picture->width + 1) & ~1;
  const uint8_t* src_y = picture->y;
  const uint8_t* src_u = picture->u;
  const uint8_t* src_v = picture->v;
  const uint8_t* src_a = picture->a;
  const int alpha_height =
      WebPPictureHasTransparency(picture) ? picture->height : 0;
  const int height = picture->height + uv_height + alpha_height;
  FILE* const f = WFOPEN(PGM_name, "wb");
  if (f == NULL) return 0;
  fprintf(f, "P5\n%d %d\n255\n", stride, height);
  for (y = 0; y < picture->height; ++y) {
    if (fwrite(src_y, picture->width, 1, f) != 1) return 0;
    if (picture->width & 1) fputc(0, f);  // pad
    src_y += picture->y_stride;
  }
  for (y = 0; y < uv_height; ++y) {
    if (fwrite(src_u, uv_width, 1, f) != 1) return 0;
    if (fwrite(src_v, uv_width, 1, f) != 1) return 0;
    src_u += picture->uv_stride;
    src_v += picture->uv_stride;
  }
  for (y = 0; y < alpha_height; ++y) {
    if (fwrite(src_a, picture->width, 1, f) != 1) return 0;
    if (picture->width & 1) fputc(0, f);  // pad
    src_a += picture->a_stride;
  }
  fclose(f);
  return 1;
}