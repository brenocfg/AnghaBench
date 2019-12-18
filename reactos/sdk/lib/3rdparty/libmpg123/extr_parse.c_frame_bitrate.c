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
struct TYPE_3__ {size_t lsf; int lay; size_t bitrate_index; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int*** tabsel_123 ; 

int frame_bitrate(mpg123_handle *fr)
{
	return tabsel_123[fr->lsf][fr->lay-1][fr->bitrate_index];
}