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

__attribute__((used)) static int m_gt_1(const char *z){
  while( isVowel(z) ){ z++; }
  if( *z==0 ) return 0;
  while( isConsonant(z) ){ z++; }
  if( *z==0 ) return 0;
  while( isVowel(z) ){ z++; }
  if( *z==0 ) return 0;
  while( isConsonant(z) ){ z++; }
  return *z!=0;
}