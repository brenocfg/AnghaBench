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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BUFFER_LEN ; 
 int /*<<< orphan*/  CharUpperW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pattern_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL pattern_imatch(LPCWSTR str, LPCWSTR pattern)
{
	WCHAR b1[BUFFER_LEN], b2[BUFFER_LEN];

	lstrcpyW(b1, str);
	lstrcpyW(b2, pattern);
	CharUpperW(b1);
	CharUpperW(b2);

	return pattern_match(b1, b2);
}