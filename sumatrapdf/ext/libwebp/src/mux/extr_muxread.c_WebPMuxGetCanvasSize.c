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
typedef  int /*<<< orphan*/  WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;

/* Variables and functions */
 int /*<<< orphan*/  MuxGetCanvasInfo (int /*<<< orphan*/  const*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_MUX_INVALID_ARGUMENT ; 

WebPMuxError WebPMuxGetCanvasSize(const WebPMux* mux, int* width, int* height) {
  if (mux == NULL || width == NULL || height == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  return MuxGetCanvasInfo(mux, width, height, NULL);
}