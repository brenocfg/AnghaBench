#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int from; } ;
typedef  TYPE_1__ BracketPair ;

/* Variables and functions */

__attribute__((used)) static int compare_bp(const void *a, const void *b)
{
    BracketPair *bpa = (BracketPair *)a;
    BracketPair *bpb = (BracketPair *)b;
    return bpa->from - bpb->from;
}