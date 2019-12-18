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
struct TYPE_3__ {int /*<<< orphan*/ * memory_; int /*<<< orphan*/ * memory_argb_; scalar_t__ use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */

int WebPPictureIsView(const WebPPicture* picture) {
  if (picture == NULL) return 0;
  if (picture->use_argb) {
    return (picture->memory_argb_ == NULL);
  }
  return (picture->memory_ == NULL);
}