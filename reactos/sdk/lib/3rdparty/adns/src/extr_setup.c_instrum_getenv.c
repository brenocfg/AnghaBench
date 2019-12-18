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
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int /*<<< orphan*/  adns__debug (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* getenv (char const*) ; 

__attribute__((used)) static const char *instrum_getenv(adns_state ads, const char *envvar) {
  const char *value;

  value= getenv(envvar);
  if (!value) adns__debug(ads,-1,0,"environment variable %s not set",envvar);
  else adns__debug(ads,-1,0,"environment variable %s set to `%s'",envvar,value);
  return value;
}