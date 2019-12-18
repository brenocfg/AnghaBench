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
 int /*<<< orphan*/  safe_isalnum (char const) ; 
 scalar_t__ safe_isspace (char const) ; 
 scalar_t__ safe_tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int startsWith(const char *s, const char *t){
  while( safe_isspace(*s) ){ s++; }
  while( *t ){
    if( safe_tolower(*s++)!=safe_tolower(*t++) ) return 0;
  }
  return *s!='_' && !safe_isalnum(*s);
}