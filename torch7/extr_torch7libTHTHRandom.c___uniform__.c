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
typedef  int /*<<< orphan*/  THGenerator ;

/* Variables and functions */
 scalar_t__ THRandom_random (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double __uniform__(THGenerator *_generator)
{
  /* divided by 2^32 */
  return (double)THRandom_random(_generator) * (1.0/4294967296.0);
}