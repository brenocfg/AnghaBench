#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  add_text_to_macro (char const*,int) ; 
 int /*<<< orphan*/  stub1 (char const*,int) ; 
 scalar_t__ top_macro () ; 
 TYPE_1__* wpp_callbacks ; 

__attribute__((used)) static void put_buffer(const char *s, int len)
{
	if(top_macro())
		add_text_to_macro(s, len);
	else
		wpp_callbacks->write(s, len);
}