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
typedef  size_t WebPMuxError ;

/* Variables and functions */
 size_t WEBP_MUX_NOT_ENOUGH_DATA ; 
 size_t WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  assert (int) ; 
 char const** kErrorMessages ; 

__attribute__((used)) static const char* ErrorString(WebPMuxError err) {
  assert(err <= WEBP_MUX_NOT_FOUND && err >= WEBP_MUX_NOT_ENOUGH_DATA);
  return kErrorMessages[-err];
}