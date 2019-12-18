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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {int method; int alpha_filtering; int /*<<< orphan*/  alpha_compression; int /*<<< orphan*/  alpha_quality; } ;
typedef  TYPE_1__ WebPConfig ;
typedef  int /*<<< orphan*/  WEBP_FILTER_TYPE ;
struct TYPE_5__ {size_t alpha_data_size_; int /*<<< orphan*/ * alpha_data_; TYPE_1__* config_; } ;
typedef  TYPE_2__ VP8Encoder ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeAlpha (TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int const,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  WEBP_FILTER_BEST ; 
 int /*<<< orphan*/  WEBP_FILTER_FAST ; 
 int /*<<< orphan*/  WEBP_FILTER_NONE ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int CompressAlphaJob(void* arg1, void* dummy) {
  VP8Encoder* const enc = (VP8Encoder*)arg1;
  const WebPConfig* config = enc->config_;
  uint8_t* alpha_data = NULL;
  size_t alpha_size = 0;
  const int effort_level = config->method;  // maps to [0..6]
  const WEBP_FILTER_TYPE filter =
      (config->alpha_filtering == 0) ? WEBP_FILTER_NONE :
      (config->alpha_filtering == 1) ? WEBP_FILTER_FAST :
                                       WEBP_FILTER_BEST;
  if (!EncodeAlpha(enc, config->alpha_quality, config->alpha_compression,
                   filter, effort_level, &alpha_data, &alpha_size)) {
    return 0;
  }
  if (alpha_size != (uint32_t)alpha_size) {  // Sanity check.
    WebPSafeFree(alpha_data);
    return 0;
  }
  enc->alpha_data_size_ = (uint32_t)alpha_size;
  enc->alpha_data_ = alpha_data;
  (void)dummy;
  return 1;
}