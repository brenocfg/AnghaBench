#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ size; } ;
struct TYPE_15__ {scalar_t__ id; TYPE_2__ bitstream; } ;
typedef  TYPE_1__ WebPMuxFrameInfo ;
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  TYPE_2__ WebPData ;
struct TYPE_17__ {int out_frame_count_; } ;
typedef  TYPE_3__ WebPAnimEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  FrameToFullCanvas (TYPE_3__* const,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ WEBP_CHUNK_ANMF ; 
 scalar_t__ WEBP_MUX_BAD_DATA ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (TYPE_2__* const) ; 
 int /*<<< orphan*/  WebPDataInit (TYPE_2__*) ; 
 scalar_t__ WebPMuxAssemble (int /*<<< orphan*/ * const,TYPE_2__*) ; 
 int /*<<< orphan*/ * WebPMuxCreate (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPMuxDelete (int /*<<< orphan*/ * const) ; 
 scalar_t__ WebPMuxGetCanvasSize (int /*<<< orphan*/ * const,int*,int*) ; 
 scalar_t__ WebPMuxGetFrame (int /*<<< orphan*/ * const,int,TYPE_1__*) ; 
 scalar_t__ WebPMuxSetImage (int /*<<< orphan*/ * const,TYPE_2__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static WebPMuxError OptimizeSingleFrame(WebPAnimEncoder* const enc,
                                        WebPData* const webp_data) {
  WebPMuxError err = WEBP_MUX_OK;
  int canvas_width, canvas_height;
  WebPMuxFrameInfo frame;
  WebPData full_image;
  WebPData webp_data2;
  WebPMux* const mux = WebPMuxCreate(webp_data, 0);
  if (mux == NULL) return WEBP_MUX_BAD_DATA;
  assert(enc->out_frame_count_ == 1);
  WebPDataInit(&frame.bitstream);
  WebPDataInit(&full_image);
  WebPDataInit(&webp_data2);

  err = WebPMuxGetFrame(mux, 1, &frame);
  if (err != WEBP_MUX_OK) goto End;
  if (frame.id != WEBP_CHUNK_ANMF) goto End;  // Non-animation: nothing to do.
  err = WebPMuxGetCanvasSize(mux, &canvas_width, &canvas_height);
  if (err != WEBP_MUX_OK) goto End;
  if (!FrameToFullCanvas(enc, &frame, &full_image)) {
    err = WEBP_MUX_BAD_DATA;
    goto End;
  }
  err = WebPMuxSetImage(mux, &full_image, 1);
  if (err != WEBP_MUX_OK) goto End;
  err = WebPMuxAssemble(mux, &webp_data2);
  if (err != WEBP_MUX_OK) goto End;

  if (webp_data2.size < webp_data->size) {  // Pick 'webp_data2' if smaller.
    WebPDataClear(webp_data);
    *webp_data = webp_data2;
    WebPDataInit(&webp_data2);
  }

 End:
  WebPDataClear(&frame.bitstream);
  WebPDataClear(&full_image);
  WebPMuxDelete(mux);
  WebPDataClear(&webp_data2);
  return err;
}