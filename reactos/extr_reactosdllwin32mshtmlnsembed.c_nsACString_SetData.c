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
typedef  int /*<<< orphan*/  nsACString ;

/* Variables and functions */
 int /*<<< orphan*/  NS_CStringSetData (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PR_UINT32_MAX ; 

void nsACString_SetData(nsACString *str, const char *data)
{
    NS_CStringSetData(str, data, PR_UINT32_MAX);
}