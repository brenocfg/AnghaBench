#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  x_expand; } ;
typedef  TYPE_1__ WebPRescaler ;

/* Variables and functions */
 int /*<<< orphan*/  WebPRescalerImportRowExpand (TYPE_1__* const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPRescalerImportRowShrink (TYPE_1__* const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPRescalerInputDone (TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 

void WebPRescalerImportRow(WebPRescaler* const wrk, const uint8_t* src) {
  assert(!WebPRescalerInputDone(wrk));
  if (!wrk->x_expand) {
    WebPRescalerImportRowShrink(wrk, src);
  } else {
    WebPRescalerImportRowExpand(wrk, src);
  }
}