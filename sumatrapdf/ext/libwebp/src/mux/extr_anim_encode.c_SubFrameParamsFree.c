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
struct TYPE_3__ {int /*<<< orphan*/  sub_frame_lossy_; int /*<<< orphan*/  sub_frame_ll_; } ;
typedef  TYPE_1__ SubFrameParams ;

/* Variables and functions */
 int /*<<< orphan*/  WebPPictureFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SubFrameParamsFree(SubFrameParams* const params) {
  WebPPictureFree(&params->sub_frame_ll_);
  WebPPictureFree(&params->sub_frame_lossy_);
}