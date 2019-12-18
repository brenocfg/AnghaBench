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
struct TYPE_4__ {int verbose; int kmax; int kmin; scalar_t__ minimize_size; } ;
typedef  TYPE_1__ WebPAnimEncoderOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DisableKeyframes (TYPE_1__* const) ; 
 int MAX_CACHED_FRAMES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void SanitizeEncoderOptions(WebPAnimEncoderOptions* const enc_options) {
  int print_warning = enc_options->verbose;

  if (enc_options->minimize_size) {
    DisableKeyframes(enc_options);
  }

  if (enc_options->kmax == 1) {  // All frames will be key-frames.
    enc_options->kmin = 0;
    enc_options->kmax = 0;
    return;
  } else if (enc_options->kmax <= 0) {
    DisableKeyframes(enc_options);
    print_warning = 0;
  }

  if (enc_options->kmin >= enc_options->kmax) {
    enc_options->kmin = enc_options->kmax - 1;
    if (print_warning) {
      fprintf(stderr, "WARNING: Setting kmin = %d, so that kmin < kmax.\n",
              enc_options->kmin);
    }
  } else {
    const int kmin_limit = enc_options->kmax / 2 + 1;
    if (enc_options->kmin < kmin_limit && kmin_limit < enc_options->kmax) {
      // This ensures that enc.keyframe + kmin >= kmax is always true. So, we
      // can flush all the frames in the 'count_since_key_frame == kmax' case.
      enc_options->kmin = kmin_limit;
      if (print_warning) {
        fprintf(stderr,
                "WARNING: Setting kmin = %d, so that kmin >= kmax / 2 + 1.\n",
                enc_options->kmin);
      }
    }
  }
  // Limit the max number of frames that are allocated.
  if (enc_options->kmax - enc_options->kmin > MAX_CACHED_FRAMES) {
    enc_options->kmin = enc_options->kmax - MAX_CACHED_FRAMES;
    if (print_warning) {
      fprintf(stderr,
              "WARNING: Setting kmin = %d, so that kmax - kmin <= %d.\n",
              enc_options->kmin, MAX_CACHED_FRAMES);
    }
  }
  assert(enc_options->kmin < enc_options->kmax);
}