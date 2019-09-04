#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* apt; } ;
struct TYPE_9__ {int /*<<< orphan*/  oxid; scalar_t__ main; } ;
typedef  int DWORD ;
typedef  TYPE_1__ APARTMENT ;

/* Variables and functions */
 int COINIT_APARTMENTTHREADED ; 
 TYPE_1__* COM_CurrentApt () ; 
 TYPE_7__* COM_CurrentInfo () ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__* MTA ; 
 TYPE_1__* MainApartment ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  apartment_addref (TYPE_1__*) ; 
 void* apartment_construct (int) ; 
 int /*<<< orphan*/  apartment_createwindowifneeded (TYPE_1__*) ; 
 int /*<<< orphan*/  csApartment ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static APARTMENT *apartment_get_or_create(DWORD model)
{
    APARTMENT *apt = COM_CurrentApt();

    if (!apt)
    {
        if (model & COINIT_APARTMENTTHREADED)
        {
            EnterCriticalSection(&csApartment);

            apt = apartment_construct(model);
            if (!MainApartment)
            {
                MainApartment = apt;
                apt->main = TRUE;
                TRACE("Created main-threaded apartment with OXID %s\n", wine_dbgstr_longlong(apt->oxid));
            }

            LeaveCriticalSection(&csApartment);

            if (apt->main)
                apartment_createwindowifneeded(apt);
        }
        else
        {
            EnterCriticalSection(&csApartment);

            /* The multi-threaded apartment (MTA) contains zero or more threads interacting
             * with free threaded (ie thread safe) COM objects. There is only ever one MTA
             * in a process */
            if (MTA)
            {
                TRACE("entering the multithreaded apartment %s\n", wine_dbgstr_longlong(MTA->oxid));
                apartment_addref(MTA);
            }
            else
                MTA = apartment_construct(model);

            apt = MTA;

            LeaveCriticalSection(&csApartment);
        }
        COM_CurrentInfo()->apt = apt;
    }

    return apt;
}