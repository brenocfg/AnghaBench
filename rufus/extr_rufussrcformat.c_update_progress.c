#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  float uint64_t ;
struct TYPE_2__ {float image_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_261 ; 
 int /*<<< orphan*/  UPDATE_PERCENT (int /*<<< orphan*/ ,float) ; 
 TYPE_1__ img_report ; 

__attribute__((used)) static void update_progress(const uint64_t processed_bytes)
{
	UPDATE_PERCENT(MSG_261, (100.0f*processed_bytes) / (1.0f*img_report.image_size));
}