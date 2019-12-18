#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;
struct TYPE_10__ {int x_offset; int y_offset; scalar_t__ dispose_method; scalar_t__ blend_method; int duration; TYPE_9__ bitstream; } ;
typedef  TYPE_1__ WebPMuxFrameInfo ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_11__ {int bgcolor; int loop_count; } ;
typedef  TYPE_2__ WebPMuxAnimParams ;
typedef  int /*<<< orphan*/  WebPMux ;
struct TYPE_12__ {scalar_t__ size; } ;
typedef  TYPE_3__ WebPData ;
typedef  int /*<<< orphan*/  WebPChunkId ;
struct TYPE_13__ {int width; int height; int format; scalar_t__ has_alpha; } ;
typedef  TYPE_4__ WebPBitstreamFeatures ;
typedef  scalar_t__ VP8StatusCode ;

/* Variables and functions */
 int ALPHA_FLAG ; 
 int ANIMATION_FLAG ; 
 int EXIF_FLAG ; 
 int ICCP_FLAG ; 
 int /*<<< orphan*/  RETURN_IF_ERROR (char*) ; 
 int /*<<< orphan*/  RETURN_IF_ERROR3 (char*,char const* const,int) ; 
 scalar_t__ const VP8_STATUS_OK ; 
 int /*<<< orphan*/  WEBP_CHUNK_ANMF ; 
 scalar_t__ WEBP_MUX_BLEND ; 
 scalar_t__ WEBP_MUX_DISPOSE_NONE ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (TYPE_9__*) ; 
 scalar_t__ WebPGetFeatures (int /*<<< orphan*/ ,scalar_t__,TYPE_4__*) ; 
 scalar_t__ WebPMuxGetAnimationParams (int /*<<< orphan*/  const*,TYPE_2__*) ; 
 scalar_t__ WebPMuxGetCanvasSize (int /*<<< orphan*/  const*,int*,int*) ; 
 scalar_t__ WebPMuxGetChunk (int /*<<< orphan*/  const*,char*,TYPE_3__*) ; 
 scalar_t__ WebPMuxGetFeatures (int /*<<< orphan*/  const*,int*) ; 
 scalar_t__ WebPMuxGetFrame (int /*<<< orphan*/  const*,int,TYPE_1__*) ; 
 scalar_t__ WebPMuxNumChunks (int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int*) ; 
 int XMP_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static WebPMuxError DisplayInfo(const WebPMux* mux) {
  int width, height;
  uint32_t flag;

  WebPMuxError err = WebPMuxGetCanvasSize(mux, &width, &height);
  assert(err == WEBP_MUX_OK);  // As WebPMuxCreate() was successful earlier.
  printf("Canvas size: %d x %d\n", width, height);

  err = WebPMuxGetFeatures(mux, &flag);
  RETURN_IF_ERROR("Failed to retrieve features\n");

  if (flag == 0) {
    printf("No features present.\n");
    return err;
  }

  // Print the features present.
  printf("Features present:");
  if (flag & ANIMATION_FLAG) printf(" animation");
  if (flag & ICCP_FLAG)      printf(" ICC profile");
  if (flag & EXIF_FLAG)      printf(" EXIF metadata");
  if (flag & XMP_FLAG)       printf(" XMP metadata");
  if (flag & ALPHA_FLAG)     printf(" transparency");
  printf("\n");

  if (flag & ANIMATION_FLAG) {
    const WebPChunkId id = WEBP_CHUNK_ANMF;
    const char* const type_str = "frame";
    int nFrames;

    WebPMuxAnimParams params;
    err = WebPMuxGetAnimationParams(mux, &params);
    assert(err == WEBP_MUX_OK);
    printf("Background color : 0x%.8X  Loop Count : %d\n",
           params.bgcolor, params.loop_count);

    err = WebPMuxNumChunks(mux, id, &nFrames);
    assert(err == WEBP_MUX_OK);

    printf("Number of %ss: %d\n", type_str, nFrames);
    if (nFrames > 0) {
      int i;
      printf("No.: width height alpha x_offset y_offset ");
      printf("duration   dispose blend ");
      printf("image_size  compression\n");
      for (i = 1; i <= nFrames; i++) {
        WebPMuxFrameInfo frame;
        err = WebPMuxGetFrame(mux, i, &frame);
        if (err == WEBP_MUX_OK) {
          WebPBitstreamFeatures features;
          const VP8StatusCode status = WebPGetFeatures(
              frame.bitstream.bytes, frame.bitstream.size, &features);
          assert(status == VP8_STATUS_OK);  // Checked by WebPMuxCreate().
          (void)status;
          printf("%3d: %5d %5d %5s %8d %8d ", i, features.width,
                 features.height, features.has_alpha ? "yes" : "no",
                 frame.x_offset, frame.y_offset);
          {
            const char* const dispose =
                (frame.dispose_method == WEBP_MUX_DISPOSE_NONE) ? "none"
                                                                : "background";
            const char* const blend =
                (frame.blend_method == WEBP_MUX_BLEND) ? "yes" : "no";
            printf("%8d %10s %5s ", frame.duration, dispose, blend);
          }
          printf("%10d %11s\n", (int)frame.bitstream.size,
                 (features.format == 1) ? "lossy" :
                 (features.format == 2) ? "lossless" :
                                          "undefined");
        }
        WebPDataClear(&frame.bitstream);
        RETURN_IF_ERROR3("Failed to retrieve %s#%d\n", type_str, i);
      }
    }
  }

  if (flag & ICCP_FLAG) {
    WebPData icc_profile;
    err = WebPMuxGetChunk(mux, "ICCP", &icc_profile);
    assert(err == WEBP_MUX_OK);
    printf("Size of the ICC profile data: %d\n", (int)icc_profile.size);
  }

  if (flag & EXIF_FLAG) {
    WebPData exif;
    err = WebPMuxGetChunk(mux, "EXIF", &exif);
    assert(err == WEBP_MUX_OK);
    printf("Size of the EXIF metadata: %d\n", (int)exif.size);
  }

  if (flag & XMP_FLAG) {
    WebPData xmp;
    err = WebPMuxGetChunk(mux, "XMP ", &xmp);
    assert(err == WEBP_MUX_OK);
    printf("Size of the XMP metadata: %d\n", (int)xmp.size);
  }

  if ((flag & ALPHA_FLAG) && !(flag & ANIMATION_FLAG)) {
    WebPMuxFrameInfo image;
    err = WebPMuxGetFrame(mux, 1, &image);
    if (err == WEBP_MUX_OK) {
      printf("Size of the image (with alpha): %d\n", (int)image.bitstream.size);
    }
    WebPDataClear(&image.bitstream);
    RETURN_IF_ERROR("Failed to retrieve the image\n");
  }

  return WEBP_MUX_OK;
}