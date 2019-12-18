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
typedef  void* BOOL ;

/* Variables and functions */
 void* derived ; 
 void* notes ; 
 void* raw ; 
 void* sampletables ; 

void xml_write_init(BOOL n, BOOL t, BOOL r, BOOL d)
{
    /* Init file globals */
    notes = n;
    sampletables = t;
    raw = r;
    derived = d;
}