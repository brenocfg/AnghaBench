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
typedef  int /*<<< orphan*/  TRACKBAR_INFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TB_ENDTRACK ; 
 int /*<<< orphan*/  TRUE ; 
#define  VK_DOWN 135 
#define  VK_END 134 
#define  VK_HOME 133 
#define  VK_LEFT 132 
#define  VK_NEXT 131 
#define  VK_PRIOR 130 
#define  VK_RIGHT 129 
#define  VK_UP 128 
 int /*<<< orphan*/  notify_with_scroll (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL
TRACKBAR_KeyUp (const TRACKBAR_INFO *infoPtr, INT nVirtKey)
{
    switch (nVirtKey) {
    case VK_LEFT:
    case VK_UP:
    case VK_RIGHT:
    case VK_DOWN:
    case VK_NEXT:
    case VK_PRIOR:
    case VK_HOME:
    case VK_END:
        notify_with_scroll (infoPtr, TB_ENDTRACK);
    }
    return TRUE;
}