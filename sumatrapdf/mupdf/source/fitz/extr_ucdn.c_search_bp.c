#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int member_2; int /*<<< orphan*/  from; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ BracketPair ;

/* Variables and functions */
 int /*<<< orphan*/  BIDI_BRACKET_LEN ; 
 int /*<<< orphan*/  bracket_pairs ; 
 scalar_t__ bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_bp ; 

__attribute__((used)) static BracketPair *search_bp(uint32_t code)
{
	BracketPair bp = {0,0,2};
	BracketPair *res;

	bp.from = code;
	res = (BracketPair *) bsearch(&bp, bracket_pairs, BIDI_BRACKET_LEN,
		sizeof(BracketPair), compare_bp);
	return res;
}