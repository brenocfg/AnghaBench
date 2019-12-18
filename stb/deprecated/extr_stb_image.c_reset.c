#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int todo; int restart_interval; int /*<<< orphan*/  marker; TYPE_1__* img_comp; scalar_t__ nomore; scalar_t__ code_buffer; scalar_t__ code_bits; } ;
typedef  TYPE_2__ jpeg ;
struct TYPE_4__ {scalar_t__ dc_pred; } ;

/* Variables and functions */
 int /*<<< orphan*/  MARKER_none ; 

__attribute__((used)) static void reset(jpeg *j)
{
   j->code_bits = 0;
   j->code_buffer = 0;
   j->nomore = 0;
   j->img_comp[0].dc_pred = j->img_comp[1].dc_pred = j->img_comp[2].dc_pred = 0;
   j->marker = MARKER_none;
   j->todo = j->restart_interval ? j->restart_interval : 0x7fffffff;
   // no more than 1<<31 MCUs if no restart_interal? that's plenty safe,
   // since we don't even allow 1<<30 pixels
}