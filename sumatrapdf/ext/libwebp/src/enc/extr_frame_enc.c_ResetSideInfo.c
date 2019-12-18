#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * stats; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_7__ {int /*<<< orphan*/  block_count_; TYPE_1__* pic_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_8__ {TYPE_2__* enc_; } ;
typedef  TYPE_3__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  ResetSSE (TYPE_2__* const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ResetSideInfo(const VP8EncIterator* const it) {
  VP8Encoder* const enc = it->enc_;
  WebPPicture* const pic = enc->pic_;
  if (pic->stats != NULL) {
    memset(enc->block_count_, 0, sizeof(enc->block_count_));
  }
  ResetSSE(enc);
}