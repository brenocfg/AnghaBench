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
struct TYPE_3__ {int rtfMinor; int /*<<< orphan*/  ansiCodePage; int /*<<< orphan*/  codePage; int /*<<< orphan*/  rtfParam; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ) ; 
#define  rtfAnsiCodePage 129 
#define  rtfUTF8RTF 128 

__attribute__((used)) static void
DocAttr(RTF_Info *info)
{
        TRACE("minor %d, param %d\n", info->rtfMinor, info->rtfParam);

        switch (info->rtfMinor)
        {
        case rtfAnsiCodePage:
                info->codePage = info->ansiCodePage = info->rtfParam;
                break;
        case rtfUTF8RTF:
                info->codePage = info->ansiCodePage = CP_UTF8;
                break;
        }
}