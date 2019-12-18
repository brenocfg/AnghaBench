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
typedef  int UINT32 ;
typedef  scalar_t__ INT32 ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__) ; 

__attribute__((used)) static BOOL colour_match(UINT32 x, UINT32 y)
{
    const INT32 tolerance = 8;

    const INT32 dr = abs((INT32)(x & 0x000000FF) - (INT32)(y & 0x000000FF));
    const INT32 dg = abs((INT32)((x & 0x0000FF00) >> 8) - (INT32)((y & 0x0000FF00) >> 8));
    const INT32 db = abs((INT32)((x & 0x00FF0000) >> 16) - (INT32)((y & 0x00FF0000) >> 16));

    return (dr <= tolerance && dg <= tolerance && db <= tolerance);
}