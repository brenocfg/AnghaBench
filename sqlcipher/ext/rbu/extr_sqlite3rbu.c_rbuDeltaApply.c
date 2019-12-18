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
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 unsigned int rbuDeltaChecksum (char*,unsigned int) ; 
 unsigned int rbuDeltaGetInt (char const**,int*) ; 

__attribute__((used)) static int rbuDeltaApply(
  const char *zSrc,      /* The source or pattern file */
  int lenSrc,            /* Length of the source file */
  const char *zDelta,    /* Delta to apply to the pattern */
  int lenDelta,          /* Length of the delta */
  char *zOut             /* Write the output into this preallocated buffer */
){
  unsigned int limit;
  unsigned int total = 0;
#if RBU_ENABLE_DELTA_CKSUM
  char *zOrigOut = zOut;
#endif

  limit = rbuDeltaGetInt(&zDelta, &lenDelta);
  if( *zDelta!='\n' ){
    /* ERROR: size integer not terminated by "\n" */
    return -1;
  }
  zDelta++; lenDelta--;
  while( *zDelta && lenDelta>0 ){
    unsigned int cnt, ofst;
    cnt = rbuDeltaGetInt(&zDelta, &lenDelta);
    switch( zDelta[0] ){
      case '@': {
        zDelta++; lenDelta--;
        ofst = rbuDeltaGetInt(&zDelta, &lenDelta);
        if( lenDelta>0 && zDelta[0]!=',' ){
          /* ERROR: copy command not terminated by ',' */
          return -1;
        }
        zDelta++; lenDelta--;
        total += cnt;
        if( total>limit ){
          /* ERROR: copy exceeds output file size */
          return -1;
        }
        if( (int)(ofst+cnt) > lenSrc ){
          /* ERROR: copy extends past end of input */
          return -1;
        }
        memcpy(zOut, &zSrc[ofst], cnt);
        zOut += cnt;
        break;
      }
      case ':': {
        zDelta++; lenDelta--;
        total += cnt;
        if( total>limit ){
          /* ERROR:  insert command gives an output larger than predicted */
          return -1;
        }
        if( (int)cnt>lenDelta ){
          /* ERROR: insert count exceeds size of delta */
          return -1;
        }
        memcpy(zOut, zDelta, cnt);
        zOut += cnt;
        zDelta += cnt;
        lenDelta -= cnt;
        break;
      }
      case ';': {
        zDelta++; lenDelta--;
        zOut[0] = 0;
#if RBU_ENABLE_DELTA_CKSUM
        if( cnt!=rbuDeltaChecksum(zOrigOut, total) ){
          /* ERROR:  bad checksum */
          return -1;
        }
#endif
        if( total!=limit ){
          /* ERROR: generated size does not match predicted size */
          return -1;
        }
        return total;
      }
      default: {
        /* ERROR: unknown delta operator */
        return -1;
      }
    }
  }
  /* ERROR: unterminated delta */
  return -1;
}