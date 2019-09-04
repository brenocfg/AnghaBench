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
struct TYPE_5__ {size_t nBands; TYPE_1__* bands; } ;
typedef  TYPE_2__ rbsize_result_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  cx; int /*<<< orphan*/  fStyle; int /*<<< orphan*/  rc; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void rbsize_add_band(rbsize_result_t *rbsr, int left, int top, int right, int bottom, DWORD fStyle, UINT cx)
{
    SetRect(&(rbsr->bands[rbsr->nBands].rc), left, top, right, bottom);
    rbsr->bands[rbsr->nBands].fStyle = fStyle;
    rbsr->bands[rbsr->nBands].cx = cx;
    rbsr->nBands++;
}