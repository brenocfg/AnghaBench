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

/* Variables and functions */
 void* RTLD_DEFAULT ; 
 scalar_t__ dlsym (void*,char const*) ; 

__attribute__((used)) static const char *ll_bcsym(void *lib, const char *sym)
{
#if defined(RTLD_DEFAULT)
  if (lib == NULL) lib = RTLD_DEFAULT;
#elif LJ_TARGET_OSX || LJ_TARGET_BSD
  if (lib == NULL) lib = (void *)(intptr_t)-2;
#endif
  return (const char *)dlsym(lib, sym);
}