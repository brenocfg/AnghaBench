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
 int /*<<< orphan*/  MuxRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ *) ; 

void WebPMuxDelete(WebPMux* mux) {
  if (mux != NULL) {
    MuxRelease(mux);
    WebPSafeFree(mux);
  }
}