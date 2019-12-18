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
struct TYPE_5__ {int /*<<< orphan*/  tokens_; } ;
typedef  TYPE_1__ VP8Encoder ;

/* Variables and functions */
 int VP8EncDeleteAlpha (TYPE_1__*) ; 
 int /*<<< orphan*/  VP8TBufferClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPSafeFree (TYPE_1__*) ; 

__attribute__((used)) static int DeleteVP8Encoder(VP8Encoder* enc) {
  int ok = 1;
  if (enc != NULL) {
    ok = VP8EncDeleteAlpha(enc);
    VP8TBufferClear(&enc->tokens_);
    WebPSafeFree(enc);
  }
  return ok;
}