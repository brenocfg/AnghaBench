#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
struct Metadata {int dummy; } ;
struct TYPE_7__ {size_t width; int height; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_8__ {size_t data_size; int type; int width; int height; size_t bytes_per_px; int depth; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ PNMInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ImgIoUtilCheckSizeArgumentsOverflow (size_t,size_t) ; 
 size_t ReadHeader (TYPE_2__*) ; 
 int WEBP_MAX_DIMENSION ; 
 int WebPPictureImportRGB (TYPE_1__* const,int /*<<< orphan*/ *,int) ; 
 int WebPPictureImportRGBA (TYPE_1__* const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int) ; 
 int /*<<< orphan*/  stderr ; 

int ReadPNM(const uint8_t* const data, size_t data_size,
            WebPPicture* const pic, int keep_alpha,
            struct Metadata* const metadata) {
  int ok = 0;
  int i, j;
  uint64_t stride, pixel_bytes;
  uint8_t* rgb = NULL, *tmp_rgb;
  size_t offset;
  PNMInfo info;

  info.data = data;
  info.data_size = data_size;
  offset = ReadHeader(&info);
  if (offset == 0) {
    fprintf(stderr, "Error parsing PNM header.\n");
    goto End;
  }

  if (info.type < 5 || info.type > 7) {
    fprintf(stderr, "Unsupported P%d PNM format.\n", info.type);
    goto End;
  }

  // Some basic validations.
  if (pic == NULL) goto End;
  if (info.width > WEBP_MAX_DIMENSION || info.height > WEBP_MAX_DIMENSION) {
    fprintf(stderr, "Invalid %dx%d dimension for PNM\n",
                    info.width, info.height);
    goto End;
  }

  pixel_bytes = (uint64_t)info.width * info.height * info.bytes_per_px;
  if (data_size < offset + pixel_bytes) {
    fprintf(stderr, "Truncated PNM file (P%d).\n", info.type);
    goto End;
  }
  stride =
      (uint64_t)(info.bytes_per_px < 3 ? 3 : info.bytes_per_px) * info.width;
  if (stride != (size_t)stride ||
      !ImgIoUtilCheckSizeArgumentsOverflow(stride, info.height)) {
    goto End;
  }

  rgb = (uint8_t*)malloc((size_t)stride * info.height);
  if (rgb == NULL) goto End;

  // Convert input
  tmp_rgb = rgb;
  for (j = 0; j < info.height; ++j) {
    assert(offset + info.bytes_per_px * info.width <= data_size);
    if (info.depth == 1) {
      // convert grayscale -> RGB
      for (i = 0; i < info.width; ++i) {
        const uint8_t v = data[offset + i];
        tmp_rgb[3 * i + 0] = tmp_rgb[3 * i + 1] = tmp_rgb[3 * i + 2] = v;
      }
    } else if (info.depth == 3) {   // RGB
      memcpy(tmp_rgb, data + offset, 3 * info.width * sizeof(*data));
    } else if (info.depth == 4) {   // RGBA
      memcpy(tmp_rgb, data + offset, 4 * info.width * sizeof(*data));
    }
    offset += info.bytes_per_px * info.width;
    tmp_rgb += stride;
  }

  // WebP conversion.
  pic->width = info.width;
  pic->height = info.height;
  ok = (info.depth == 4) ? WebPPictureImportRGBA(pic, rgb, (int)stride)
                         : WebPPictureImportRGB(pic, rgb, (int)stride);
  if (!ok) goto End;

  ok = 1;
 End:
  free((void*)rgb);

  (void)metadata;
  (void)keep_alpha;
  return ok;
}