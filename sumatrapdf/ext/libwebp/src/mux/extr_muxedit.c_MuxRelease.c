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
struct TYPE_3__ {int /*<<< orphan*/  unknown_; int /*<<< orphan*/  xmp_; int /*<<< orphan*/  exif_; int /*<<< orphan*/  anim_; int /*<<< orphan*/  iccp_; int /*<<< orphan*/  vp8x_; int /*<<< orphan*/  images_; } ;
typedef  TYPE_1__ WebPMux ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteAllImages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MuxRelease(WebPMux* const mux) {
  assert(mux != NULL);
  DeleteAllImages(&mux->images_);
  ChunkListDelete(&mux->vp8x_);
  ChunkListDelete(&mux->iccp_);
  ChunkListDelete(&mux->anim_);
  ChunkListDelete(&mux->exif_);
  ChunkListDelete(&mux->xmp_);
  ChunkListDelete(&mux->unknown_);
}