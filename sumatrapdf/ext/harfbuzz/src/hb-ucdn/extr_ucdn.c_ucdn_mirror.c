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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  to; int /*<<< orphan*/  from; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ MirrorPair ;

/* Variables and functions */
 int /*<<< orphan*/  BIDI_MIRROR_LEN ; 
 scalar_t__ bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_mp ; 
 int /*<<< orphan*/  mirror_pairs ; 

uint32_t ucdn_mirror(uint32_t code)
{
    MirrorPair mp = {0};
    MirrorPair *res;

    mp.from = code;
    res = (MirrorPair *) bsearch(&mp, mirror_pairs, BIDI_MIRROR_LEN,
                                sizeof(MirrorPair), compare_mp);

    if (res == NULL)
        return code;
    else
        return res->to;
}