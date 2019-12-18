#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* z; } ;
typedef  TYPE_1__ GeoParse ;
typedef  double GeoCoord ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ atof (char const*) ; 
 char geopolySkipSpace (TYPE_1__*) ; 
 scalar_t__ safe_isdigit (char) ; 
 int /*<<< orphan*/  sqlite3AtoF (char const*,double*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int geopolyParseNumber(GeoParse *p, GeoCoord *pVal){
  char c = geopolySkipSpace(p);
  const unsigned char *z = p->z;
  int j = 0;
  int seenDP = 0;
  int seenE = 0;
  if( c=='-' ){
    j = 1;
    c = z[j];
  }
  if( c=='0' && z[j+1]>='0' && z[j+1]<='9' ) return 0;
  for(;; j++){
    c = z[j];
    if( safe_isdigit(c) ) continue;
    if( c=='.' ){
      if( z[j-1]=='-' ) return 0;
      if( seenDP ) return 0;
      seenDP = 1;
      continue;
    }
    if( c=='e' || c=='E' ){
      if( z[j-1]<'0' ) return 0;
      if( seenE ) return -1;
      seenDP = seenE = 1;
      c = z[j+1];
      if( c=='+' || c=='-' ){
        j++;
        c = z[j+1];
      }
      if( c<'0' || c>'9' ) return 0;
      continue;
    }
    break;
  }
  if( z[j-1]<'0' ) return 0;
  if( pVal ){
#ifdef SQLITE_AMALGAMATION
     /* The sqlite3AtoF() routine is much much faster than atof(), if it
     ** is available */
     double r;
     (void)sqlite3AtoF((const char*)p->z, &r, j, SQLITE_UTF8);
     *pVal = r;
#else
     *pVal = (GeoCoord)atof((const char*)p->z);
#endif
  }
  p->z += j;
  return 1;
}