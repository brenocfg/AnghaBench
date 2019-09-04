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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  SS_CENTER 133 
#define  SS_LEFT 132 
#define  SS_LEFTNOWORDWRAP 131 
#define  SS_OWNERDRAW 130 
#define  SS_RIGHT 129 
#define  SS_SIMPLE 128 
 int SS_TYPEMASK ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL hasTextStyle( DWORD style )
{
    switch (style & SS_TYPEMASK)
    {
        case SS_SIMPLE:
        case SS_LEFT:
        case SS_LEFTNOWORDWRAP:
        case SS_CENTER:
        case SS_RIGHT:
        case SS_OWNERDRAW:
            return TRUE;
    }

    return FALSE;
}