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
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ nExpectedNotify ; 
 scalar_t__ nReceivedNotify ; 
 scalar_t__ nUnexpectedNotify ; 

__attribute__((used)) static BOOL notifies_received(void)
{
    BOOL fRet = (nExpectedNotify == nReceivedNotify);
    nExpectedNotify = nReceivedNotify = 0;
    nUnexpectedNotify = 0;
    return fRet;
}