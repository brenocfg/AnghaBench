#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  progress_hook; } ;
struct TYPE_5__ {scalar_t__ curr_canvas_copy_modified_; TYPE_2__* curr_canvas_; TYPE_3__ curr_canvas_copy_; } ;
typedef  TYPE_1__ WebPAnimEncoder ;
struct TYPE_6__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  progress_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  WebPCopyPixels (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void CopyCurrentCanvas(WebPAnimEncoder* const enc) {
  if (enc->curr_canvas_copy_modified_) {
    WebPCopyPixels(enc->curr_canvas_, &enc->curr_canvas_copy_);
    enc->curr_canvas_copy_.progress_hook = enc->curr_canvas_->progress_hook;
    enc->curr_canvas_copy_.user_data = enc->curr_canvas_->user_data;
    enc->curr_canvas_copy_modified_ = 0;
  }
}