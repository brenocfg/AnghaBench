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
typedef  scalar_t__ VP8StatusCode ;
struct TYPE_3__ {scalar_t__ status_; char* error_msg_; scalar_t__ ready_; } ;
typedef  TYPE_1__ VP8Decoder ;

/* Variables and functions */
 scalar_t__ VP8_STATUS_OK ; 

int VP8SetError(VP8Decoder* const dec,
                VP8StatusCode error, const char* const msg) {
  // The oldest error reported takes precedence over the new one.
  if (dec->status_ == VP8_STATUS_OK) {
    dec->status_ = error;
    dec->error_msg_ = msg;
    dec->ready_ = 0;
  }
  return 0;
}