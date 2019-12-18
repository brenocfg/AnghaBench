#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_parts_minus_one_; scalar_t__ ready_; int /*<<< orphan*/  worker_; } ;
typedef  TYPE_1__ VP8Decoder ;
struct TYPE_6__ {int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  InitGetCoeffs () ; 
 int /*<<< orphan*/  SetOk (TYPE_1__* const) ; 
 TYPE_2__* WebPGetWorkerInterface () ; 
 scalar_t__ WebPSafeCalloc (unsigned long long,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

VP8Decoder* VP8New(void) {
  VP8Decoder* const dec = (VP8Decoder*)WebPSafeCalloc(1ULL, sizeof(*dec));
  if (dec != NULL) {
    SetOk(dec);
    WebPGetWorkerInterface()->Init(&dec->worker_);
    dec->ready_ = 0;
    dec->num_parts_minus_one_ = 0;
    InitGetCoeffs();
  }
  return dec;
}