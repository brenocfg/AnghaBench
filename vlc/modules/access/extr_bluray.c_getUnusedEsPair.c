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
typedef  int /*<<< orphan*/  vlc_array_t ;
typedef  int /*<<< orphan*/  es_pair_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_pair_compare_Unused ; 
 int /*<<< orphan*/ * getEsPair (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static es_pair_t *getUnusedEsPair(vlc_array_t *p_array)
{
    return getEsPair(p_array, es_pair_compare_Unused, 0);
}