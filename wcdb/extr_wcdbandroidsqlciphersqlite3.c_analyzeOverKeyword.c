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
 int TK_ID ; 
 int TK_LP ; 
 int TK_OVER ; 
 int TK_RP ; 
 int getToken (unsigned char const**) ; 

__attribute__((used)) static int analyzeOverKeyword(const unsigned char *z, int lastToken){
  if( lastToken==TK_RP ){
    int t = getToken(&z);
    if( t==TK_LP || t==TK_ID ) return TK_OVER;
  }
  return TK_ID;
}