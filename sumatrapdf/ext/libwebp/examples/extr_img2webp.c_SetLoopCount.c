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
typedef  int uint32_t ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_4__ {int loop_count; } ;
typedef  TYPE_1__ WebPMuxAnimParams ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;

/* Variables and functions */
 int ANIMATION_FLAG ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ * const) ; 
 scalar_t__ WebPMuxAssemble (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * WebPMuxCreate (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  WebPMuxDelete (int /*<<< orphan*/ * const) ; 
 scalar_t__ WebPMuxGetAnimationParams (int /*<<< orphan*/ * const,TYPE_1__*) ; 
 scalar_t__ WebPMuxGetFeatures (int /*<<< orphan*/ * const,int*) ; 
 scalar_t__ WebPMuxSetAnimationParams (int /*<<< orphan*/ * const,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int SetLoopCount(int loop_count, WebPData* const webp_data) {
  int ok = 1;
  WebPMuxError err;
  uint32_t features;
  WebPMuxAnimParams new_params;
  WebPMux* const mux = WebPMuxCreate(webp_data, 1);
  if (mux == NULL) return 0;

  err = WebPMuxGetFeatures(mux, &features);
  ok = (err == WEBP_MUX_OK);
  if (!ok || !(features & ANIMATION_FLAG)) goto End;

  err = WebPMuxGetAnimationParams(mux, &new_params);
  ok = (err == WEBP_MUX_OK);
  if (ok) {
    new_params.loop_count = loop_count;
    err = WebPMuxSetAnimationParams(mux, &new_params);
    ok = (err == WEBP_MUX_OK);
  }
  if (ok) {
    WebPDataClear(webp_data);
    err = WebPMuxAssemble(mux, webp_data);
    ok = (err == WEBP_MUX_OK);
  }

 End:
  WebPMuxDelete(mux);
  if (!ok) {
    fprintf(stderr, "Error during loop-count setting\n");
  }
  return ok;
}