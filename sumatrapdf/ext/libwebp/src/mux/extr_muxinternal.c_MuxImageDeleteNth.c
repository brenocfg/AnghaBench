#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxImage ;
typedef  int /*<<< orphan*/  WebPMuxError ;

/* Variables and functions */
 int /*<<< orphan*/ * MuxImageDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SearchImageToGetOrDelete (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 

WebPMuxError MuxImageDeleteNth(WebPMuxImage** wpi_list, uint32_t nth) {
  assert(wpi_list);
  if (!SearchImageToGetOrDelete(wpi_list, nth, &wpi_list)) {
    return WEBP_MUX_NOT_FOUND;
  }
  *wpi_list = MuxImageDelete(*wpi_list);
  return WEBP_MUX_OK;
}