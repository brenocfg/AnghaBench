#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_word ;
struct TYPE_41__ {int used; int* dp; } ;
typedef  TYPE_1__ const mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int CHAR_BIT ; 
 int DIGIT_BIT ; 
 int MP_OKAY ; 
 int MP_WARRAY ; 
 int fast_mp_montgomery_reduce (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  mp_clear (TYPE_1__ const*) ; 
 int mp_copy (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_count_bits (TYPE_1__ const*) ; 
 int mp_dr_reduce (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  mp_dr_setup (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  mp_exch (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_init (TYPE_1__ const*) ; 
 int mp_mod (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_montgomery_calc_normalization (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_montgomery_reduce (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int mp_montgomery_setup (TYPE_1__ const*,int*) ; 
 int mp_mul (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_mulmod (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_reduce_2k (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int mp_reduce_2k_setup (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  mp_set (TYPE_1__ const*,int) ; 
 int mp_sqr (TYPE_1__ const*,TYPE_1__ const*) ; 

int
mp_exptmod_fast (const mp_int * G, const mp_int * X, mp_int * P, mp_int * Y, int redmode)
{
  mp_int  M[256], res;
  mp_digit buf, mp;
  int     err, bitbuf, bitcpy, bitcnt, mode, digidx, x, y, winsize;

  /* use a pointer to the reduction algorithm.  This allows us to use
   * one of many reduction algorithms without modding the guts of
   * the code with if statements everywhere.
   */
  int     (*redux)(mp_int*,const mp_int*,mp_digit);

  /* find window size */
  x = mp_count_bits (X);
  if (x <= 7) {
    winsize = 2;
  } else if (x <= 36) {
    winsize = 3;
  } else if (x <= 140) {
    winsize = 4;
  } else if (x <= 450) {
    winsize = 5;
  } else if (x <= 1303) {
    winsize = 6;
  } else if (x <= 3529) {
    winsize = 7;
  } else {
    winsize = 8;
  }

  /* init M array */
  /* init first cell */
  if ((err = mp_init(&M[1])) != MP_OKAY) {
     return err;
  }

  /* now init the second half of the array */
  for (x = 1<<(winsize-1); x < (1 << winsize); x++) {
    if ((err = mp_init(&M[x])) != MP_OKAY) {
      for (y = 1<<(winsize-1); y < x; y++) {
        mp_clear (&M[y]);
      }
      mp_clear(&M[1]);
      return err;
    }
  }

  /* determine and setup reduction code */
  if (redmode == 0) {
     /* now setup montgomery  */
     if ((err = mp_montgomery_setup (P, &mp)) != MP_OKAY) {
        goto __M;
     }

     /* automatically pick the comba one if available (saves quite a few calls/ifs) */
     if (((P->used * 2 + 1) < MP_WARRAY) &&
          P->used < (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
        redux = fast_mp_montgomery_reduce;
     } else {
        /* use slower baseline Montgomery method */
        redux = mp_montgomery_reduce;
     }
  } else if (redmode == 1) {
     /* setup DR reduction for moduli of the form B**k - b */
     mp_dr_setup(P, &mp);
     redux = mp_dr_reduce;
  } else {
     /* setup DR reduction for moduli of the form 2**k - b */
     if ((err = mp_reduce_2k_setup(P, &mp)) != MP_OKAY) {
        goto __M;
     }
     redux = mp_reduce_2k;
  }

  /* setup result */
  if ((err = mp_init (&res)) != MP_OKAY) {
    goto __M;
  }

  /* create M table
   *

   *
   * The first half of the table is not computed though accept for M[0] and M[1]
   */

  if (redmode == 0) {
     /* now we need R mod m */
     if ((err = mp_montgomery_calc_normalization (&res, P)) != MP_OKAY) {
       goto __RES;
     }

     /* now set M[1] to G * R mod m */
     if ((err = mp_mulmod (G, &res, P, &M[1])) != MP_OKAY) {
       goto __RES;
     }
  } else {
     mp_set(&res, 1);
     if ((err = mp_mod(G, P, &M[1])) != MP_OKAY) {
        goto __RES;
     }
  }

  /* compute the value at M[1<<(winsize-1)] by squaring M[1] (winsize-1) times */
  if ((err = mp_copy (&M[1], &M[1 << (winsize - 1)])) != MP_OKAY) {
    goto __RES;
  }

  for (x = 0; x < (winsize - 1); x++) {
    if ((err = mp_sqr (&M[1 << (winsize - 1)], &M[1 << (winsize - 1)])) != MP_OKAY) {
      goto __RES;
    }
    if ((err = redux (&M[1 << (winsize - 1)], P, mp)) != MP_OKAY) {
      goto __RES;
    }
  }

  /* create upper table */
  for (x = (1 << (winsize - 1)) + 1; x < (1 << winsize); x++) {
    if ((err = mp_mul (&M[x - 1], &M[1], &M[x])) != MP_OKAY) {
      goto __RES;
    }
    if ((err = redux (&M[x], P, mp)) != MP_OKAY) {
      goto __RES;
    }
  }

  /* set initial mode and bit cnt */
  mode   = 0;
  bitcnt = 1;
  buf    = 0;
  digidx = X->used - 1;
  bitcpy = 0;
  bitbuf = 0;

  for (;;) {
    /* grab next digit as required */
    if (--bitcnt == 0) {
      /* if digidx == -1 we are out of digits so break */
      if (digidx == -1) {
        break;
      }
      /* read next digit and reset bitcnt */
      buf    = X->dp[digidx--];
      bitcnt = DIGIT_BIT;
    }

    /* grab the next msb from the exponent */
    y     = (buf >> (DIGIT_BIT - 1)) & 1;
    buf <<= (mp_digit)1;

    /* if the bit is zero and mode == 0 then we ignore it
     * These represent the leading zero bits before the first 1 bit
     * in the exponent.  Technically this opt is not required but it
     * does lower the # of trivial squaring/reductions used
     */
    if (mode == 0 && y == 0) {
      continue;
    }

    /* if the bit is zero and mode == 1 then we square */
    if (mode == 1 && y == 0) {
      if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
        goto __RES;
      }
      if ((err = redux (&res, P, mp)) != MP_OKAY) {
        goto __RES;
      }
      continue;
    }

    /* else we add it to the window */
    bitbuf |= (y << (winsize - ++bitcpy));
    mode    = 2;

    if (bitcpy == winsize) {
      /* ok window is filled so square as required and multiply  */
      /* square first */
      for (x = 0; x < winsize; x++) {
        if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
          goto __RES;
        }
        if ((err = redux (&res, P, mp)) != MP_OKAY) {
          goto __RES;
        }
      }

      /* then multiply */
      if ((err = mp_mul (&res, &M[bitbuf], &res)) != MP_OKAY) {
        goto __RES;
      }
      if ((err = redux (&res, P, mp)) != MP_OKAY) {
        goto __RES;
      }

      /* empty window and reset */
      bitcpy = 0;
      bitbuf = 0;
      mode   = 1;
    }
  }

  /* if bits remain then square/multiply */
  if (mode == 2 && bitcpy > 0) {
    /* square then multiply if the bit is set */
    for (x = 0; x < bitcpy; x++) {
      if ((err = mp_sqr (&res, &res)) != MP_OKAY) {
        goto __RES;
      }
      if ((err = redux (&res, P, mp)) != MP_OKAY) {
        goto __RES;
      }

      /* get next bit of the window */
      bitbuf <<= 1;
      if ((bitbuf & (1 << winsize)) != 0) {
        /* then multiply */
        if ((err = mp_mul (&res, &M[1], &res)) != MP_OKAY) {
          goto __RES;
        }
        if ((err = redux (&res, P, mp)) != MP_OKAY) {
          goto __RES;
        }
      }
    }
  }

  if (redmode == 0) {
     /* fixup result if Montgomery reduction is used
      * recall that any value in a Montgomery system is
      * actually multiplied by R mod n.  So we have
      * to reduce one more time to cancel out the factor
      * of R.
      */
     if ((err = redux(&res, P, mp)) != MP_OKAY) {
       goto __RES;
     }
  }

  /* swap res with Y */
  mp_exch (&res, Y);
  err = MP_OKAY;
__RES:mp_clear (&res);
__M:
  mp_clear(&M[1]);
  for (x = 1<<(winsize-1); x < (1 << winsize); x++) {
    mp_clear (&M[x]);
  }
  return err;
}