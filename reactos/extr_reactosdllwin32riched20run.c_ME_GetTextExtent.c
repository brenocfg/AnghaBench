#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ hDC; } ;
struct TYPE_8__ {scalar_t__ cy; scalar_t__ cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_2__ ME_Context ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HGDIOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  GetTextExtentPoint32W (scalar_t__,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ME_SelectStyleFont (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_UnselectStyleFont (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ME_GetTextExtent(ME_Context *c, LPCWSTR szText, int nChars, ME_Style *s, SIZE *size)
{
  HGDIOBJ hOldFont;
  if (c->hDC) {
    hOldFont = ME_SelectStyleFont(c, s);
    GetTextExtentPoint32W(c->hDC, szText, nChars, size);
    ME_UnselectStyleFont(c, s, hOldFont);
  } else {
    size->cx = 0;
    size->cy = 0;
  }
}