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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UCHAR ;
struct TYPE_4__ {int Extra; void* VertCounter; void* HorzCounter; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__* PMOUSE_PACKET ;

/* Variables and functions */
 int ButtonState ; 
 int FROM_LEFT_1ST_BUTTON_PRESSED ; 
 int FROM_LEFT_2ND_BUTTON_PRESSED ; 
 int FROM_LEFT_3RD_BUTTON_PRESSED ; 
 int FROM_LEFT_4TH_BUTTON_PRESSED ; 
 int /*<<< orphan*/  HorzCounter ; 
 int /*<<< orphan*/  INFINITE ; 
 void* LOBYTE (int /*<<< orphan*/ ) ; 
 int MOUSE_4TH_BUTTON ; 
 int MOUSE_5TH_BUTTON ; 
 int /*<<< orphan*/  MOUSE_ALWAYS_SET ; 
 int /*<<< orphan*/  MOUSE_LEFT_BUTTON ; 
 int /*<<< orphan*/  MOUSE_MAX ; 
 int /*<<< orphan*/  MOUSE_MIDDLE_BUTTON ; 
 int /*<<< orphan*/  MOUSE_RIGHT_BUTTON ; 
 int /*<<< orphan*/  MOUSE_X_OVERFLOW ; 
 int /*<<< orphan*/  MOUSE_X_SIGN ; 
 int /*<<< orphan*/  MOUSE_Y_OVERFLOW ; 
 int /*<<< orphan*/  MOUSE_Y_SIGN ; 
 int MouseId ; 
 int /*<<< orphan*/  MouseMutex ; 
 int /*<<< orphan*/  MouseResetCounters () ; 
 int RIGHTMOST_BUTTON_PRESSED ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 scalar_t__ ScrollCounter ; 
 int /*<<< orphan*/  VertCounter ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID MouseGetPacket(PMOUSE_PACKET Packet)
{
    /* Clear the packet */
    RtlZeroMemory(Packet, sizeof(*Packet));

    /* Acquire the mutex */
    WaitForSingleObject(MouseMutex, INFINITE);

    Packet->Flags |= MOUSE_ALWAYS_SET;

    /* Set the sign flags */
    if (HorzCounter < 0)
    {
        Packet->Flags |= MOUSE_X_SIGN;
        HorzCounter = -HorzCounter;
    }

    if (VertCounter < 0)
    {
        Packet->Flags |= MOUSE_Y_SIGN;
        VertCounter = -VertCounter;
    }

    /* Check for horizontal overflows */
    if (HorzCounter > MOUSE_MAX)
    {
        HorzCounter = MOUSE_MAX;
        Packet->Flags |= MOUSE_X_OVERFLOW;
    }

    /* Check for vertical overflows */
    if (VertCounter > MOUSE_MAX)
    {
        VertCounter = MOUSE_MAX;
        Packet->Flags |= MOUSE_Y_OVERFLOW;
    }

    /* Set the button flags */
    if (ButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) Packet->Flags |= MOUSE_LEFT_BUTTON;
    if (ButtonState & FROM_LEFT_2ND_BUTTON_PRESSED) Packet->Flags |= MOUSE_MIDDLE_BUTTON;
    if (ButtonState &     RIGHTMOST_BUTTON_PRESSED) Packet->Flags |= MOUSE_RIGHT_BUTTON;

    if (MouseId == 4)
    {
        if (ButtonState & FROM_LEFT_3RD_BUTTON_PRESSED) Packet->Extra |= MOUSE_4TH_BUTTON;
        if (ButtonState & FROM_LEFT_4TH_BUTTON_PRESSED) Packet->Extra |= MOUSE_5TH_BUTTON;
    }

    if (MouseId >= 3)
    {
        /* Set the scroll counter */
        Packet->Extra |= ((UCHAR)ScrollCounter & 0x0F);
    }

    /* Store the counters in the packet */
    Packet->HorzCounter = LOBYTE(HorzCounter);
    Packet->VertCounter = LOBYTE(VertCounter);

    /* Reset the counters */
    MouseResetCounters();

    /* Release the mutex */
    ReleaseMutex(MouseMutex);
}