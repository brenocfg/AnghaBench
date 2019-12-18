#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int* y; int const y_stride; int* u; int const uv_stride; int* v; scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_7__ {TYPE_1__* pic_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_8__ {int x_; int y_; int* y_left_; int* u_left_; int* v_left_; int* y_top_; int* uv_top_; scalar_t__ yuv_in_; TYPE_2__* enc_; } ;
typedef  TYPE_3__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  ImportBlock (int const* const,int const,scalar_t__,int const,int const,int) ; 
 int /*<<< orphan*/  ImportLine (int const* const,int,int* const,int const,int) ; 
 int /*<<< orphan*/  InitLeft (TYPE_3__* const) ; 
 int MinSize (scalar_t__,int) ; 
 scalar_t__ U_OFF_ENC ; 
 scalar_t__ V_OFF_ENC ; 
 scalar_t__ Y_OFF_ENC ; 
 int /*<<< orphan*/  memset (int* const,int,int) ; 

void VP8IteratorImport(VP8EncIterator* const it, uint8_t* const tmp_32) {
  const VP8Encoder* const enc = it->enc_;
  const int x = it->x_, y = it->y_;
  const WebPPicture* const pic = enc->pic_;
  const uint8_t* const ysrc = pic->y + (y * pic->y_stride  + x) * 16;
  const uint8_t* const usrc = pic->u + (y * pic->uv_stride + x) * 8;
  const uint8_t* const vsrc = pic->v + (y * pic->uv_stride + x) * 8;
  const int w = MinSize(pic->width - x * 16, 16);
  const int h = MinSize(pic->height - y * 16, 16);
  const int uv_w = (w + 1) >> 1;
  const int uv_h = (h + 1) >> 1;

  ImportBlock(ysrc, pic->y_stride,  it->yuv_in_ + Y_OFF_ENC, w, h, 16);
  ImportBlock(usrc, pic->uv_stride, it->yuv_in_ + U_OFF_ENC, uv_w, uv_h, 8);
  ImportBlock(vsrc, pic->uv_stride, it->yuv_in_ + V_OFF_ENC, uv_w, uv_h, 8);

  if (tmp_32 == NULL) return;

  // Import source (uncompressed) samples into boundary.
  if (x == 0) {
    InitLeft(it);
  } else {
    if (y == 0) {
      it->y_left_[-1] = it->u_left_[-1] = it->v_left_[-1] = 127;
    } else {
      it->y_left_[-1] = ysrc[- 1 - pic->y_stride];
      it->u_left_[-1] = usrc[- 1 - pic->uv_stride];
      it->v_left_[-1] = vsrc[- 1 - pic->uv_stride];
    }
    ImportLine(ysrc - 1, pic->y_stride,  it->y_left_, h,   16);
    ImportLine(usrc - 1, pic->uv_stride, it->u_left_, uv_h, 8);
    ImportLine(vsrc - 1, pic->uv_stride, it->v_left_, uv_h, 8);
  }

  it->y_top_  = tmp_32 + 0;
  it->uv_top_ = tmp_32 + 16;
  if (y == 0) {
    memset(tmp_32, 127, 32 * sizeof(*tmp_32));
  } else {
    ImportLine(ysrc - pic->y_stride,  1, tmp_32,          w,   16);
    ImportLine(usrc - pic->uv_stride, 1, tmp_32 + 16,     uv_w, 8);
    ImportLine(vsrc - pic->uv_stride, 1, tmp_32 + 16 + 8, uv_w, 8);
  }
}