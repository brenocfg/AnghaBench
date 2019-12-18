#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPPicture ;
typedef  scalar_t__ WebPEncodingError ;
struct TYPE_7__ {int /*<<< orphan*/  profile_; scalar_t__ has_alpha_; int /*<<< orphan*/ * pic_; } ;
typedef  TYPE_1__ VP8Encoder ;

/* Variables and functions */
 scalar_t__ IsVP8XNeeded (TYPE_1__ const* const) ; 
 scalar_t__ PutAlphaChunk (TYPE_1__ const* const) ; 
 scalar_t__ PutRIFFHeader (TYPE_1__ const* const,size_t) ; 
 scalar_t__ PutVP8FrameHeader (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ PutVP8Header (int /*<<< orphan*/ * const,size_t) ; 
 scalar_t__ PutVP8XHeader (TYPE_1__ const* const) ; 
 scalar_t__ VP8_ENC_OK ; 
 int WebPEncodingSetError (int /*<<< orphan*/ * const,scalar_t__) ; 

__attribute__((used)) static int PutWebPHeaders(const VP8Encoder* const enc, size_t size0,
                          size_t vp8_size, size_t riff_size) {
  WebPPicture* const pic = enc->pic_;
  WebPEncodingError err = VP8_ENC_OK;

  // RIFF header.
  err = PutRIFFHeader(enc, riff_size);
  if (err != VP8_ENC_OK) goto Error;

  // VP8X.
  if (IsVP8XNeeded(enc)) {
    err = PutVP8XHeader(enc);
    if (err != VP8_ENC_OK) goto Error;
  }

  // Alpha.
  if (enc->has_alpha_) {
    err = PutAlphaChunk(enc);
    if (err != VP8_ENC_OK) goto Error;
  }

  // VP8 header.
  err = PutVP8Header(pic, vp8_size);
  if (err != VP8_ENC_OK) goto Error;

  // VP8 frame header.
  err = PutVP8FrameHeader(pic, enc->profile_, size0);
  if (err != VP8_ENC_OK) goto Error;

  // All OK.
  return 1;

  // Error.
 Error:
  return WebPEncodingSetError(pic, err);
}