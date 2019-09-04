#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nZoomNumerator; int nZoomDenominator; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_RewrapRepaint (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
ME_SetZoom(ME_TextEditor *editor, int numerator, int denominator)
{
  /* TODO: Zoom images and objects */

  if (numerator == 0 && denominator == 0)
  {
    editor->nZoomNumerator = editor->nZoomDenominator = 0;
    return TRUE;
  }
  if (numerator <= 0 || denominator <= 0)
    return FALSE;
  if (numerator * 64 <= denominator || numerator / denominator >= 64)
    return FALSE;

  editor->nZoomNumerator = numerator;
  editor->nZoomDenominator = denominator;

  ME_RewrapRepaint(editor);
  return TRUE;
}