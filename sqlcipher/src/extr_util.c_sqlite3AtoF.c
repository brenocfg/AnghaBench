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
typedef  int u8 ;
typedef  int i64 ;
typedef  int LONGDOUBLE_TYPE ;

/* Variables and functions */
 int INFINITY ; 
 int LARGEST_INT64 ; 
 int SQLITE_UTF16BE ; 
 int SQLITE_UTF16LE ; 
 int SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Atoi64 (char const*,double*,int,int) ; 
 scalar_t__ sqlite3Isdigit (char const) ; 
 scalar_t__ sqlite3Isspace (char const) ; 
 int sqlite3Pow10 (int) ; 

int sqlite3AtoF(const char *z, double *pResult, int length, u8 enc){
#ifndef SQLITE_OMIT_FLOATING_POINT
  int incr;
  const char *zEnd = z + length;
  /* sign * significand * (10 ^ (esign * exponent)) */
  int sign = 1;    /* sign of significand */
  i64 s = 0;       /* significand */
  int d = 0;       /* adjust exponent for shifting decimal point */
  int esign = 1;   /* sign of exponent */
  int e = 0;       /* exponent */
  int eValid = 1;  /* True exponent is either not used or is well-formed */
  double result;
  int nDigits = 0;
  int nonNum = 0;  /* True if input contains UTF16 with high byte non-zero */

  assert( enc==SQLITE_UTF8 || enc==SQLITE_UTF16LE || enc==SQLITE_UTF16BE );
  *pResult = 0.0;   /* Default return value, in case of an error */

  if( enc==SQLITE_UTF8 ){
    incr = 1;
  }else{
    int i;
    incr = 2;
    assert( SQLITE_UTF16LE==2 && SQLITE_UTF16BE==3 );
    for(i=3-enc; i<length && z[i]==0; i+=2){}
    nonNum = i<length;
    zEnd = &z[i^1];
    z += (enc&1);
  }

  /* skip leading spaces */
  while( z<zEnd && sqlite3Isspace(*z) ) z+=incr;
  if( z>=zEnd ) return 0;

  /* get sign of significand */
  if( *z=='-' ){
    sign = -1;
    z+=incr;
  }else if( *z=='+' ){
    z+=incr;
  }

  /* copy max significant digits to significand */
  while( z<zEnd && sqlite3Isdigit(*z) && s<((LARGEST_INT64-9)/10) ){
    s = s*10 + (*z - '0');
    z+=incr; nDigits++;
  }

  /* skip non-significant significand digits
  ** (increase exponent by d to shift decimal left) */
  while( z<zEnd && sqlite3Isdigit(*z) ){ z+=incr; nDigits++; d++; }
  if( z>=zEnd ) goto do_atof_calc;

  /* if decimal point is present */
  if( *z=='.' ){
    z+=incr;
    /* copy digits from after decimal to significand
    ** (decrease exponent by d to shift decimal right) */
    while( z<zEnd && sqlite3Isdigit(*z) ){
      if( s<((LARGEST_INT64-9)/10) ){
        s = s*10 + (*z - '0');
        d--;
      }
      z+=incr; nDigits++;
    }
  }
  if( z>=zEnd ) goto do_atof_calc;

  /* if exponent is present */
  if( *z=='e' || *z=='E' ){
    z+=incr;
    eValid = 0;

    /* This branch is needed to avoid a (harmless) buffer overread.  The 
    ** special comment alerts the mutation tester that the correct answer
    ** is obtained even if the branch is omitted */
    if( z>=zEnd ) goto do_atof_calc;              /*PREVENTS-HARMLESS-OVERREAD*/

    /* get sign of exponent */
    if( *z=='-' ){
      esign = -1;
      z+=incr;
    }else if( *z=='+' ){
      z+=incr;
    }
    /* copy digits to exponent */
    while( z<zEnd && sqlite3Isdigit(*z) ){
      e = e<10000 ? (e*10 + (*z - '0')) : 10000;
      z+=incr;
      eValid = 1;
    }
  }

  /* skip trailing spaces */
  while( z<zEnd && sqlite3Isspace(*z) ) z+=incr;

do_atof_calc:
  /* adjust exponent by d, and update sign */
  e = (e*esign) + d;
  if( e<0 ) {
    esign = -1;
    e *= -1;
  } else {
    esign = 1;
  }

  if( s==0 ) {
    /* In the IEEE 754 standard, zero is signed. */
    result = sign<0 ? -(double)0 : (double)0;
  } else {
    /* Attempt to reduce exponent.
    **
    ** Branches that are not required for the correct answer but which only
    ** help to obtain the correct answer faster are marked with special
    ** comments, as a hint to the mutation tester.
    */
    while( e>0 ){                                       /*OPTIMIZATION-IF-TRUE*/
      if( esign>0 ){
        if( s>=(LARGEST_INT64/10) ) break;             /*OPTIMIZATION-IF-FALSE*/
        s *= 10;
      }else{
        if( s%10!=0 ) break;                           /*OPTIMIZATION-IF-FALSE*/
        s /= 10;
      }
      e--;
    }

    /* adjust the sign of significand */
    s = sign<0 ? -s : s;

    if( e==0 ){                                         /*OPTIMIZATION-IF-TRUE*/
      result = (double)s;
    }else{
      /* attempt to handle extremely small/large numbers better */
      if( e>307 ){                                      /*OPTIMIZATION-IF-TRUE*/
        if( e<342 ){                                    /*OPTIMIZATION-IF-TRUE*/
          LONGDOUBLE_TYPE scale = sqlite3Pow10(e-308);
          if( esign<0 ){
            result = s / scale;
            result /= 1.0e+308;
          }else{
            result = s * scale;
            result *= 1.0e+308;
          }
        }else{ assert( e>=342 );
          if( esign<0 ){
            result = 0.0*s;
          }else{
#ifdef INFINITY
            result = INFINITY*s;
#else
            result = 1e308*1e308*s;  /* Infinity */
#endif
          }
        }
      }else{
        LONGDOUBLE_TYPE scale = sqlite3Pow10(e);
        if( esign<0 ){
          result = s / scale;
        }else{
          result = s * scale;
        }
      }
    }
  }

  /* store the result */
  *pResult = result;

  /* return true if number and no extra non-whitespace chracters after */
  return z==zEnd && nDigits>0 && eValid && nonNum==0;
#else
  return !sqlite3Atoi64(z, pResult, length, enc);
#endif /* SQLITE_OMIT_FLOATING_POINT */
}