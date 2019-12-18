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
typedef  int /*<<< orphan*/  WebPMux ;

/* Variables and functions */
 int /*<<< orphan*/  MuxInit (int /*<<< orphan*/ * const) ; 
 scalar_t__ WEBP_ABI_IS_INCOMPATIBLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_MUX_ABI_VERSION ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 

WebPMux* WebPNewInternal(int version) {
  if (WEBP_ABI_IS_INCOMPATIBLE(version, WEBP_MUX_ABI_VERSION)) {
    return NULL;
  } else {
    WebPMux* const mux = (WebPMux*)WebPSafeMalloc(1ULL, sizeof(WebPMux));
    if (mux != NULL) MuxInit(mux);
    return mux;
  }
}