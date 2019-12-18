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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  image_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_261 ; 
 int /*<<< orphan*/  OP_FORMAT ; 
 int /*<<< orphan*/  UpdateProgressWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_1__ img_report ; 

__attribute__((used)) static void update_progress(const uint64_t processed_bytes)
{
	UpdateProgressWithInfo(OP_FORMAT, MSG_261, processed_bytes, img_report.image_size);
}