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
typedef  int __uint32_t ;
typedef  int __int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_WORDS (int,int,double) ; 
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 int /*<<< orphan*/  INSERT_WORDS (double,int,int) ; 
 double one ; 

double modf(double x, double *iptr)
{
	__int32_t i0,i1,j_0;
	__uint32_t i;
	EXTRACT_WORDS(i0,i1,x);
	j_0 = ((i0>>20)&0x7ff)-0x3ff;	/* exponent of x */
	if(j_0<20) {			/* integer part in high x */
	    if(j_0<0) {			/* |x|<1 */
	        INSERT_WORDS(*iptr,i0&0x80000000U,0);	/* *iptr = +-0 */
		return x;
	    } else {
		i = (0x000fffff)>>j_0;
		if(((i0&i)|i1)==0) {		/* x is integral */
		    __uint32_t high;
		    *iptr = x;
		    GET_HIGH_WORD(high,x);
		    INSERT_WORDS(x,high&0x80000000U,0);	/* return +-0 */
		    return x;
		} else {
		    INSERT_WORDS(*iptr,i0&(~i),0);
		    return x - *iptr;
		}
	    }
	} else if (j_0>51) {		/* no fraction part */
	    __uint32_t high;
	    *iptr = x*one;
	    GET_HIGH_WORD(high,x);
	    INSERT_WORDS(x,high&0x80000000U,0);	/* return +-0 */
	    return x;
	} else {			/* fraction part in low x */
	    i = ((__uint32_t)(0xffffffffU))>>(j_0-20);
	    if((i1&i)==0) { 		/* x is integral */
	        __uint32_t high;
		*iptr = x;
		GET_HIGH_WORD(high,x);
		INSERT_WORDS(x,high&0x80000000U,0);	/* return +-0 */
		return x;
	    } else {
	        INSERT_WORDS(*iptr,i0,i1&(~i));
		return x - *iptr;
	    }
	}
}