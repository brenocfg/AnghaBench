#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ WebPOutputFileFormat ;
typedef  int /*<<< orphan*/  WebPDecBuffer ;
typedef  int /*<<< orphan*/  W_CHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ALPHA_PLANE_ONLY ; 
 scalar_t__ ARGB ; 
 scalar_t__ Argb ; 
 scalar_t__ BGR ; 
 scalar_t__ BGRA ; 
 scalar_t__ BMP ; 
 int /*<<< orphan*/ * ImgIoUtilSetBinaryMode (int /*<<< orphan*/ *) ; 
 scalar_t__ PAM ; 
 scalar_t__ PGM ; 
 scalar_t__ PNG ; 
 scalar_t__ PPM ; 
 scalar_t__ RAW_YUV ; 
 scalar_t__ RGB ; 
 scalar_t__ RGBA ; 
 scalar_t__ RGBA_4444 ; 
 scalar_t__ RGB_565 ; 
 scalar_t__ TIFF ; 
 int /*<<< orphan*/ * WFOPEN (char const* const,char*) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WSTRCMP (char const* const,char*) ; 
 int WebPWrite16bAsPGM (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWriteAlphaPlane (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWriteBMP (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWritePAM (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWritePGM (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWritePNG (char const* const,int const,...) ; 
 int WebPWritePPM (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWriteTIFF (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 int WebPWriteYUV (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const) ; 
 scalar_t__ YUV ; 
 scalar_t__ YUVA ; 
 scalar_t__ bgrA ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ rgbA ; 
 scalar_t__ rgbA_4444 ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

int WebPSaveImage(const WebPDecBuffer* const buffer,
                  WebPOutputFileFormat format,
                  const char* const out_file_name) {
  FILE* fout = NULL;
  int needs_open_file = 1;
  const int use_stdout =
      (out_file_name != NULL) && !WSTRCMP(out_file_name, "-");
  int ok = 1;

  if (buffer == NULL || out_file_name == NULL) return 0;

#ifdef HAVE_WINCODEC_H
  needs_open_file = (format != PNG);
#endif

  if (needs_open_file) {
    fout = use_stdout ? ImgIoUtilSetBinaryMode(stdout)
                      : WFOPEN(out_file_name, "wb");
    if (fout == NULL) {
      WFPRINTF(stderr, "Error opening output file %s\n",
               (const W_CHAR*)out_file_name);
      return 0;
    }
  }

  if (format == PNG ||
      format == RGBA || format == BGRA || format == ARGB ||
      format == rgbA || format == bgrA || format == Argb) {
#ifdef HAVE_WINCODEC_H
    ok &= WebPWritePNG(out_file_name, use_stdout, buffer);
#else
    ok &= WebPWritePNG(fout, buffer);
#endif
  } else if (format == PAM) {
    ok &= WebPWritePAM(fout, buffer);
  } else if (format == PPM || format == RGB || format == BGR) {
    ok &= WebPWritePPM(fout, buffer);
  } else if (format == RGBA_4444 || format == RGB_565 || format == rgbA_4444) {
    ok &= WebPWrite16bAsPGM(fout, buffer);
  } else if (format == BMP) {
    ok &= WebPWriteBMP(fout, buffer);
  } else if (format == TIFF) {
    ok &= WebPWriteTIFF(fout, buffer);
  } else if (format == RAW_YUV) {
    ok &= WebPWriteYUV(fout, buffer);
  } else if (format == PGM || format == YUV || format == YUVA) {
    ok &= WebPWritePGM(fout, buffer);
  } else if (format == ALPHA_PLANE_ONLY) {
    ok &= WebPWriteAlphaPlane(fout, buffer);
  }
  if (fout != NULL && fout != stdout) {
    fclose(fout);
  }
  return ok;
}