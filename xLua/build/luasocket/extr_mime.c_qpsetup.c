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
typedef  int UC ;

/* Variables and functions */
 int QP_CR ; 
 int QP_IF_LAST ; 
 int QP_PLAIN ; 
 int QP_QUOTED ; 

__attribute__((used)) static void qpsetup(UC *cl, UC *unbase)
{
    int i;
    for (i = 0; i < 256; i++) cl[i] = QP_QUOTED;
    for (i = 33; i <= 60; i++) cl[i] = QP_PLAIN;
    for (i = 62; i <= 126; i++) cl[i] = QP_PLAIN;
    cl['\t'] = QP_IF_LAST; 
    cl[' '] = QP_IF_LAST;
    cl['\r'] = QP_CR;
    for (i = 0; i < 256; i++) unbase[i] = 255;
    unbase['0'] = 0; unbase['1'] = 1; unbase['2'] = 2;
    unbase['3'] = 3; unbase['4'] = 4; unbase['5'] = 5;
    unbase['6'] = 6; unbase['7'] = 7; unbase['8'] = 8;
    unbase['9'] = 9; unbase['A'] = 10; unbase['a'] = 10;
    unbase['B'] = 11; unbase['b'] = 11; unbase['C'] = 12;
    unbase['c'] = 12; unbase['D'] = 13; unbase['d'] = 13;
    unbase['E'] = 14; unbase['e'] = 14; unbase['F'] = 15;
    unbase['f'] = 15;
}