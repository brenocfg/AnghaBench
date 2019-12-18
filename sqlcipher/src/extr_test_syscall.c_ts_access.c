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
 int orig_access (char const*,int) ; 
 scalar_t__ tsIsFail () ; 

__attribute__((used)) static int ts_access(const char *zPath, int mode){
  if( tsIsFail() ){
    return -1;
  }
  return orig_access(zPath, mode);
}