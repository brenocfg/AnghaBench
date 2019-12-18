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
struct TYPE_4__ {int /*<<< orphan*/  buf_; } ;
typedef  TYPE_1__ VP8BitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

void VP8BitWriterWipeOut(VP8BitWriter* const bw) {
  if (bw != NULL) {
    WebPSafeFree(bw->buf_);
    memset(bw, 0, sizeof(*bw));
  }
}