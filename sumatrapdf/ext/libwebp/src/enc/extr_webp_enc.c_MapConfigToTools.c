#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int score_t ;
struct TYPE_4__ {int method; int partition_limit; scalar_t__ target_size; scalar_t__ target_PSNR; int /*<<< orphan*/  low_memory; int /*<<< orphan*/  thread_level; } ;
typedef  TYPE_1__ WebPConfig ;
struct TYPE_5__ {int method_; scalar_t__ rd_opt_level_; int max_i4_header_bits_; int mb_header_limit_; int mb_w_; int mb_h_; int do_search_; int use_tokens_; int num_parts_; int /*<<< orphan*/  thread_level_; TYPE_1__* config_; } ;
typedef  TYPE_2__ VP8Encoder ;

/* Variables and functions */
 scalar_t__ RD_OPT_BASIC ; 
 scalar_t__ RD_OPT_NONE ; 
 scalar_t__ RD_OPT_TRELLIS ; 
 scalar_t__ RD_OPT_TRELLIS_ALL ; 

__attribute__((used)) static void MapConfigToTools(VP8Encoder* const enc) {
  const WebPConfig* const config = enc->config_;
  const int method = config->method;
  const int limit = 100 - config->partition_limit;
  enc->method_ = method;
  enc->rd_opt_level_ = (method >= 6) ? RD_OPT_TRELLIS_ALL
                     : (method >= 5) ? RD_OPT_TRELLIS
                     : (method >= 3) ? RD_OPT_BASIC
                     : RD_OPT_NONE;
  enc->max_i4_header_bits_ =
      256 * 16 * 16 *                 // upper bound: up to 16bit per 4x4 block
      (limit * limit) / (100 * 100);  // ... modulated with a quadratic curve.

  // partition0 = 512k max.
  enc->mb_header_limit_ =
      (score_t)256 * 510 * 8 * 1024 / (enc->mb_w_ * enc->mb_h_);

  enc->thread_level_ = config->thread_level;

  enc->do_search_ = (config->target_size > 0 || config->target_PSNR > 0);
  if (!config->low_memory) {
#if !defined(DISABLE_TOKEN_BUFFER)
    enc->use_tokens_ = (enc->rd_opt_level_ >= RD_OPT_BASIC);  // need rd stats
#endif
    if (enc->use_tokens_) {
      enc->num_parts_ = 1;   // doesn't work with multi-partition
    }
  }
}