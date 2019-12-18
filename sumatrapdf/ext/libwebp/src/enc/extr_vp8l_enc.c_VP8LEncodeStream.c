#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stats_side ;
struct TYPE_23__ {int (* Sync ) (TYPE_2__*) ;int /*<<< orphan*/  (* End ) (TYPE_2__*) ;int /*<<< orphan*/  (* Execute ) (TYPE_2__*) ;int /*<<< orphan*/  (* Launch ) (TYPE_2__*) ;int /*<<< orphan*/  (* Reset ) (TYPE_2__*) ;int /*<<< orphan*/  (* Init ) (TYPE_2__* const) ;} ;
typedef  TYPE_1__ WebPWorkerInterface ;
struct TYPE_24__ {int /*<<< orphan*/  hook; int /*<<< orphan*/ * data2; TYPE_6__* data1; } ;
typedef  TYPE_2__ WebPWorker ;
struct TYPE_25__ {int /*<<< orphan*/ * stats; } ;
typedef  TYPE_3__ WebPPicture ;
typedef  void* WebPEncodingError ;
struct TYPE_26__ {scalar_t__ thread_level; } ;
typedef  TYPE_4__ WebPConfig ;
typedef  int /*<<< orphan*/  WebPAuxStats ;
struct TYPE_27__ {int /*<<< orphan*/ * palette_; int /*<<< orphan*/  palette_size_; int /*<<< orphan*/  transform_bits_; int /*<<< orphan*/  histo_bits_; } ;
typedef  TYPE_5__ VP8LEncoder ;
typedef  int /*<<< orphan*/  VP8LBitWriter ;
struct TYPE_28__ {int num_crunch_configs_; int use_cache_; int red_and_blue_always_zero_; void* err_; TYPE_5__* enc_; int /*<<< orphan*/ * bw_; int /*<<< orphan*/ * stats_; TYPE_3__* picture_; TYPE_4__* config_; void** crunch_configs_; } ;
typedef  TYPE_6__ StreamEncodeContext ;
typedef  void* CrunchConfig ;

/* Variables and functions */
 int CRUNCH_CONFIGS_MAX ; 
 int /*<<< orphan*/  EncodeStreamHook ; 
 int /*<<< orphan*/  EncoderAnalyze (TYPE_5__* const,void**,int*,int*) ; 
 int /*<<< orphan*/  EncoderInit (TYPE_5__* const) ; 
 int /*<<< orphan*/  VP8LBitWriterClone (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LBitWriterInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VP8LBitWriterNumBytes (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8LBitWriterSwap (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LBitWriterWipeOut (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8LEncoderDelete (TYPE_5__* const) ; 
 void* VP8LEncoderNew (TYPE_4__ const* const,TYPE_3__ const* const) ; 
 void* VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 void* VP8_ENC_OK ; 
 TYPE_1__* WebPGetWorkerInterface () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int stub5 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*) ; 
 int stub7 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__*) ; 

WebPEncodingError VP8LEncodeStream(const WebPConfig* const config,
                                   const WebPPicture* const picture,
                                   VP8LBitWriter* const bw_main,
                                   int use_cache) {
  WebPEncodingError err = VP8_ENC_OK;
  VP8LEncoder* const enc_main = VP8LEncoderNew(config, picture);
  VP8LEncoder* enc_side = NULL;
  CrunchConfig crunch_configs[CRUNCH_CONFIGS_MAX];
  int num_crunch_configs_main, num_crunch_configs_side = 0;
  int idx;
  int red_and_blue_always_zero = 0;
  WebPWorker worker_main, worker_side;
  StreamEncodeContext params_main, params_side;
  // The main thread uses picture->stats, the side thread uses stats_side.
  WebPAuxStats stats_side;
  VP8LBitWriter bw_side;
  const WebPWorkerInterface* const worker_interface = WebPGetWorkerInterface();
  int ok_main;

  // Analyze image (entropy, num_palettes etc)
  if (enc_main == NULL ||
      !EncoderAnalyze(enc_main, crunch_configs, &num_crunch_configs_main,
                      &red_and_blue_always_zero) ||
      !EncoderInit(enc_main) || !VP8LBitWriterInit(&bw_side, 0)) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  // Split the configs between the main and side threads (if any).
  if (config->thread_level > 0) {
    num_crunch_configs_side = num_crunch_configs_main / 2;
    for (idx = 0; idx < num_crunch_configs_side; ++idx) {
      params_side.crunch_configs_[idx] =
          crunch_configs[num_crunch_configs_main - num_crunch_configs_side +
                         idx];
    }
    params_side.num_crunch_configs_ = num_crunch_configs_side;
  }
  num_crunch_configs_main -= num_crunch_configs_side;
  for (idx = 0; idx < num_crunch_configs_main; ++idx) {
    params_main.crunch_configs_[idx] = crunch_configs[idx];
  }
  params_main.num_crunch_configs_ = num_crunch_configs_main;

  // Fill in the parameters for the thread workers.
  {
    const int params_size = (num_crunch_configs_side > 0) ? 2 : 1;
    for (idx = 0; idx < params_size; ++idx) {
      // Create the parameters for each worker.
      WebPWorker* const worker = (idx == 0) ? &worker_main : &worker_side;
      StreamEncodeContext* const param =
          (idx == 0) ? &params_main : &params_side;
      param->config_ = config;
      param->picture_ = picture;
      param->use_cache_ = use_cache;
      param->red_and_blue_always_zero_ = red_and_blue_always_zero;
      if (idx == 0) {
        param->stats_ = picture->stats;
        param->bw_ = bw_main;
        param->enc_ = enc_main;
      } else {
        param->stats_ = (picture->stats == NULL) ? NULL : &stats_side;
        // Create a side bit writer.
        if (!VP8LBitWriterClone(bw_main, &bw_side)) {
          err = VP8_ENC_ERROR_OUT_OF_MEMORY;
          goto Error;
        }
        param->bw_ = &bw_side;
        // Create a side encoder.
        enc_side = VP8LEncoderNew(config, picture);
        if (enc_side == NULL || !EncoderInit(enc_side)) {
          err = VP8_ENC_ERROR_OUT_OF_MEMORY;
          goto Error;
        }
        // Copy the values that were computed for the main encoder.
        enc_side->histo_bits_ = enc_main->histo_bits_;
        enc_side->transform_bits_ = enc_main->transform_bits_;
        enc_side->palette_size_ = enc_main->palette_size_;
        memcpy(enc_side->palette_, enc_main->palette_,
               sizeof(enc_main->palette_));
        param->enc_ = enc_side;
      }
      // Create the workers.
      worker_interface->Init(worker);
      worker->data1 = param;
      worker->data2 = NULL;
      worker->hook = EncodeStreamHook;
    }
  }

  // Start the second thread if needed.
  if (num_crunch_configs_side != 0) {
    if (!worker_interface->Reset(&worker_side)) {
      err = VP8_ENC_ERROR_OUT_OF_MEMORY;
      goto Error;
    }
#if !defined(WEBP_DISABLE_STATS)
    // This line is here and not in the param initialization above to remove a
    // Clang static analyzer warning.
    if (picture->stats != NULL) {
      memcpy(&stats_side, picture->stats, sizeof(stats_side));
    }
#endif
    // This line is only useful to remove a Clang static analyzer warning.
    params_side.err_ = VP8_ENC_OK;
    worker_interface->Launch(&worker_side);
  }
  // Execute the main thread.
  worker_interface->Execute(&worker_main);
  ok_main = worker_interface->Sync(&worker_main);
  worker_interface->End(&worker_main);
  if (num_crunch_configs_side != 0) {
    // Wait for the second thread.
    const int ok_side = worker_interface->Sync(&worker_side);
    worker_interface->End(&worker_side);
    if (!ok_main || !ok_side) {
      err = ok_main ? params_side.err_ : params_main.err_;
      goto Error;
    }
    if (VP8LBitWriterNumBytes(&bw_side) < VP8LBitWriterNumBytes(bw_main)) {
      VP8LBitWriterSwap(bw_main, &bw_side);
#if !defined(WEBP_DISABLE_STATS)
      if (picture->stats != NULL) {
        memcpy(picture->stats, &stats_side, sizeof(*picture->stats));
      }
#endif
    }
  } else {
    if (!ok_main) {
      err = params_main.err_;
      goto Error;
    }
  }

Error:
  VP8LBitWriterWipeOut(&bw_side);
  VP8LEncoderDelete(enc_main);
  VP8LEncoderDelete(enc_side);
  return err;
}