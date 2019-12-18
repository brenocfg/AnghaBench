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
struct TYPE_4__ {struct TYPE_4__* next_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  int /*<<< orphan*/  WebPMuxError ;

/* Variables and functions */
 int /*<<< orphan*/  WEBP_MUX_MEMORY_ERROR ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 

WebPMuxError MuxImagePush(const WebPMuxImage* wpi, WebPMuxImage** wpi_list) {
  WebPMuxImage* new_wpi;

  while (*wpi_list != NULL) {
    WebPMuxImage* const cur_wpi = *wpi_list;
    if (cur_wpi->next_ == NULL) break;
    wpi_list = &cur_wpi->next_;
  }

  new_wpi = (WebPMuxImage*)WebPSafeMalloc(1ULL, sizeof(*new_wpi));
  if (new_wpi == NULL) return WEBP_MUX_MEMORY_ERROR;
  *new_wpi = *wpi;
  new_wpi->next_ = NULL;

  if (*wpi_list != NULL) {
    (*wpi_list)->next_ = new_wpi;
  } else {
    *wpi_list = new_wpi;
  }
  return WEBP_MUX_OK;
}