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
 scalar_t__ isConsonant (char const*) ; 
 scalar_t__ isVowel (char const*) ; 

__attribute__((used)) static int star_oh(const char *z){
  return
    z[0]!=0 && isConsonant(z) &&
    z[0]!='w' && z[0]!='x' && z[0]!='y' &&
    z[1]!=0 && isVowel(z+1) &&
    z[2]!=0 && isConsonant(z+2);
}