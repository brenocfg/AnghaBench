#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int use_argb; int width; int height; int /*<<< orphan*/  uv_stride; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y_stride; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  ImgIoUtilCopyPlane (int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  WebPPictureAlloc (TYPE_1__* const) ; 
 int WebPPictureYUVAToARGB (TYPE_1__* const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int ReadYUV(const uint8_t* const data, size_t data_size,
                   WebPPicture* const pic) {
  const int use_argb = pic->use_argb;
  const int uv_width = (pic->width + 1) / 2;
  const int uv_height = (pic->height + 1) / 2;
  const int y_plane_size = pic->width * pic->height;
  const int uv_plane_size = uv_width * uv_height;
  const size_t expected_data_size = y_plane_size + 2 * uv_plane_size;

  if (data_size != expected_data_size) {
    fprintf(stderr,
            "input data doesn't have the expected size (%d instead of %d)\n",
            (int)data_size, (int)expected_data_size);
    return 0;
  }

  pic->use_argb = 0;
  if (!WebPPictureAlloc(pic)) return 0;
  ImgIoUtilCopyPlane(data, pic->width, pic->y, pic->y_stride,
                     pic->width, pic->height);
  ImgIoUtilCopyPlane(data + y_plane_size, uv_width,
                     pic->u, pic->uv_stride, uv_width, uv_height);
  ImgIoUtilCopyPlane(data + y_plane_size + uv_plane_size, uv_width,
                     pic->v, pic->uv_stride, uv_width, uv_height);
  return use_argb ? WebPPictureYUVAToARGB(pic) : 1;
}