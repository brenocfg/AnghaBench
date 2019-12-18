#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_9__ {unsigned char const* z; int nVertex; int nAlloc; scalar_t__* a; int /*<<< orphan*/  nErr; } ;
struct TYPE_8__ {int nVertex; unsigned char* hdr; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ GeoPoly ;
typedef  TYPE_2__ GeoParse ;
typedef  scalar_t__ GeoCoord ;

/* Variables and functions */
 int /*<<< orphan*/  GEOPOLY_SZ (int /*<<< orphan*/ ) ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ geopolyParseNumber (TYPE_2__*,scalar_t__*) ; 
 char geopolySkipSpace (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__*) ; 
 TYPE_1__* sqlite3_malloc64 (int /*<<< orphan*/ ) ; 
 scalar_t__* sqlite3_realloc64 (scalar_t__*,int) ; 

__attribute__((used)) static GeoPoly *geopolyParseJson(const unsigned char *z, int *pRc){
  GeoParse s;
  int rc = SQLITE_OK;
  memset(&s, 0, sizeof(s));
  s.z = z;
  if( geopolySkipSpace(&s)=='[' ){
    s.z++;
    while( geopolySkipSpace(&s)=='[' ){
      int ii = 0;
      char c;
      s.z++;
      if( s.nVertex>=s.nAlloc ){
        GeoCoord *aNew;
        s.nAlloc = s.nAlloc*2 + 16;
        aNew = sqlite3_realloc64(s.a, s.nAlloc*sizeof(GeoCoord)*2 );
        if( aNew==0 ){
          rc = SQLITE_NOMEM;
          s.nErr++;
          break;
        }
        s.a = aNew;
      }
      while( geopolyParseNumber(&s, ii<=1 ? &s.a[s.nVertex*2+ii] : 0) ){
        ii++;
        if( ii==2 ) s.nVertex++;
        c = geopolySkipSpace(&s);
        s.z++;
        if( c==',' ) continue;
        if( c==']' && ii>=2 ) break;
        s.nErr++;
        rc = SQLITE_ERROR;
        goto parse_json_err;
      }
      if( geopolySkipSpace(&s)==',' ){
        s.z++;
        continue;
      }
      break;
    }
    if( geopolySkipSpace(&s)==']'
     && s.nVertex>=4
     && s.a[0]==s.a[s.nVertex*2-2]
     && s.a[1]==s.a[s.nVertex*2-1]
     && (s.z++, geopolySkipSpace(&s)==0)
    ){
      GeoPoly *pOut;
      int x = 1;
      s.nVertex--;  /* Remove the redundant vertex at the end */
      pOut = sqlite3_malloc64( GEOPOLY_SZ((sqlite3_int64)s.nVertex) );
      x = 1;
      if( pOut==0 ) goto parse_json_err;
      pOut->nVertex = s.nVertex;
      memcpy(pOut->a, s.a, s.nVertex*2*sizeof(GeoCoord));
      pOut->hdr[0] = *(unsigned char*)&x;
      pOut->hdr[1] = (s.nVertex>>16)&0xff;
      pOut->hdr[2] = (s.nVertex>>8)&0xff;
      pOut->hdr[3] = s.nVertex&0xff;
      sqlite3_free(s.a);
      if( pRc ) *pRc = SQLITE_OK;
      return pOut;
    }else{
      s.nErr++;
      rc = SQLITE_ERROR;
    }
  }
parse_json_err:
  if( pRc ) *pRc = rc;
  sqlite3_free(s.a);
  return 0;
}