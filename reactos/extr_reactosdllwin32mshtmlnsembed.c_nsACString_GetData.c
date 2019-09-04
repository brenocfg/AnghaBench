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
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  NS_CStringGetData (int /*<<< orphan*/  const*,char const**,int /*<<< orphan*/ *) ; 

UINT32 nsACString_GetData(const nsACString *str, const char **data)
{
    return NS_CStringGetData(str, data, NULL);
}