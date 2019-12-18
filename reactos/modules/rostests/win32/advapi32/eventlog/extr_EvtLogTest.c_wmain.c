#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  TestEventsGeneration () ; 
 int /*<<< orphan*/  TestMyEventProvider () ; 
 int /*<<< orphan*/  _getch () ; 
 int /*<<< orphan*/  wprintf (char*) ; 
 int /*<<< orphan*/  wscanf (char*,int*) ; 

int wmain(int argc, WCHAR* argv[])
{
    UINT Choice = 0;

    wprintf(L"\n"
            L"EventLog API interactive tester for ReactOS\n"
            L"===========================================\n"
            L"\n");

ChoiceMenu:
    do
    {
        wprintf(L"What do you want to do:\n"
                L"1) Test events generation.\n"
                L"2) Test customized event provider.\n"
                L"\n"
                L"0) Quit the program.\n"
                L"(Enter the right number, or 0 to quit): ");
        wscanf(L"%lu", &Choice);
        wprintf(L"\n\n");
    } while ((Choice != 0) && (Choice != 1) && (Choice != 2));

    switch (Choice)
    {
        case 0:
            goto Quit;
            break;

        case 1:
            TestEventsGeneration();
            break;

        case 2:
            TestMyEventProvider();
            break;

        default:
            break;
    }
    wprintf(L"\n\n\n\n");
    goto ChoiceMenu;

Quit:
    wprintf(L"Press any key to quit...\n");
    _getch();
    return 0;
}