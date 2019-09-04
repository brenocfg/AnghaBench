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
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void format_clsid( WCHAR *buffer, const CLSID *clsid )
{
    static const WCHAR clsid_formatW[] = {'{','%','0','8','X','-','%','0','4','X','-','%','0','4','X','-',
                                    '%','0','2','X','%','0','2','X','-','%','0','2','X','%','0','2','X',
                                    '%','0','2','X','%','0','2','X','%','0','2','X','%','0','2','X','}',0};

    sprintfW( buffer, clsid_formatW, clsid->Data1, clsid->Data2, clsid->Data3,
              clsid->Data4[0], clsid->Data4[1], clsid->Data4[2], clsid->Data4[3],
              clsid->Data4[4], clsid->Data4[5], clsid->Data4[6], clsid->Data4[7] );

}