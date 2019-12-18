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
struct TYPE_4__ {float b; float c; float e; float a; float f; float d; } ;
typedef  TYPE_1__ fz_matrix ;

/* Variables and functions */
 scalar_t__ FLT_EPSILON ; 
 float MY_EPSILON ; 
 scalar_t__ fabsf (float) ; 

fz_matrix
fz_gridfit_matrix(int as_tiled, fz_matrix m)
{
	if (fabsf(m.b) < FLT_EPSILON && fabsf(m.c) < FLT_EPSILON)
	{
		if (as_tiled)
		{
			float f;
			/* Nearest boundary for left */
			f = (float)(int)(m.e + 0.5f);
			m.a += m.e - f; /* Adjust width for change */
			m.e = f;
			/* Nearest boundary for right (width really) */
			m.a = (float)(int)(m.a + 0.5f);
		}
		else if (m.a > 0)
		{
			float f;
			/* Adjust left hand side onto pixel boundary */
			f = (float)(int)(m.e);
			if (f - m.e > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves left */
			m.a += m.e - f; /* width gets wider as f <= m.e */
			m.e = f;
			/* Adjust right hand side onto pixel boundary */
			f = (float)(int)(m.a);
			if (m.a - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves right */
			m.a = f;
		}
		else if (m.a < 0)
		{
			float f;
			/* Adjust right hand side onto pixel boundary */
			f = (float)(int)(m.e);
			if (m.e - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves right */
			m.a += m.e - f; /* width gets wider (more -ve) */
			m.e = f;
			/* Adjust left hand side onto pixel boundary */
			f = (float)(int)(m.a);
			if (f - m.a > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves left */
			m.a = f;
		}
		if (as_tiled)
		{
			float f;
			/* Nearest boundary for top */
			f = (float)(int)(m.f + 0.5f);
			m.d += m.f - f; /* Adjust width for change */
			m.f = f;
			/* Nearest boundary for bottom (height really) */
			m.d = (float)(int)(m.d + 0.5f);
		}
		else if (m.d > 0)
		{
			float f;
			/* Adjust top onto pixel boundary */
			f = (float)(int)(m.f);
			if (f - m.f > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves upwards */
			m.d += m.f - f; /* width gets wider as f <= m.f */
			m.f = f;
			/* Adjust bottom onto pixel boundary */
			f = (float)(int)(m.d);
			if (m.d - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves down */
			m.d = f;
		}
		else if (m.d < 0)
		{
			float f;
			/* Adjust bottom onto pixel boundary */
			f = (float)(int)(m.f);
			if (m.f - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves down */
			m.d += m.f - f; /* width gets wider (more -ve) */
			m.f = f;
			/* Adjust top onto pixel boundary */
			f = (float)(int)(m.d);
			if (f - m.d > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves up */
			m.d = f;
		}
	}
	else if (fabsf(m.a) < FLT_EPSILON && fabsf(m.d) < FLT_EPSILON)
	{
		if (as_tiled)
		{
			float f;
			/* Nearest boundary for left */
			f = (float)(int)(m.e + 0.5f);
			m.b += m.e - f; /* Adjust width for change */
			m.e = f;
			/* Nearest boundary for right (width really) */
			m.b = (float)(int)(m.b + 0.5f);
		}
		else if (m.b > 0)
		{
			float f;
			/* Adjust left hand side onto pixel boundary */
			f = (float)(int)(m.f);
			if (f - m.f > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves left */
			m.b += m.f - f; /* width gets wider as f <= m.f */
			m.f = f;
			/* Adjust right hand side onto pixel boundary */
			f = (float)(int)(m.b);
			if (m.b - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves right */
			m.b = f;
		}
		else if (m.b < 0)
		{
			float f;
			/* Adjust right hand side onto pixel boundary */
			f = (float)(int)(m.f);
			if (m.f - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves right */
			m.b += m.f - f; /* width gets wider (more -ve) */
			m.f = f;
			/* Adjust left hand side onto pixel boundary */
			f = (float)(int)(m.b);
			if (f - m.b > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves left */
			m.b = f;
		}
		if (as_tiled)
		{
			float f;
			/* Nearest boundary for left */
			f = (float)(int)(m.f + 0.5f);
			m.c += m.f - f; /* Adjust width for change */
			m.f = f;
			/* Nearest boundary for right (width really) */
			m.c = (float)(int)(m.c + 0.5f);
		}
		else if (m.c > 0)
		{
			float f;
			/* Adjust top onto pixel boundary */
			f = (float)(int)(m.e);
			if (f - m.e > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves upwards */
			m.c += m.e - f; /* width gets wider as f <= m.e */
			m.e = f;
			/* Adjust bottom onto pixel boundary */
			f = (float)(int)(m.c);
			if (m.c - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves down */
			m.c = f;
		}
		else if (m.c < 0)
		{
			float f;
			/* Adjust bottom onto pixel boundary */
			f = (float)(int)(m.e);
			if (m.e - f > MY_EPSILON)
				f += 1.0f; /* Ensure it moves down */
			m.c += m.e - f; /* width gets wider (more -ve) */
			m.e = f;
			/* Adjust top onto pixel boundary */
			f = (float)(int)(m.c);
			if (f - m.c > MY_EPSILON)
				f -= 1.0f; /* Ensure it moves up */
			m.c = f;
		}
	}
	return m;
}