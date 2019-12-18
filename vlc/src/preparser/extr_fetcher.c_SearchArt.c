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
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_fetcher_t ;

/* Variables and functions */
 int CheckArt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvokeModule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int SearchArt( input_fetcher_t* fetcher, input_item_t* item, int scope)
{
    InvokeModule( fetcher, item, scope, "art finder" );
    return CheckArt( item );
}