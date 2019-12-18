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
 int TK_FILTER ; 
 int TK_ID ; 
 scalar_t__ TK_LP ; 
 int TK_RP ; 
 scalar_t__ getToken (unsigned char const**) ; 

__attribute__((used)) static int analyzeFilterKeyword(const unsigned char *z, int lastToken){
  if( lastToken==TK_RP && getToken(&z)==TK_LP ){
    return TK_FILTER;
  }
  return TK_ID;
}