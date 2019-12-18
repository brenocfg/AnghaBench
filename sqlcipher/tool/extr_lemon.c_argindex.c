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
 int /*<<< orphan*/  ISOPT (scalar_t__) ; 
 scalar_t__* argv ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int argindex(int n)
{
  int i;
  int dashdash = 0;
  if( argv!=0 && *argv!=0 ){
    for(i=1; argv[i]; i++){
      if( dashdash || !ISOPT(argv[i]) ){
        if( n==0 ) return i;
        n--;
      }
      if( strcmp(argv[i],"--")==0 ) dashdash = 1;
    }
  }
  return -1;
}