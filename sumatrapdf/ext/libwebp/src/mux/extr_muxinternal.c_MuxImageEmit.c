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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * unknown_; int /*<<< orphan*/ * img_; int /*<<< orphan*/ * alpha_; int /*<<< orphan*/ * header_; } ;
typedef  TYPE_1__ WebPMuxImage ;

/* Variables and functions */
 int /*<<< orphan*/ * ChunkEmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ChunkEmitSpecial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ChunkListEmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MuxImageDiskSize (TYPE_1__ const* const) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const* const) ; 

uint8_t* MuxImageEmit(const WebPMuxImage* const wpi, uint8_t* dst) {
  // Ordering of chunks to be emitted is strictly as follows:
  // 1. ANMF chunk (if present).
  // 2. ALPH chunk (if present).
  // 3. VP8/VP8L chunk.
  assert(wpi);
  if (wpi->header_ != NULL) {
    dst = ChunkEmitSpecial(wpi->header_, MuxImageDiskSize(wpi), dst);
  }
  if (wpi->alpha_ != NULL) dst = ChunkEmit(wpi->alpha_, dst);
  if (wpi->img_ != NULL) dst = ChunkEmit(wpi->img_, dst);
  if (wpi->unknown_ != NULL) dst = ChunkListEmit(wpi->unknown_, dst);
  return dst;
}