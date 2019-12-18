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
struct TYPE_3__ {int /*<<< orphan*/ * alph_dec_; int /*<<< orphan*/ * alpha_plane_; int /*<<< orphan*/ * alpha_plane_mem_; } ;
typedef  TYPE_1__ VP8Decoder ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void WebPDeallocateAlphaMemory(VP8Decoder* const dec) {
  assert(dec != NULL);
  WebPSafeFree(dec->alpha_plane_mem_);
  dec->alpha_plane_mem_ = NULL;
  dec->alpha_plane_ = NULL;
  ALPHDelete(dec->alph_dec_);
  dec->alph_dec_ = NULL;
}