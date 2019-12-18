#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* zName; int custom_errno; } ;

/* Variables and functions */
 TYPE_1__* aSyscall ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int tsErrno(const char *zFunc){
  int i;
  int nFunc = strlen(zFunc);
  for(i=0; aSyscall[i].zName; i++){
    if( strlen(aSyscall[i].zName)!=nFunc ) continue;
    if( memcmp(aSyscall[i].zName, zFunc, nFunc) ) continue;
    return aSyscall[i].custom_errno;
  }

  assert(0);
  return 0;
}