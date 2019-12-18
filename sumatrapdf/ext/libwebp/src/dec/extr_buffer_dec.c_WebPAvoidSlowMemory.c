#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_external_memory; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ WebPDecBuffer ;
struct TYPE_6__ {scalar_t__ has_alpha; } ;
typedef  TYPE_2__ WebPBitstreamFeatures ;

/* Variables and functions */
 scalar_t__ WebPIsPremultipliedMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int WebPAvoidSlowMemory(const WebPDecBuffer* const output,
                        const WebPBitstreamFeatures* const features) {
  assert(output != NULL);
  return (output->is_external_memory >= 2) &&
         WebPIsPremultipliedMode(output->colorspace) &&
         (features != NULL && features->has_alpha);
}