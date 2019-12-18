#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ size; } ;
struct TYPE_10__ {TYPE_3__ bitstream; } ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_8__ {TYPE_1__ bitstream; } ;
struct TYPE_11__ {TYPE_4__ sub_frame_; TYPE_2__ key_frame_; } ;
typedef  TYPE_5__ EncodedFrame ;

/* Variables and functions */

__attribute__((used)) static int64_t KeyFramePenalty(const EncodedFrame* const encoded_frame) {
  return ((int64_t)encoded_frame->key_frame_.bitstream.size -
          encoded_frame->sub_frame_.bitstream.size);
}