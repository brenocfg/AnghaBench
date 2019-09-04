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
typedef  int uint32_t ;

/* Variables and functions */
 int LP_ENCODING_12BIT_STR_LEN (unsigned char*) ; 
 int LP_ENCODING_32BIT_STR_LEN (unsigned char*) ; 
 int LP_ENCODING_6BIT_STR_LEN (unsigned char*) ; 
 scalar_t__ LP_ENCODING_IS_12BIT_STR (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_13BIT_INT (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_16BIT_INT (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_24BIT_INT (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_32BIT_INT (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_32BIT_STR (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_64BIT_INT (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_6BIT_STR (unsigned char) ; 
 scalar_t__ LP_ENCODING_IS_7BIT_UINT (unsigned char) ; 
 unsigned char LP_EOF ; 

uint32_t lpCurrentEncodedSize(unsigned char *p) {
    if (LP_ENCODING_IS_7BIT_UINT(p[0])) return 1;
    if (LP_ENCODING_IS_6BIT_STR(p[0])) return 1+LP_ENCODING_6BIT_STR_LEN(p);
    if (LP_ENCODING_IS_13BIT_INT(p[0])) return 2;
    if (LP_ENCODING_IS_16BIT_INT(p[0])) return 3;
    if (LP_ENCODING_IS_24BIT_INT(p[0])) return 4;
    if (LP_ENCODING_IS_32BIT_INT(p[0])) return 5;
    if (LP_ENCODING_IS_64BIT_INT(p[0])) return 9;
    if (LP_ENCODING_IS_12BIT_STR(p[0])) return 2+LP_ENCODING_12BIT_STR_LEN(p);
    if (LP_ENCODING_IS_32BIT_STR(p[0])) return 5+LP_ENCODING_32BIT_STR_LEN(p);
    if (p[0] == LP_EOF) return 1;
    return 0;
}