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
struct TYPE_6__ {int /*<<< orphan*/ * ft_face; TYPE_1__* buffer; } ;
typedef  TYPE_2__ fz_font ;
struct TYPE_5__ {int len; } ;

/* Variables and functions */
 scalar_t__ is_postscript (int /*<<< orphan*/ *) ; 
 scalar_t__ is_truetype (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ttc (TYPE_2__*) ; 

int
pdf_font_writing_supported(fz_font *font)
{
	if (font->ft_face == NULL || font->buffer == NULL || font->buffer->len < 4)
		return 0;
	if (is_ttc(font))
		return 0;
	if (is_truetype(font->ft_face))
		return 1;
	if (is_postscript(font->ft_face))
		return 1;
	return 0;
}