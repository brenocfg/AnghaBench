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
struct TYPE_4__ {int lossless; int /*<<< orphan*/  quality; int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ WebPConfig ;
struct TYPE_5__ {int /*<<< orphan*/  quality_; int /*<<< orphan*/  method_; } ;

/* Variables and functions */
 int MAX_LEVEL ; 
 TYPE_2__* kLosslessPresets ; 

int WebPConfigLosslessPreset(WebPConfig* config, int level) {
  if (config == NULL || level < 0 || level > MAX_LEVEL) return 0;
  config->lossless = 1;
  config->method = kLosslessPresets[level].method_;
  config->quality = kLosslessPresets[level].quality_;
  return 1;
}