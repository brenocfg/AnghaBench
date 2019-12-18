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
struct TYPE_4__ {scalar_t__ canvas_height_; scalar_t__ canvas_width_; } ;
typedef  TYPE_1__ WebPMux ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void MuxInit(WebPMux* const mux) {
  assert(mux != NULL);
  memset(mux, 0, sizeof(*mux));
  mux->canvas_width_ = 0;     // just to be explicit
  mux->canvas_height_ = 0;
}