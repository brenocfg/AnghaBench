#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startup ;
typedef  int /*<<< orphan*/  classes ;
struct TYPE_7__ {int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; } ;
struct TYPE_6__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;

/* Variables and functions */
#define  ANIMATE_CLASSA 146 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
#define  DATETIMEPICK_CLASSA 145 
 int /*<<< orphan*/  FALSE ; 
#define  HOTKEY_CLASSA 144 
 int MAX_PATH ; 
#define  MONTHCAL_CLASSA 143 
#define  PROGRESS_CLASSA 142 
#define  REBARCLASSNAMEA 141 
#define  STATUSCLASSNAMEA 140 
#define  TOOLBARCLASSNAMEA 139 
#define  TOOLTIPS_CLASSA 138 
#define  TRACKBAR_CLASSA 137 
#define  UPDOWN_CLASSA 136 
#define  WC_COMBOBOXEXA 135 
#define  WC_HEADERA 134 
#define  WC_IPADDRESSA 133 
#define  WC_LISTVIEWA 132 
#define  WC_NATIVEFONTCTLA 131 
#define  WC_PAGESCROLLERA 130 
#define  WC_TABCONTROLA 129 
#define  WC_TREEVIEWA 128 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  winetest_get_mainargs (char***) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_comctl32_classes(void)
{
    char path_name[MAX_PATH];
    PROCESS_INFORMATION info;
    STARTUPINFOA startup;
    char **argv;
    int i;

    static const char *classes[] =
    {
        ANIMATE_CLASSA,
        WC_COMBOBOXEXA,
        DATETIMEPICK_CLASSA,
        WC_HEADERA,
        HOTKEY_CLASSA,
        WC_IPADDRESSA,
        WC_LISTVIEWA,
        MONTHCAL_CLASSA,
        WC_NATIVEFONTCTLA,
        WC_PAGESCROLLERA,
        PROGRESS_CLASSA,
        REBARCLASSNAMEA,
        STATUSCLASSNAMEA,
        "SysLink",
        WC_TABCONTROLA,
        TOOLBARCLASSNAMEA,
        TOOLTIPS_CLASSA,
        TRACKBAR_CLASSA,
        WC_TREEVIEWA,
        UPDOWN_CLASSA,
        "!Button",
        "!Edit",
        "!Static",
        "!Listbox",
        "!ComboBox",
        "!ComboLBox",
    };

    winetest_get_mainargs( &argv );
    for (i = 0; i < sizeof(classes) / sizeof(classes[0]); i++)
    {
        memset( &startup, 0, sizeof(startup) );
        startup.cb = sizeof( startup );
        sprintf( path_name, "%s class %s", argv[0], classes[i] );
        ok( CreateProcessA( NULL, path_name, NULL, NULL, FALSE, 0, NULL, NULL, &startup, &info ),
            "CreateProcess failed.\n" );
        winetest_wait_child_process( info.hProcess );
        CloseHandle( info.hProcess );
        CloseHandle( info.hThread );
    }
}