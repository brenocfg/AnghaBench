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
typedef  int sqlite3_int64 ;

/* Variables and functions */
 int LARGEST_INT64 ; 
 scalar_t__ totypeIsdigit (char const) ; 
 scalar_t__ totypeIsspace (char const) ; 

__attribute__((used)) static int totypeAtoF(const char *z, double *pResult, int length){
  const char *zEnd = z + length;
  /* sign * significand * (10 ^ (esign * exponent)) */
  int sign = 1;    /* sign of significand */
  sqlite3_int64 s = 0;       /* significand */
  int d = 0;       /* adjust exponent for shifting decimal point */
  int esign = 1;   /* sign of exponent */
  int e = 0;       /* exponent */
  int eValid = 1;  /* True exponent is either not used or is well-formed */
  double result;
  int nDigits = 0;
  int nonNum = 0;

  *pResult = 0.0;   /* Default return value, in case of an error */

  /* skip leading spaces */
  while( z<zEnd && totypeIsspace(*z) ) z++;
  if( z>=zEnd ) return 0;

  /* get sign of significand */
  if( *z=='-' ){
    sign = -1;
    z++;
  }else if( *z=='+' ){
    z++;
  }

  /* skip leading zeroes */
  while( z<zEnd && z[0]=='0' ) z++, nDigits++;

  /* copy max significant digits to significand */
  while( z<zEnd && totypeIsdigit(*z) && s<((LARGEST_INT64-9)/10) ){
    s = s*10 + (*z - '0');
    z++, nDigits++;
  }

  /* skip non-significant significand digits
  ** (increase exponent by d to shift decimal left) */
  while( z<zEnd && totypeIsdigit(*z) ) z++, nDigits++, d++;
  if( z>=zEnd ) goto totype_atof_calc;

  /* if decimal point is present */
  if( *z=='.' ){
    z++;
    /* copy digits from after decimal to significand
    ** (decrease exponent by d to shift decimal right) */
    while( z<zEnd && totypeIsdigit(*z) && s<((LARGEST_INT64-9)/10) ){
      s = s*10 + (*z - '0');
      z++, nDigits++, d--;
    }
    /* skip non-significant digits */
    while( z<zEnd && totypeIsdigit(*z) ) z++, nDigits++;
  }
  if( z>=zEnd ) goto totype_atof_calc;

  /* if exponent is present */
  if( *z=='e' || *z=='E' ){
    z++;
    eValid = 0;
    if( z>=zEnd ) goto totype_atof_calc;
    /* get sign of exponent */
    if( *z=='-' ){
      esign = -1;
      z++;
    }else if( *z=='+' ){
      z++;
    }
    /* copy digits to exponent */
    while( z<zEnd && totypeIsdigit(*z) ){
      e = e<10000 ? (e*10 + (*z - '0')) : 10000;
      z++;
      eValid = 1;
    }
  }

  /* skip trailing spaces */
  if( nDigits && eValid ){
    while( z<zEnd && totypeIsspace(*z) ) z++;
  }

totype_atof_calc:
  /* adjust exponent by d, and update sign */
  e = (e*esign) + d;
  if( e<0 ) {
    esign = -1;
    e *= -1;
  } else {
    esign = 1;
  }

  /* if 0 significand */
  if( !s ) {
    /* In the IEEE 754 standard, zero is signed.
    ** Add the sign if we've seen at least one digit */
    result = (sign<0 && nDigits) ? -(double)0 : (double)0;
  } else {
    /* attempt to reduce exponent */
    if( esign>0 ){
      while( s<(LARGEST_INT64/10) && e>0 ) e--,s*=10;
    }else{
      while( !(s%10) && e>0 ) e--,s/=10;
    }

    /* adjust the sign of significand */
    s = sign<0 ? -s : s;

    /* if exponent, scale significand as appropriate
    ** and store in result. */
    if( e ){
      double scale = 1.0;
      /* attempt to handle extremely small/large numbers better */
      if( e>307 && e<342 ){
        while( e%308 ) { scale *= 1.0e+1; e -= 1; }
        if( esign<0 ){
          result = s / scale;
          result /= 1.0e+308;
        }else{
          result = s * scale;
          result *= 1.0e+308;
        }
      }else if( e>=342 ){
        if( esign<0 ){
          result = 0.0*s;
        }else{
          result = 1e308*1e308*s;  /* Infinity */
        }
      }else{
        /* 1.0e+22 is the largest power of 10 than can be
        ** represented exactly. */
        while( e%22 ) { scale *= 1.0e+1; e -= 1; }
        while( e>0 ) { scale *= 1.0e+22; e -= 22; }
        if( esign<0 ){
          result = s / scale;
        }else{
          result = s * scale;
        }
      }
    } else {
      result = (double)s;
    }
  }

  /* store the result */
  *pResult = result;

  /* return true if number and no extra non-whitespace chracters after */
  return z>=zEnd && nDigits>0 && eValid && nonNum==0;
}