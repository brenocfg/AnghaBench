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
typedef  int /*<<< orphan*/  vp8_frm_hdr ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  (* writer ) (int*,int,TYPE_1__ const* const) ;} ;
typedef  TYPE_1__ WebPPicture ;
typedef  int /*<<< orphan*/  WebPEncodingError ;

/* Variables and functions */
 int /*<<< orphan*/  VP8_ENC_ERROR_BAD_WRITE ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_PARTITION0_OVERFLOW ; 
 int /*<<< orphan*/  VP8_ENC_OK ; 
 int VP8_FRAME_HEADER_SIZE ; 
 size_t VP8_MAX_PARTITION0_SIZE ; 
 int VP8_SIGNATURE ; 
 int /*<<< orphan*/  stub1 (int*,int,TYPE_1__ const* const) ; 

__attribute__((used)) static WebPEncodingError PutVP8FrameHeader(const WebPPicture* const pic,
                                           int profile, size_t size0) {
  uint8_t vp8_frm_hdr[VP8_FRAME_HEADER_SIZE];
  uint32_t bits;

  if (size0 >= VP8_MAX_PARTITION0_SIZE) {  // partition #0 is too big to fit
    return VP8_ENC_ERROR_PARTITION0_OVERFLOW;
  }

  // Paragraph 9.1.
  bits = 0                         // keyframe (1b)
       | (profile << 1)            // profile (3b)
       | (1 << 4)                  // visible (1b)
       | ((uint32_t)size0 << 5);   // partition length (19b)
  vp8_frm_hdr[0] = (bits >>  0) & 0xff;
  vp8_frm_hdr[1] = (bits >>  8) & 0xff;
  vp8_frm_hdr[2] = (bits >> 16) & 0xff;
  // signature
  vp8_frm_hdr[3] = (VP8_SIGNATURE >> 16) & 0xff;
  vp8_frm_hdr[4] = (VP8_SIGNATURE >>  8) & 0xff;
  vp8_frm_hdr[5] = (VP8_SIGNATURE >>  0) & 0xff;
  // dimensions
  vp8_frm_hdr[6] = pic->width & 0xff;
  vp8_frm_hdr[7] = pic->width >> 8;
  vp8_frm_hdr[8] = pic->height & 0xff;
  vp8_frm_hdr[9] = pic->height >> 8;

  if (!pic->writer(vp8_frm_hdr, sizeof(vp8_frm_hdr), pic)) {
    return VP8_ENC_ERROR_BAD_WRITE;
  }
  return VP8_ENC_OK;
}