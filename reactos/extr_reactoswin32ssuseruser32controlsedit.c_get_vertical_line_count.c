#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bottom; int top; } ;
struct TYPE_5__ {int line_height; TYPE_1__ format_rect; } ;
typedef  int INT ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 int max (int,int) ; 

__attribute__((used)) static inline INT get_vertical_line_count(EDITSTATE *es)
{
	INT vlc = (es->format_rect.bottom - es->format_rect.top) / es->line_height;
	return max(1,vlc);
}