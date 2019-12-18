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
 char* malloc (int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void *asciiToUtf16le(const char *z){
  int n = strlen(z);
  char *z16;
  int i, j;

  z16 = malloc( n*2 + 2 );
  for(i=j=0; i<=n; i++){
    z16[j++] = z[i];
    z16[j++] = 0;
  }
  return (void*)z16;
}