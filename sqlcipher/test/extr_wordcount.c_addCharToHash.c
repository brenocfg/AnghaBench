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

__attribute__((used)) static void addCharToHash(unsigned int *a, unsigned char x){
  if( a[0]<4 ){
    a[1] = (a[1]<<8) | x;
    a[0]++;
  }else{
    a[2] = (a[2]<<8) | x;
    a[0]++;
    if( a[0]==8 ){
      a[3] += a[1] + a[4];
      a[4] += a[2] + a[3];
      a[0] = a[1] = a[2] = 0;
    }
  }    
}