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
typedef  scalar_t__ GLushort ;
typedef  float GLshort ;
typedef  int GLint ;

/* Variables and functions */
 scalar_t__ __GLU_SWAP_2_BYTES (char const*) ; 
 int floor (float) ; 
 int /*<<< orphan*/  halveImage_short (int,int,int,float const*,float*,int,int,int,int) ; 

__attribute__((used)) static void scale_internal_short(GLint components, GLint widthin,
			   GLint heightin, const GLshort *datain,
			   GLint widthout, GLint heightout,
			   GLshort *dataout, GLint element_size,
			   GLint ysize, GLint group_size,
			   GLint myswap_bytes)
{
    float convx;
    float convy;
    float percent;
    /* Max components in a format is 4, so... */
    float totals[4];
    float area;
    int i,j,k,xindex;

    const char *temp, *temp0;
    const char *temp_index;
    int outindex;

    int lowx_int, highx_int, lowy_int, highy_int;
    float x_percent, y_percent;
    float lowx_float, highx_float, lowy_float, highy_float;
    float convy_float, convx_float;
    int convy_int, convx_int;
    int l, m;
    const char *left, *right;

    GLushort swapbuf;	/* unsigned buffer */

    if (widthin == widthout*2 && heightin == heightout*2) {
	halveImage_short(components, widthin, heightin,
	(const GLshort *)datain, (GLshort *)dataout,
	element_size, ysize, group_size, myswap_bytes);
	return;
    }
    convy = (float) heightin/heightout;
    convx = (float) widthin/widthout;
    convy_int = floor(convy);
    convy_float = convy - convy_int;
    convx_int = floor(convx);
    convx_float = convx - convx_int;

    area = convx * convy;

    lowy_int = 0;
    lowy_float = 0;
    highy_int = convy_int;
    highy_float = convy_float;

    for (i = 0; i < heightout; i++) {
        /* Clamp here to be sure we don't read beyond input buffer. */
        if (highy_int >= heightin)
            highy_int = heightin - 1;
	lowx_int = 0;
	lowx_float = 0;
	highx_int = convx_int;
	highx_float = convx_float;

	for (j = 0; j < widthout; j++) {
	    /*
	    ** Ok, now apply box filter to box that goes from (lowx, lowy)
	    ** to (highx, highy) on input data into this pixel on output
	    ** data.
	    */
	    totals[0] = totals[1] = totals[2] = totals[3] = 0.0;

	    /* calculate the value for pixels in the 1st row */
	    xindex = lowx_int*group_size;
	    if((highy_int>lowy_int) && (highx_int>lowx_int)) {

		y_percent = 1-lowy_float;
		temp = (const char *)datain + xindex + lowy_int * ysize;
		percent = y_percent * (1-lowx_float);
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
		left = temp;
		for(l = lowx_int+1; l < highx_int; l++) {
		    temp += group_size;
		    for (k = 0, temp_index = temp; k < components;
			 k++, temp_index += element_size) {
			if (myswap_bytes) {
			    swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			    totals[k] += *(const GLshort*)&swapbuf * y_percent;
			} else {
			    totals[k] += *(const GLshort*)temp_index * y_percent;
			}
		    }
		}
		temp += group_size;
		right = temp;
		percent = y_percent * highx_float;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}

		/* calculate the value for pixels in the last row */
		y_percent = highy_float;
		percent = y_percent * (1-lowx_float);
		temp = (const char *)datain + xindex + highy_int * ysize;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
		for(l = lowx_int+1; l < highx_int; l++) {
		    temp += group_size;
		    for (k = 0, temp_index = temp; k < components;
			 k++, temp_index += element_size) {
			if (myswap_bytes) {
			    swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			    totals[k] += *(const GLshort*)&swapbuf * y_percent;
			} else {
			    totals[k] += *(const GLshort*)temp_index * y_percent;
			}
		    }
		}
		temp += group_size;
		percent = y_percent * highx_float;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}

		/* calculate the value for pixels in the 1st and last column */
		for(m = lowy_int+1; m < highy_int; m++) {
		    left += ysize;
		    right += ysize;
		    for (k = 0; k < components;
			 k++, left += element_size, right += element_size) {
			if (myswap_bytes) {
			    swapbuf = __GLU_SWAP_2_BYTES(left);
			    totals[k] += *(const GLshort*)&swapbuf * (1-lowx_float);
			    swapbuf = __GLU_SWAP_2_BYTES(right);
			    totals[k] += *(const GLshort*)&swapbuf * highx_float;
			} else {
			    totals[k] += *(const GLshort*)left * (1-lowx_float)
				       + *(const GLshort*)right * highx_float;
			}
		    }
		}
	    } else if (highy_int > lowy_int) {
		x_percent = highx_float - lowx_float;
		percent = (1-lowy_float)*x_percent;
		temp = (const char *)datain + xindex + lowy_int*ysize;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
		for(m = lowy_int+1; m < highy_int; m++) {
		    temp += ysize;
		    for (k = 0, temp_index = temp; k < components;
			 k++, temp_index += element_size) {
			if (myswap_bytes) {
			    swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			    totals[k] += *(const GLshort*)&swapbuf * x_percent;
			} else {
			    totals[k] += *(const GLshort*)temp_index * x_percent;
			}
		    }
		}
		percent = x_percent * highy_float;
		temp += ysize;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
	    } else if (highx_int > lowx_int) {
		y_percent = highy_float - lowy_float;
		percent = (1-lowx_float)*y_percent;

	     temp = (const char *)datain + xindex + lowy_int*ysize;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
		for (l = lowx_int+1; l < highx_int; l++) {
		    temp += group_size;
		    for (k = 0, temp_index = temp; k < components;
			 k++, temp_index += element_size) {
			if (myswap_bytes) {
			    swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			    totals[k] += *(const GLshort*)&swapbuf * y_percent;
			} else {
			    totals[k] += *(const GLshort*)temp_index * y_percent;
			}
		    }
		}
		temp += group_size;
		percent = y_percent * highx_float;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
	    } else {
		percent = (highy_float-lowy_float)*(highx_float-lowx_float);
		temp = (const char *)datain + xindex + lowy_int * ysize;
		for (k = 0, temp_index = temp; k < components;
		     k++, temp_index += element_size) {
		    if (myswap_bytes) {
			swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			totals[k] += *(const GLshort*)&swapbuf * percent;
		    } else {
			totals[k] += *(const GLshort*)temp_index * percent;
		    }
		}
	    }

	    /* this is for the pixels in the body */
	    temp0 = (const char *)datain + xindex + group_size +
		 (lowy_int+1)*ysize;
	    for (m = lowy_int+1; m < highy_int; m++) {
		temp = temp0;
		for(l = lowx_int+1; l < highx_int; l++) {
		    for (k = 0, temp_index = temp; k < components;
			 k++, temp_index += element_size) {
			if (myswap_bytes) {
			    swapbuf = __GLU_SWAP_2_BYTES(temp_index);
			    totals[k] += *(const GLshort*)&swapbuf;
			} else {
			    totals[k] += *(const GLshort*)temp_index;
			}
		    }
		    temp += group_size;
		}
		temp0 += ysize;
	    }

	    outindex = (j + (i * widthout)) * components;
	    for (k = 0; k < components; k++) {
		dataout[outindex + k] = totals[k]/area;
		/*printf("totals[%d] = %f\n", k, totals[k]);*/
	    }
	    lowx_int = highx_int;
	    lowx_float = highx_float;
	    highx_int += convx_int;
	    highx_float += convx_float;
	    if(highx_float > 1) {
		highx_float -= 1.0;
		highx_int++;
	    }
	}
	lowy_int = highy_int;
	lowy_float = highy_float;
	highy_int += convy_int;
	highy_float += convy_float;
	if(highy_float > 1) {
	    highy_float -= 1.0;
	    highy_int++;
	}
    }
}