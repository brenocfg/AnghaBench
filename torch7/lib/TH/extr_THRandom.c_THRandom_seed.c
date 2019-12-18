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
 int /*<<< orphan*/  THRandom_manualSeed (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long readURandomLong () ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

unsigned long THRandom_seed(THGenerator *_generator)
{
#ifdef _WIN32
  unsigned long s = (unsigned long)time(0);
#else
  unsigned long s = readURandomLong();
#endif
  THRandom_manualSeed(_generator, s);
  return s;
}