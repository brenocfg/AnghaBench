#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int width; int height; TYPE_3__* const extra_info; TYPE_3__* stats; int /*<<< orphan*/ * argb; } ;
typedef  TYPE_1__ WebPPicture ;
typedef  scalar_t__ WebPEncodingError ;
struct TYPE_22__ {scalar_t__ image_hint; } ;
typedef  TYPE_2__ WebPConfig ;
struct TYPE_23__ {float* PSNR; int coded_size; int lossless_size; } ;
typedef  TYPE_3__ WebPAuxStats ;
struct TYPE_24__ {scalar_t__ error_; } ;
typedef  TYPE_4__ VP8LBitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LBitWriterInit (TYPE_4__*,int) ; 
 int /*<<< orphan*/  VP8LBitWriterWipeOut (TYPE_4__*) ; 
 scalar_t__ VP8LEncodeStream (TYPE_2__ const* const,TYPE_1__ const* const,TYPE_4__*,int) ; 
 scalar_t__ VP8_ENC_ERROR_NULL_PARAMETER ; 
 scalar_t__ VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VP8_ENC_ERROR_USER_ABORT ; 
 scalar_t__ VP8_ENC_OK ; 
 scalar_t__ WEBP_HINT_GRAPH ; 
 int /*<<< orphan*/  WebPEncodingSetError (TYPE_1__ const* const,scalar_t__) ; 
 int WebPPictureHasTransparency (TYPE_1__ const* const) ; 
 int /*<<< orphan*/  WebPReportProgress (TYPE_1__ const* const,int,int*) ; 
 scalar_t__ WriteImage (TYPE_1__ const* const,TYPE_4__*,size_t*) ; 
 int /*<<< orphan*/  WriteImageSize (TYPE_1__ const* const,TYPE_4__*) ; 
 int /*<<< orphan*/  WriteRealAlphaAndVersion (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__* const,int /*<<< orphan*/ ,int const) ; 

int VP8LEncodeImage(const WebPConfig* const config,
                    const WebPPicture* const picture) {
  int width, height;
  int has_alpha;
  size_t coded_size;
  int percent = 0;
  int initial_size;
  WebPEncodingError err = VP8_ENC_OK;
  VP8LBitWriter bw;

  if (picture == NULL) return 0;

  if (config == NULL || picture->argb == NULL) {
    err = VP8_ENC_ERROR_NULL_PARAMETER;
    WebPEncodingSetError(picture, err);
    return 0;
  }

  width = picture->width;
  height = picture->height;
  // Initialize BitWriter with size corresponding to 16 bpp to photo images and
  // 8 bpp for graphical images.
  initial_size = (config->image_hint == WEBP_HINT_GRAPH) ?
      width * height : width * height * 2;
  if (!VP8LBitWriterInit(&bw, initial_size)) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  if (!WebPReportProgress(picture, 1, &percent)) {
 UserAbort:
    err = VP8_ENC_ERROR_USER_ABORT;
    goto Error;
  }
  // Reset stats (for pure lossless coding)
  if (picture->stats != NULL) {
    WebPAuxStats* const stats = picture->stats;
    memset(stats, 0, sizeof(*stats));
    stats->PSNR[0] = 99.f;
    stats->PSNR[1] = 99.f;
    stats->PSNR[2] = 99.f;
    stats->PSNR[3] = 99.f;
    stats->PSNR[4] = 99.f;
  }

  // Write image size.
  if (!WriteImageSize(picture, &bw)) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  has_alpha = WebPPictureHasTransparency(picture);
  // Write the non-trivial Alpha flag and lossless version.
  if (!WriteRealAlphaAndVersion(&bw, has_alpha)) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  if (!WebPReportProgress(picture, 5, &percent)) goto UserAbort;

  // Encode main image stream.
  err = VP8LEncodeStream(config, picture, &bw, 1 /*use_cache*/);
  if (err != VP8_ENC_OK) goto Error;

  if (!WebPReportProgress(picture, 90, &percent)) goto UserAbort;

  // Finish the RIFF chunk.
  err = WriteImage(picture, &bw, &coded_size);
  if (err != VP8_ENC_OK) goto Error;

  if (!WebPReportProgress(picture, 100, &percent)) goto UserAbort;

#if !defined(WEBP_DISABLE_STATS)
  // Save size.
  if (picture->stats != NULL) {
    picture->stats->coded_size += (int)coded_size;
    picture->stats->lossless_size = (int)coded_size;
  }
#endif

  if (picture->extra_info != NULL) {
    const int mb_w = (width + 15) >> 4;
    const int mb_h = (height + 15) >> 4;
    memset(picture->extra_info, 0, mb_w * mb_h * sizeof(*picture->extra_info));
  }

 Error:
  if (bw.error_) err = VP8_ENC_ERROR_OUT_OF_MEMORY;
  VP8LBitWriterWipeOut(&bw);
  if (err != VP8_ENC_OK) {
    WebPEncodingSetError(picture, err);
    return 0;
  }
  return 1;
}