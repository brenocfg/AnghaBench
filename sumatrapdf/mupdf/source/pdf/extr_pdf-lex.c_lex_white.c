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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fz_unread_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ iswhite (int) ; 
 int lex_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lex_white(fz_context *ctx, fz_stream *f)
{
	int c;
	do {
		c = lex_byte(ctx, f);
	} while ((c <= 32) && (iswhite(c)));
	if (c != EOF)
		fz_unread_byte(ctx, f);
}