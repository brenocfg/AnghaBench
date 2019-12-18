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
typedef  int u_int64_t ;
typedef  int u_char ;

/* Variables and functions */
 int* T ; 
 int shift ; 

__attribute__((used)) static u_int64_t append8 (u_int64_t p, u_char m)
{
    return ((p << 8) | m) ^ T[p >> shift];
}