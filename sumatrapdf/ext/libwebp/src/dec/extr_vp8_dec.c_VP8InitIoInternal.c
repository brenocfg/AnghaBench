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
typedef  int /*<<< orphan*/  VP8Io ;

/* Variables and functions */
 scalar_t__ WEBP_ABI_IS_INCOMPATIBLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEBP_DECODER_ABI_VERSION ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

int VP8InitIoInternal(VP8Io* const io, int version) {
  if (WEBP_ABI_IS_INCOMPATIBLE(version, WEBP_DECODER_ABI_VERSION)) {
    return 0;  // mismatch error
  }
  if (io != NULL) {
    memset(io, 0, sizeof(*io));
  }
  return 1;
}