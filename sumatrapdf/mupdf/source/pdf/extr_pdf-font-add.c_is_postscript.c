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
typedef  int /*<<< orphan*/  FT_Face ;

/* Variables and functions */
 int ft_font_file_kind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_postscript(FT_Face face)
{
	int kind = ft_font_file_kind(face);
	return (kind == 1 || kind == 3);
}