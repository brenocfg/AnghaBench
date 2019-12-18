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
struct TYPE_3__ {int /*<<< orphan*/  dq_uv_ac_; int /*<<< orphan*/  dq_uv_dc_; int /*<<< orphan*/  dq_y2_ac_; int /*<<< orphan*/  dq_y2_dc_; int /*<<< orphan*/  dq_y1_dc_; int /*<<< orphan*/  base_quant_; } ;
typedef  TYPE_1__ VP8Encoder ;
typedef  int /*<<< orphan*/  VP8BitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  VP8PutBits (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VP8PutSignedBits (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PutQuant(VP8BitWriter* const bw,
                     const VP8Encoder* const enc) {
  VP8PutBits(bw, enc->base_quant_, 7);
  VP8PutSignedBits(bw, enc->dq_y1_dc_, 4);
  VP8PutSignedBits(bw, enc->dq_y2_dc_, 4);
  VP8PutSignedBits(bw, enc->dq_y2_ac_, 4);
  VP8PutSignedBits(bw, enc->dq_uv_dc_, 4);
  VP8PutSignedBits(bw, enc->dq_uv_ac_, 4);
}