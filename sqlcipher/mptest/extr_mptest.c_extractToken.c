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
 int /*<<< orphan*/  ISSPACE (char const) ; 

__attribute__((used)) static int extractToken(const char *zIn, int nIn, char *zOut, int nOut){
  int i;
  if( nIn<=0 ){
    zOut[0] = 0;
    return 0;
  }
  for(i=0; i<nIn && i<nOut-1 && !ISSPACE(zIn[i]); i++){ zOut[i] = zIn[i]; }
  zOut[i] = 0;
  return i;
}