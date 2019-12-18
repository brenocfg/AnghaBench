#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* img_; } ;
typedef  TYPE_2__ WebPMuxImage ;
struct TYPE_9__ {int duration; int /*<<< orphan*/  bitstream; int /*<<< orphan*/  id; int /*<<< orphan*/  blend_method; int /*<<< orphan*/  dispose_method; scalar_t__ y_offset; scalar_t__ x_offset; } ;
typedef  TYPE_3__ WebPMuxFrameInfo ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_7__ {int /*<<< orphan*/  tag_; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkGetIdFromTag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SynthesizeBitstream (TYPE_2__ const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_MUX_BLEND ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_NONE ; 

__attribute__((used)) static WebPMuxError MuxGetImageInternal(const WebPMuxImage* const wpi,
                                        WebPMuxFrameInfo* const info) {
  // Set some defaults for unrelated fields.
  info->x_offset = 0;
  info->y_offset = 0;
  info->duration = 1;
  info->dispose_method = WEBP_MUX_DISPOSE_NONE;
  info->blend_method = WEBP_MUX_BLEND;
  // Extract data for related fields.
  info->id = ChunkGetIdFromTag(wpi->img_->tag_);
  return SynthesizeBitstream(wpi, &info->bitstream);
}