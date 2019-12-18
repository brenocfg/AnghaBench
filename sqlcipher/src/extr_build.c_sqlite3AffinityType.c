#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int szSorterRef; } ;
struct TYPE_4__ {int szEst; int /*<<< orphan*/  colFlags; } ;
typedef  TYPE_1__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  COLFLAG_SORTERREF ; 
 char SQLITE_AFF_BLOB ; 
 char SQLITE_AFF_INTEGER ; 
 char SQLITE_AFF_NUMERIC ; 
 char SQLITE_AFF_REAL ; 
 char SQLITE_AFF_TEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3GetInt32 (char const*,int*) ; 
 TYPE_2__ sqlite3GlobalConfig ; 
 scalar_t__ sqlite3Isdigit (char const) ; 
 int* sqlite3UpperToLower ; 

char sqlite3AffinityType(const char *zIn, Column *pCol){
  u32 h = 0;
  char aff = SQLITE_AFF_NUMERIC;
  const char *zChar = 0;

  assert( zIn!=0 );
  while( zIn[0] ){
    h = (h<<8) + sqlite3UpperToLower[(*zIn)&0xff];
    zIn++;
    if( h==(('c'<<24)+('h'<<16)+('a'<<8)+'r') ){             /* CHAR */
      aff = SQLITE_AFF_TEXT;
      zChar = zIn;
    }else if( h==(('c'<<24)+('l'<<16)+('o'<<8)+'b') ){       /* CLOB */
      aff = SQLITE_AFF_TEXT;
    }else if( h==(('t'<<24)+('e'<<16)+('x'<<8)+'t') ){       /* TEXT */
      aff = SQLITE_AFF_TEXT;
    }else if( h==(('b'<<24)+('l'<<16)+('o'<<8)+'b')          /* BLOB */
        && (aff==SQLITE_AFF_NUMERIC || aff==SQLITE_AFF_REAL) ){
      aff = SQLITE_AFF_BLOB;
      if( zIn[0]=='(' ) zChar = zIn;
#ifndef SQLITE_OMIT_FLOATING_POINT
    }else if( h==(('r'<<24)+('e'<<16)+('a'<<8)+'l')          /* REAL */
        && aff==SQLITE_AFF_NUMERIC ){
      aff = SQLITE_AFF_REAL;
    }else if( h==(('f'<<24)+('l'<<16)+('o'<<8)+'a')          /* FLOA */
        && aff==SQLITE_AFF_NUMERIC ){
      aff = SQLITE_AFF_REAL;
    }else if( h==(('d'<<24)+('o'<<16)+('u'<<8)+'b')          /* DOUB */
        && aff==SQLITE_AFF_NUMERIC ){
      aff = SQLITE_AFF_REAL;
#endif
    }else if( (h&0x00FFFFFF)==(('i'<<16)+('n'<<8)+'t') ){    /* INT */
      aff = SQLITE_AFF_INTEGER;
      break;
    }
  }

  /* If pCol is not NULL, store an estimate of the field size.  The
  ** estimate is scaled so that the size of an integer is 1.  */
  if( pCol ){
    int v = 0;   /* default size is approx 4 bytes */
    if( aff<SQLITE_AFF_NUMERIC ){
      if( zChar ){
        while( zChar[0] ){
          if( sqlite3Isdigit(zChar[0]) ){
            /* BLOB(k), VARCHAR(k), CHAR(k) -> r=(k/4+1) */
            sqlite3GetInt32(zChar, &v);
            break;
          }
          zChar++;
        }
      }else{
        v = 16;   /* BLOB, TEXT, CLOB -> r=5  (approx 20 bytes)*/
      }
    }
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
    if( v>=sqlite3GlobalConfig.szSorterRef ){
      pCol->colFlags |= COLFLAG_SORTERREF;
    }
#endif
    v = v/4 + 1;
    if( v>255 ) v = 255;
    pCol->szEst = v;
  }
  return aff;
}