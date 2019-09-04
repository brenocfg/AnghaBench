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
struct TYPE_5__ {scalar_t__ dwUsed; int /*<<< orphan*/  dwSize; scalar_t__ buffer; TYPE_1__* editstream; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwCookie; int /*<<< orphan*/  (* pfnCallback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  dwError; } ;
typedef  TYPE_2__ ME_InStream ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void
ME_StreamInFill(ME_InStream *stream)
{
  stream->editstream->dwError = stream->editstream->pfnCallback(stream->editstream->dwCookie,
                                                                (BYTE *)stream->buffer,
                                                                sizeof(stream->buffer),
                                                                (LONG *)&stream->dwSize);
  stream->dwUsed = 0;
}