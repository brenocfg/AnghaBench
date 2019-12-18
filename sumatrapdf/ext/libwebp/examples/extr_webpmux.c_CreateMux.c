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
typedef  int /*<<< orphan*/  WebPData ;
typedef  int /*<<< orphan*/  W_CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ExUtilReadFileToWebPData (char const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPMuxCreate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int CreateMux(const char* const filename, WebPMux** mux) {
  WebPData bitstream;
  assert(mux != NULL);
  if (!ExUtilReadFileToWebPData(filename, &bitstream)) return 0;
  *mux = WebPMuxCreate(&bitstream, 1);
  WebPDataClear(&bitstream);
  if (*mux != NULL) return 1;
  WFPRINTF(stderr, "Failed to create mux object from file %s.\n",
           (const W_CHAR*)filename);
  return 0;
}