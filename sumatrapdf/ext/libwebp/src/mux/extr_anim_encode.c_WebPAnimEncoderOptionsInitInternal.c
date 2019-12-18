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
typedef  int /*<<< orphan*/  WebPAnimEncoderOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultEncoderOptions (int /*<<< orphan*/ *) ; 
 scalar_t__ WEBP_ABI_IS_INCOMPATIBLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_MUX_ABI_VERSION ; 

int WebPAnimEncoderOptionsInitInternal(WebPAnimEncoderOptions* enc_options,
                                       int abi_version) {
  if (enc_options == NULL ||
      WEBP_ABI_IS_INCOMPATIBLE(abi_version, WEBP_MUX_ABI_VERSION)) {
    return 0;
  }
  DefaultEncoderOptions(enc_options);
  return 1;
}