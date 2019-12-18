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
 char* fts5ConfigSkipLiteral (char const*) ; 
 char* fts5ConfigSkipWhitespace (char const*) ; 

__attribute__((used)) static const char *fts5ConfigSkipArgs(const char *pIn){
  const char *p = pIn;
  
  while( 1 ){
    p = fts5ConfigSkipWhitespace(p);
    p = fts5ConfigSkipLiteral(p);
    p = fts5ConfigSkipWhitespace(p);
    if( p==0 || *p==')' ) break;
    if( *p!=',' ){
      p = 0;
      break;
    }
    p++;
  }

  return p;
}