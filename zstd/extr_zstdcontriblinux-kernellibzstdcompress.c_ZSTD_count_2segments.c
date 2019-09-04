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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * MIN (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 size_t const ZSTD_count (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static size_t ZSTD_count_2segments(const BYTE *ip, const BYTE *match, const BYTE *iEnd, const BYTE *mEnd, const BYTE *iStart)
{
	const BYTE *const vEnd = MIN(ip + (mEnd - match), iEnd);
	size_t const matchLength = ZSTD_count(ip, match, vEnd);
	if (match + matchLength != mEnd)
		return matchLength;
	return matchLength + ZSTD_count(ip + matchLength, iStart, iEnd);
}