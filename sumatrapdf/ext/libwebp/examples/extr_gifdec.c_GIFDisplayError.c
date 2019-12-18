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
struct GifFileType {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ErrorGIFNotAvailable () ; 

void GIFDisplayError(const struct GifFileType* const gif, int gif_error) {
  (void)gif;
  (void)gif_error;
  ErrorGIFNotAvailable();
}