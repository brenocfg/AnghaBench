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
struct TYPE_4__ {int dwStyle; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int UDS_ALIGNLEFT ; 
 int UDS_ALIGNRIGHT ; 
 scalar_t__ UPDOWN_IsBuddyEdit (TYPE_1__ const*) ; 

__attribute__((used)) static BOOL UPDOWN_HasBuddyBorder(const UPDOWN_INFO *infoPtr)
{
    return  ( ((infoPtr->dwStyle & (UDS_ALIGNLEFT | UDS_ALIGNRIGHT)) != 0) &&
	      UPDOWN_IsBuddyEdit(infoPtr) );
}