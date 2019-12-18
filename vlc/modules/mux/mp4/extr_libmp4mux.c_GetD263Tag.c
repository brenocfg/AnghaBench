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
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_fourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * box_new (char*) ; 

__attribute__((used)) static bo_t *GetD263Tag(void)
{
    bo_t *d263 = box_new("d263");
    if(!d263)
        return NULL;

    bo_add_fourcc(d263, "VLC ");
    bo_add_16be(d263, 0xa);
    bo_add_8(d263, 0);

    return d263;
}