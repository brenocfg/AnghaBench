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
struct TYPE_4__ {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ WebPDecoderConfig ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultFeatures (int /*<<< orphan*/ *) ; 
 scalar_t__ WEBP_ABI_IS_INCOMPATIBLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_DECODER_ABI_VERSION ; 
 int /*<<< orphan*/  WebPInitDecBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int WebPInitDecoderConfigInternal(WebPDecoderConfig* config,
                                  int version) {
  if (WEBP_ABI_IS_INCOMPATIBLE(version, WEBP_DECODER_ABI_VERSION)) {
    return 0;   // version mismatch
  }
  if (config == NULL) {
    return 0;
  }
  memset(config, 0, sizeof(*config));
  DefaultFeatures(&config->input);
  WebPInitDecBuffer(&config->output);
  return 1;
}