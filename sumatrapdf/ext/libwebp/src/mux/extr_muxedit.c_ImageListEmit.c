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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {struct TYPE_4__* next_; } ;
typedef  TYPE_1__ WebPMuxImage ;

/* Variables and functions */
 int /*<<< orphan*/ * MuxImageEmit (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint8_t* ImageListEmit(const WebPMuxImage* wpi_list, uint8_t* dst) {
  while (wpi_list != NULL) {
    dst = MuxImageEmit(wpi_list, dst);
    wpi_list = wpi_list->next_;
  }
  return dst;
}