#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * hic; scalar_t__ bResize; int /*<<< orphan*/ * lpInFormat; int /*<<< orphan*/ * lpOutFormat; } ;
typedef  TYPE_1__ IGetFrameImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICDecompressEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICDecompressExEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AVIFILE_CloseCompressor(IGetFrameImpl *This)
{
  if (This->lpInFormat != This->lpOutFormat) {
    HeapFree(GetProcessHeap(), 0, This->lpOutFormat);
    This->lpOutFormat = NULL;
  }
  HeapFree(GetProcessHeap(), 0, This->lpInFormat);
  This->lpInFormat = NULL;
  if (This->hic != NULL) {
    if (This->bResize)
      ICDecompressExEnd(This->hic);
    else
      ICDecompressEnd(This->hic);
    ICClose(This->hic);
    This->hic = NULL;
  }
}