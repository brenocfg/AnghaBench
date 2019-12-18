#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int increment_t ;
struct TYPE_3__ {int b_current; int channels; double* coeffs; double* buffer; int /*<<< orphan*/  coeff_half_len; } ;
typedef  TYPE_1__ SINC_FILTER ;

/* Variables and functions */
 int MAKE_INCREMENT_T (int /*<<< orphan*/ ) ; 
 double fp_to_double (int) ; 
 int fp_to_int (int) ; 
 int int_to_fp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
calc_output_hex (SINC_FILTER *filter, increment_t increment, increment_t start_filter_index, double scale, float * output)
{	double		fraction, left [6], right [6], icoeff ;
	increment_t	filter_index, max_filter_index ;
	int			data_index, coeff_count, indx ;

	/* Convert input parameters into fixed point. */
	max_filter_index = int_to_fp (filter->coeff_half_len) ;

	/* First apply the left half of the filter. */
	filter_index = start_filter_index ;
	coeff_count = (max_filter_index - filter_index) / increment ;
	filter_index = filter_index + coeff_count * increment ;
	data_index = filter->b_current - filter->channels * coeff_count ;

	left [0] = left [1] = left [2] = left [3] = left [4] = left [5] = 0.0 ;
	do
	{	fraction = fp_to_double (filter_index) ;
		indx = fp_to_int (filter_index) ;

		icoeff = filter->coeffs [indx] + fraction * (filter->coeffs [indx + 1] - filter->coeffs [indx]) ;

		left [0] += icoeff * filter->buffer [data_index] ;
		left [1] += icoeff * filter->buffer [data_index + 1] ;
		left [2] += icoeff * filter->buffer [data_index + 2] ;
		left [3] += icoeff * filter->buffer [data_index + 3] ;
		left [4] += icoeff * filter->buffer [data_index + 4] ;
		left [5] += icoeff * filter->buffer [data_index + 5] ;

		filter_index -= increment ;
		data_index = data_index + 6 ;
		}
	while (filter_index >= MAKE_INCREMENT_T (0)) ;

	/* Now apply the right half of the filter. */
	filter_index = increment - start_filter_index ;
	coeff_count = (max_filter_index - filter_index) / increment ;
	filter_index = filter_index + coeff_count * increment ;
	data_index = filter->b_current + filter->channels * (1 + coeff_count) ;

	right [0] = right [1] = right [2] = right [3] = right [4] = right [5] = 0.0 ;
	do
	{	fraction = fp_to_double (filter_index) ;
		indx = fp_to_int (filter_index) ;

		icoeff = filter->coeffs [indx] + fraction * (filter->coeffs [indx + 1] - filter->coeffs [indx]) ;

		right [0] += icoeff * filter->buffer [data_index] ;
		right [1] += icoeff * filter->buffer [data_index + 1] ;
		right [2] += icoeff * filter->buffer [data_index + 2] ;
		right [3] += icoeff * filter->buffer [data_index + 3] ;
		right [4] += icoeff * filter->buffer [data_index + 4] ;
		right [5] += icoeff * filter->buffer [data_index + 5] ;

		filter_index -= increment ;
		data_index = data_index - 6 ;
		}
	while (filter_index > MAKE_INCREMENT_T (0)) ;

	output [0] = scale * (left [0] + right [0]) ;
	output [1] = scale * (left [1] + right [1]) ;
	output [2] = scale * (left [2] + right [2]) ;
	output [3] = scale * (left [3] + right [3]) ;
	output [4] = scale * (left [4] + right [4]) ;
	output [5] = scale * (left [5] + right [5]) ;
}