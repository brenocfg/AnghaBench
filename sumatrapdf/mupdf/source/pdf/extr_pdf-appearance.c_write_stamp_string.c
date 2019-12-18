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
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int strlen (char const*) ; 
 int /*<<< orphan*/  write_simple_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static void
write_stamp_string(fz_context *ctx, fz_buffer *buf, fz_font *font, const char *text)
{
	write_simple_string(ctx, buf, text, text+strlen(text));
}