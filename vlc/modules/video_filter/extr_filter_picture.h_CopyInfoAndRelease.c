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
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  picture_CopyProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline picture_t *CopyInfoAndRelease( picture_t *p_outpic, picture_t *p_inpic )
{
    picture_CopyProperties( p_outpic, p_inpic );

    picture_Release( p_inpic );

    return p_outpic;
}