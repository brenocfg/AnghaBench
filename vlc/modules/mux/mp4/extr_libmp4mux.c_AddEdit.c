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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_64be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AddEdit(bo_t *elst,
                    int64_t i_movie_scaled_duration,
                    int64_t i_media_scaled_time,
                    bool b_64_ext)
{
    if(b_64_ext)
    {
        bo_add_64be(elst, i_movie_scaled_duration);
        bo_add_64be(elst, i_media_scaled_time);
    }
    else
    {
        bo_add_32be(elst, i_movie_scaled_duration);
        bo_add_32be(elst, i_media_scaled_time);
    }
    bo_add_16be(elst, 1);
    bo_add_16be(elst, 0);
}