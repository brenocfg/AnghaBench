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
typedef  int /*<<< orphan*/  WebPData ;
typedef  int /*<<< orphan*/  WebPAnimDecoderOptions ;
struct TYPE_7__ {unsigned long long canvas_width; int canvas_height; void* frame_count; void* bgcolor; void* loop_count; } ;
struct TYPE_8__ {int /*<<< orphan*/ * prev_frame_disposed_; TYPE_1__ info_; int /*<<< orphan*/ * curr_frame_; int /*<<< orphan*/ * demux_; } ;
typedef  TYPE_2__ WebPAnimDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyDecoderOptions (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DefaultDecoderOptions (int /*<<< orphan*/ *) ; 
 unsigned long long NUM_CHANNELS ; 
 scalar_t__ WEBP_ABI_IS_INCOMPATIBLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_DEMUX_ABI_VERSION ; 
 int /*<<< orphan*/  WEBP_FF_BACKGROUND_COLOR ; 
 int /*<<< orphan*/  WEBP_FF_CANVAS_HEIGHT ; 
 int /*<<< orphan*/  WEBP_FF_CANVAS_WIDTH ; 
 int /*<<< orphan*/  WEBP_FF_FRAME_COUNT ; 
 int /*<<< orphan*/  WEBP_FF_LOOP_COUNT ; 
 int /*<<< orphan*/  WebPAnimDecoderDelete (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPAnimDecoderReset (TYPE_2__*) ; 
 int /*<<< orphan*/ * WebPDemux (int /*<<< orphan*/  const*) ; 
 void* WebPDemuxGetI (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WebPSafeCalloc (unsigned long long,int) ; 

WebPAnimDecoder* WebPAnimDecoderNewInternal(
    const WebPData* webp_data, const WebPAnimDecoderOptions* dec_options,
    int abi_version) {
  WebPAnimDecoderOptions options;
  WebPAnimDecoder* dec = NULL;
  if (webp_data == NULL ||
      WEBP_ABI_IS_INCOMPATIBLE(abi_version, WEBP_DEMUX_ABI_VERSION)) {
    return NULL;
  }

  // Note: calloc() so that the pointer members are initialized to NULL.
  dec = (WebPAnimDecoder*)WebPSafeCalloc(1ULL, sizeof(*dec));
  if (dec == NULL) goto Error;

  if (dec_options != NULL) {
    options = *dec_options;
  } else {
    DefaultDecoderOptions(&options);
  }
  if (!ApplyDecoderOptions(&options, dec)) goto Error;

  dec->demux_ = WebPDemux(webp_data);
  if (dec->demux_ == NULL) goto Error;

  dec->info_.canvas_width = WebPDemuxGetI(dec->demux_, WEBP_FF_CANVAS_WIDTH);
  dec->info_.canvas_height = WebPDemuxGetI(dec->demux_, WEBP_FF_CANVAS_HEIGHT);
  dec->info_.loop_count = WebPDemuxGetI(dec->demux_, WEBP_FF_LOOP_COUNT);
  dec->info_.bgcolor = WebPDemuxGetI(dec->demux_, WEBP_FF_BACKGROUND_COLOR);
  dec->info_.frame_count = WebPDemuxGetI(dec->demux_, WEBP_FF_FRAME_COUNT);

  // Note: calloc() because we fill frame with zeroes as well.
  dec->curr_frame_ = (uint8_t*)WebPSafeCalloc(
      dec->info_.canvas_width * NUM_CHANNELS, dec->info_.canvas_height);
  if (dec->curr_frame_ == NULL) goto Error;
  dec->prev_frame_disposed_ = (uint8_t*)WebPSafeCalloc(
      dec->info_.canvas_width * NUM_CHANNELS, dec->info_.canvas_height);
  if (dec->prev_frame_disposed_ == NULL) goto Error;

  WebPAnimDecoderReset(dec);
  return dec;

 Error:
  WebPAnimDecoderDelete(dec);
  return NULL;
}