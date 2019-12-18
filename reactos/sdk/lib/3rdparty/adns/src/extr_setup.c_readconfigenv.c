#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* adns_state ;
struct TYPE_6__ {int iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns__debug (TYPE_1__*,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int adns_if_noenv ; 
 char* instrum_getenv (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  readconfig (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static void readconfigenv(adns_state ads, const char *envvar) {
  const char *filename;

  if (ads->iflags & adns_if_noenv) {
    adns__debug(ads,-1,0,"not checking environment variable `%s'",envvar);
    return;
  }
  filename= instrum_getenv(ads,envvar);
  if (filename) readconfig(ads,filename,1);
}