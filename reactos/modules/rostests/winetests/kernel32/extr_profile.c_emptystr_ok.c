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
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  trace (char*,int,scalar_t__) ; 

__attribute__((used)) static BOOL emptystr_ok(CHAR emptystr[MAX_PATH])
{
    int i;

    for(i = 0;i < MAX_PATH;++i)
        if(emptystr[i] != 0)
        {
            trace("emptystr[%d] = %d\n",i,emptystr[i]);
            return FALSE;
        }

    return TRUE;
}