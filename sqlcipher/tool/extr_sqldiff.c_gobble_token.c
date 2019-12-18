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

const char *gobble_token(const char *zIn, char *zBuf, int nBuf){
  const char *p = zIn;
  char *pOut = zBuf;
  char *pEnd = &pOut[nBuf-1];
  char q = 0;                     /* quote character, if any */

  if( p==0 ) return 0;
  while( *p==' ' ) p++;
  switch( *p ){
    case '"': q = '"'; break;
    case '\'': q = '\''; break;
    case '`': q = '`'; break;
    case '[': q = ']'; break;
  }

  if( q ){
    p++;
    while( *p && pOut<pEnd ){
      if( *p==q ){
        p++;
        if( *p!=q ) break;
      }
      if( pOut<pEnd ) *pOut++ = *p;
      p++;
    }
  }else{
    while( *p && *p!=' ' && *p!='(' ){
      if( pOut<pEnd ) *pOut++ = *p;
      p++;
    }
  }

  *pOut = '\0';
  return p;
}