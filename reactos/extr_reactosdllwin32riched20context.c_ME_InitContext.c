#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_10__ {int cx; int cy; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_13__ {TYPE_3__ rcView; scalar_t__ nAvailWidth; TYPE_2__ dpi; TYPE_1__ pt; TYPE_4__* editor; scalar_t__ hDC; } ;
struct TYPE_12__ {scalar_t__ nAvailWidth; TYPE_3__ rcFormat; } ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  TYPE_5__ ME_Context ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 void* GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 scalar_t__ ME_twips2pointsX (TYPE_5__*,scalar_t__) ; 

void ME_InitContext(ME_Context *c, ME_TextEditor *editor, HDC hDC)
{
  c->hDC = hDC;
  c->editor = editor;
  c->pt.x = 0;
  c->pt.y = 0;
  c->rcView = editor->rcFormat;
  if (hDC) {
      c->dpi.cx = GetDeviceCaps(hDC, LOGPIXELSX);
      c->dpi.cy = GetDeviceCaps(hDC, LOGPIXELSY);
  } else {
      c->dpi.cx = c->dpi.cy = 96;
  }
  if (editor->nAvailWidth)
      c->nAvailWidth = ME_twips2pointsX(c, editor->nAvailWidth);
  else
      c->nAvailWidth = c->rcView.right - c->rcView.left;
}