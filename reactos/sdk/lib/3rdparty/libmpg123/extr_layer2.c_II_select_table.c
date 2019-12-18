#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct al_table {int dummy; } ;
struct TYPE_7__ {int sampling_frequency; int stereo; size_t bitrate_index; int II_sblimit; struct al_table const* alloc; } ;
typedef  TYPE_3__ mpg123_handle ;
struct TYPE_6__ {int member_1; int member_2; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_10; int member_11; int member_12; int member_13; int member_14; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 struct al_table const* alloc_0 ; 
 struct al_table const* alloc_1 ; 
 struct al_table const* alloc_2 ; 
 struct al_table const* alloc_3 ; 
 struct al_table const* alloc_4 ; 

__attribute__((used)) static void II_select_table(mpg123_handle *fr)
{
	const int translate[3][2][16] =
	{
		{
			{ 0,2,2,2,2,2,2,0,0,0,1,1,1,1,1,0 },
			{ 0,2,2,0,0,0,1,1,1,1,1,1,1,1,1,0 }
		},
		{
			{ 0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0 },
			{ 0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0 }
		},
		{
			{ 0,3,3,3,3,3,3,0,0,0,1,1,1,1,1,0 },
			{ 0,3,3,0,0,0,1,1,1,1,1,1,1,1,1,0 }
		}
	};

	int table,sblim;
	const struct al_table *tables[5] = { alloc_0, alloc_1, alloc_2, alloc_3 , alloc_4 };
	const int sblims[5] = { 27 , 30 , 8, 12 , 30 };

	if(fr->sampling_frequency >= 3)	/* Or equivalent: (fr->lsf == 1) */
	table = 4;
	else
	table = translate[fr->sampling_frequency][2-fr->stereo][fr->bitrate_index];

	sblim = sblims[table];
	fr->alloc      = tables[table];
	fr->II_sblimit = sblim;
}