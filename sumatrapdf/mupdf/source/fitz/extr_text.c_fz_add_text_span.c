#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ a; scalar_t__ b; scalar_t__ c; scalar_t__ d; } ;
struct TYPE_10__ {int wmode; int bidi_level; scalar_t__ markup_dir; scalar_t__ language; struct TYPE_10__* next; TYPE_1__ trm; int /*<<< orphan*/ * font; } ;
typedef  TYPE_2__ fz_text_span ;
typedef  scalar_t__ fz_text_language ;
struct TYPE_11__ {TYPE_2__* tail; TYPE_2__* head; } ;
typedef  TYPE_3__ fz_text ;
struct TYPE_12__ {scalar_t__ a; scalar_t__ b; scalar_t__ c; scalar_t__ d; } ;
typedef  TYPE_4__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  scalar_t__ fz_bidi_direction ;

/* Variables and functions */
 void* fz_new_text_span (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__,TYPE_4__) ; 

__attribute__((used)) static fz_text_span *
fz_add_text_span(fz_context *ctx, fz_text *text, fz_font *font, int wmode, int bidi_level, fz_bidi_direction markup_dir, fz_text_language language, fz_matrix trm)
{
	if (!text->tail)
	{
		text->head = text->tail = fz_new_text_span(ctx, font, wmode, bidi_level, markup_dir, language, trm);
	}
	else if (text->tail->font != font ||
		text->tail->wmode != wmode ||
		text->tail->bidi_level != bidi_level ||
		text->tail->markup_dir != markup_dir ||
		text->tail->language != language ||
		text->tail->trm.a != trm.a ||
		text->tail->trm.b != trm.b ||
		text->tail->trm.c != trm.c ||
		text->tail->trm.d != trm.d)
	{
		text->tail = text->tail->next = fz_new_text_span(ctx, font, wmode, bidi_level, markup_dir, language, trm);
	}
	return text->tail;
}