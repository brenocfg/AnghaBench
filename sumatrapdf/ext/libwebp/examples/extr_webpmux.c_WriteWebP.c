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
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;

/* Variables and functions */
 char* ErrorString (scalar_t__ const) ; 
 scalar_t__ const WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPMuxAssemble (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int WriteData (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int WriteWebP(WebPMux* const mux, const char* filename) {
  int ok;
  WebPData webp_data;
  const WebPMuxError err = WebPMuxAssemble(mux, &webp_data);
  if (err != WEBP_MUX_OK) {
    fprintf(stderr, "Error (%s) assembling the WebP file.\n", ErrorString(err));
    return 0;
  }
  ok = WriteData(filename, &webp_data);
  WebPDataClear(&webp_data);
  return ok;
}