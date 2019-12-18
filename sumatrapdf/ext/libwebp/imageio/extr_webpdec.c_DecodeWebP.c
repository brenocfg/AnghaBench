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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  WebPDecoderConfig ;
typedef  int /*<<< orphan*/  VP8StatusCode ;

/* Variables and functions */
 int /*<<< orphan*/  PrintAnimationWarning (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8_STATUS_INVALID_PARAM ; 
 int /*<<< orphan*/  WebPDecode (int /*<<< orphan*/  const* const,size_t,int /*<<< orphan*/ * const) ; 

VP8StatusCode DecodeWebP(const uint8_t* const data, size_t data_size,
                         WebPDecoderConfig* const config) {
  if (config == NULL) return VP8_STATUS_INVALID_PARAM;
  PrintAnimationWarning(config);
  return WebPDecode(data, data_size, config);
}