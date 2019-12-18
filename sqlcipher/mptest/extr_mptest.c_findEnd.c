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
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ tokenLength (char const*,int*) ; 

__attribute__((used)) static int findEnd(const char *z, int *pnLine){
  int n = 0;
  while( z[n] && (strncmp(z+n,"--end",5) || !ISSPACE(z[n+5])) ){
    n += tokenLength(z+n, pnLine);
  }
  return n;
}