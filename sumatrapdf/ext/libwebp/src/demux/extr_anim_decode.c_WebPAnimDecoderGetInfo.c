#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPAnimInfo ;
struct TYPE_3__ {int /*<<< orphan*/  info_; } ;
typedef  TYPE_1__ WebPAnimDecoder ;

/* Variables and functions */

int WebPAnimDecoderGetInfo(const WebPAnimDecoder* dec, WebPAnimInfo* info) {
  if (dec == NULL || info == NULL) return 0;
  *info = dec->info_;
  return 1;
}