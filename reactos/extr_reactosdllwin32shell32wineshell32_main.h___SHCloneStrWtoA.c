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

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ SHAlloc (int) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void __SHCloneStrWtoA(char **target, const WCHAR *source)
{
	int len = WideCharToMultiByte(CP_ACP, 0, source, -1, NULL, 0, NULL, NULL);
	*target = (char *)SHAlloc(len);
	WideCharToMultiByte(CP_ACP, 0, source, -1, *target, len, NULL, NULL);
}