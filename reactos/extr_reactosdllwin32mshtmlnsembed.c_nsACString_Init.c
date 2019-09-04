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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NS_CStringContainerInit2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PR_UINT32_MAX ; 

BOOL nsACString_Init(nsACString *str, const char *data)
{
    return NS_SUCCEEDED(NS_CStringContainerInit2(str, data, PR_UINT32_MAX, 0));
}