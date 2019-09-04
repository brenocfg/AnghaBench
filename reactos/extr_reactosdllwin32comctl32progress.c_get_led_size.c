#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Self; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ PROGRESS_INFO ;
typedef  int LONG ;
typedef  scalar_t__ HTHEME ;

/* Variables and functions */
 int /*<<< orphan*/  GetThemeInt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int MulDiv (scalar_t__,int,int) ; 
 int PBS_VERTICAL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMT_PROGRESSCHUNKSIZE ; 

__attribute__((used)) static inline int get_led_size ( const PROGRESS_INFO *infoPtr, LONG style,
                                 const RECT* rect )
{
    HTHEME theme = GetWindowTheme (infoPtr->Self);
    if (theme)
    {
        int chunkSize;
        if (SUCCEEDED( GetThemeInt( theme, 0, 0, TMT_PROGRESSCHUNKSIZE, &chunkSize )))
            return chunkSize;
    }

    if (style & PBS_VERTICAL)
        return MulDiv (rect->right - rect->left, 2, 3);
    else
        return MulDiv (rect->bottom - rect->top, 2, 3);
}