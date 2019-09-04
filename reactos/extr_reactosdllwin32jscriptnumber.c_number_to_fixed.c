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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  char WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int NUMBER_DTOA_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,double,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (int,char**) ; 
 int log10 (double) ; 
 int /*<<< orphan*/  number_to_str (double,char*,int,int*) ; 

__attribute__((used)) static inline jsstr_t *number_to_fixed(double val, int prec)
{
    WCHAR buf[NUMBER_DTOA_SIZE];
    int dec_point, size, buf_size, buf_pos;
    BOOL neg = FALSE;
    jsstr_t *ret;
    WCHAR *str;

    TRACE("%lf %d\n", val, prec);

    if(val < 0) {
        neg = TRUE;
        val = -val;
    }

    if(val >= 1)
        buf_size = log10(val)+prec+2;
    else
        buf_size = prec ? prec+1 : 2;
    if(buf_size > NUMBER_DTOA_SIZE)
        buf_size = NUMBER_DTOA_SIZE;

    number_to_str(val, buf, buf_size, &dec_point);
    dec_point++;
    size = 0;
    if(neg)
        size++;
    if(dec_point > 0)
        size += dec_point;
    else
        size++;
    if(prec)
        size += prec+1;

    ret = jsstr_alloc_buf(size, &str);
    if(!ret)
        return NULL;

    size = buf_pos = 0;
    if(neg)
        str[size++] = '-';
    if(dec_point > 0) {
        for(;buf_pos<buf_size-1 && dec_point; dec_point--)
            str[size++] = buf[buf_pos++];
    }else {
        str[size++] = '0';
    }
    for(; dec_point>0; dec_point--)
        str[size++] = '0';
    if(prec) {
        str[size++] = '.';

        for(; dec_point<0 && prec; dec_point++, prec--)
            str[size++] = '0';
        for(; buf_pos<buf_size-1 && prec; prec--)
            str[size++] = buf[buf_pos++];
        for(; prec; prec--) {
            str[size++] = '0';
        }
    }
    str[size++] = 0;
    return ret;
}