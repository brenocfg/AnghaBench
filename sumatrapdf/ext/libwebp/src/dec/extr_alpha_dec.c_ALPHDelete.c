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
struct TYPE_4__ {int /*<<< orphan*/ * vp8l_dec_; } ;
typedef  TYPE_1__ ALPHDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPSafeFree (TYPE_1__* const) ; 

__attribute__((used)) static void ALPHDelete(ALPHDecoder* const dec) {
  if (dec != NULL) {
    VP8LDelete(dec->vp8l_dec_);
    dec->vp8l_dec_ = NULL;
    WebPSafeFree(dec);
  }
}