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

/* Variables and functions */
 int pointer_size ; 
 int /*<<< orphan*/  put_dword (unsigned int) ; 
 int /*<<< orphan*/  put_qword (unsigned int) ; 

void put_pword( unsigned int val )
{
    if (pointer_size == 8) put_qword( val );
    else put_dword( val );
}