#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_14__ {int /*<<< orphan*/  ReadWaitQueue; } ;
struct TYPE_13__ {TYPE_3__* Object; } ;
struct TYPE_12__ {scalar_t__ Type; } ;
struct TYPE_10__ {scalar_t__ Flink; scalar_t__ Blink; } ;
struct TYPE_11__ {TYPE_1__ ListEntry; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PCONSOLE_SCREEN_BUFFER ;
typedef  TYPE_3__* PCONSOLE_IO_OBJECT ;
typedef  TYPE_4__* PCONSOLE_IO_HANDLE ;
typedef  TYPE_5__* PCONSOLE_INPUT_BUFFER ;

/* Variables and functions */
 scalar_t__ AdjustHandleCounts (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ConioDeleteScreenBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  CsrDereferenceWait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CsrNotifyWait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 scalar_t__ GRAPHICS_BUFFER ; 
 scalar_t__ INPUT_BUFFER ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,int) ; 
 scalar_t__ TEXTMODE_BUFFER ; 
 int /*<<< orphan*/  WaitAll ; 

__attribute__((used)) static VOID
ConSrvCloseHandleEntry(PCONSOLE_IO_HANDLE Entry)
{
    PCONSOLE_IO_OBJECT Object = Entry->Object;
    if (Object != NULL)
    {
        /// LOCK /// PCONSOLE Console = Object->Console;
        /// LOCK /// EnterCriticalSection(&Console->Lock);

        /*
         * If this is a input handle, notify and dereference
         * all the waits related to this handle.
         */
        if (Object->Type == INPUT_BUFFER)
        {
            PCONSOLE_INPUT_BUFFER InputBuffer = (PCONSOLE_INPUT_BUFFER)Object;

            /*
             * Wake up all the writing waiters related to this handle for this
             * input buffer, if any, then dereference them and purge them all
             * from the list.
             * To select them amongst all the waiters for this input buffer,
             * pass the handle pointer to the waiters, then they will check
             * whether or not they are related to this handle and if so, they
             * return.
             */
            CsrNotifyWait(&InputBuffer->ReadWaitQueue,
                          WaitAll,
                          NULL,
                          (PVOID)Entry);
            if (!IsListEmpty(&InputBuffer->ReadWaitQueue))
            {
                CsrDereferenceWait(&InputBuffer->ReadWaitQueue);
            }
        }

        /* If the last handle to a screen buffer is closed, delete it... */
        if (AdjustHandleCounts(Entry, -1) == 0)
        {
            if (Object->Type == TEXTMODE_BUFFER || Object->Type == GRAPHICS_BUFFER)
            {
                PCONSOLE_SCREEN_BUFFER Buffer = (PCONSOLE_SCREEN_BUFFER)Object;
                /* ...unless it's the only buffer left. Windows allows deletion
                 * even of the last buffer, but having to deal with a lack of
                 * any active buffer might be error-prone. */
                if (Buffer->ListEntry.Flink != Buffer->ListEntry.Blink)
                    ConioDeleteScreenBuffer(Buffer);
            }
            else if (Object->Type == INPUT_BUFFER)
            {
                DPRINT("Closing the input buffer\n");
            }
            else
            {
                DPRINT1("Invalid object type %d\n", Object->Type);
            }
        }

        /// LOCK /// LeaveCriticalSection(&Console->Lock);

        /* Invalidate (zero-out) this handle entry */
        // Entry->Object = NULL;
        // RtlZeroMemory(Entry, sizeof(*Entry));
    }
    RtlZeroMemory(Entry, sizeof(*Entry)); // Be sure the whole entry is invalidated.
}