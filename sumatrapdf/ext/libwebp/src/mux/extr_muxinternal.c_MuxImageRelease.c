#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next_; int /*<<< orphan*/  unknown_; int /*<<< orphan*/  img_; int /*<<< orphan*/  alpha_; int /*<<< orphan*/  header_; } ;
typedef  TYPE_1__ WebPMuxImage ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MuxImageInit (TYPE_1__* const) ; 

WebPMuxImage* MuxImageRelease(WebPMuxImage* const wpi) {
  WebPMuxImage* next;
  if (wpi == NULL) return NULL;
  // There should be at most one chunk of header_, alpha_, img_ but we call
  // ChunkListDelete to be safe
  ChunkListDelete(&wpi->header_);
  ChunkListDelete(&wpi->alpha_);
  ChunkListDelete(&wpi->img_);
  ChunkListDelete(&wpi->unknown_);

  next = wpi->next_;
  MuxImageInit(wpi);
  return next;
}