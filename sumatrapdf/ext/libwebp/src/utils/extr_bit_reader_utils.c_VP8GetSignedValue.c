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
typedef  int const int32_t ;
typedef  int /*<<< orphan*/  VP8BitReader ;

/* Variables and functions */
 scalar_t__ VP8Get (int /*<<< orphan*/ * const,char const*) ; 
 int VP8GetValue (int /*<<< orphan*/ * const,int,char const*) ; 

int32_t VP8GetSignedValue(VP8BitReader* const br, int bits,
                          const char label[]) {
  const int value = VP8GetValue(br, bits, label);
  return VP8Get(br, label) ? -value : value;
}