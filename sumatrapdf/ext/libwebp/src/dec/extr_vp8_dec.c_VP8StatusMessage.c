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
struct TYPE_3__ {char const* error_msg_; } ;
typedef  TYPE_1__ VP8Decoder ;

/* Variables and functions */

const char* VP8StatusMessage(VP8Decoder* const dec) {
  if (dec == NULL) return "no object";
  if (!dec->error_msg_) return "OK";
  return dec->error_msg_;
}