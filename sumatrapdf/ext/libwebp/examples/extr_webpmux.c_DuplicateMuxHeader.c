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
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMuxAnimParams ;
typedef  int /*<<< orphan*/  WebPMux ;
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ WebPData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_GOTO1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_GOTO2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  End ; 
 int /*<<< orphan*/  ErrorString (scalar_t__) ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPMuxDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPMuxGetAnimationParams (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 scalar_t__ WebPMuxGetChunk (int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * WebPMuxNew () ; 
 scalar_t__ WebPMuxSetAnimationParams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WebPMuxSetChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * kFourccList ; 

__attribute__((used)) static WebPMux* DuplicateMuxHeader(const WebPMux* const mux) {
  WebPMux* new_mux = WebPMuxNew();
  WebPMuxAnimParams p;
  WebPMuxError err;
  int i;
  int ok = 1;

  if (new_mux == NULL) return NULL;

  err = WebPMuxGetAnimationParams(mux, &p);
  if (err == WEBP_MUX_OK) {
    err = WebPMuxSetAnimationParams(new_mux, &p);
    if (err != WEBP_MUX_OK) {
      ERROR_GOTO2("Error (%s) handling animation params.\n",
                  ErrorString(err), End);
    }
  } else {
    /* it might not be an animation. Just keep moving. */
  }

  for (i = 1; i <= 3; ++i) {
    WebPData metadata;
    err = WebPMuxGetChunk(mux, kFourccList[i], &metadata);
    if (err == WEBP_MUX_OK && metadata.size > 0) {
      err = WebPMuxSetChunk(new_mux, kFourccList[i], &metadata, 1);
      if (err != WEBP_MUX_OK) {
        ERROR_GOTO1("Error transferring metadata in DuplicateMux().", End);
      }
    }
  }

 End:
  if (!ok) {
    WebPMuxDelete(new_mux);
    new_mux = NULL;
  }
  return new_mux;
}