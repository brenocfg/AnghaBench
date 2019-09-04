#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info2 ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_5__ {int left; int top; int right; int bottom; } ;
struct TYPE_6__ {scalar_t__ dwStart; scalar_t__ wPriority; scalar_t__ wLanguage; scalar_t__ dwScale; scalar_t__ dwRate; int dwQuality; TYPE_1__ rcFrame; } ;
typedef  int /*<<< orphan*/ * PAVISTREAM ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ AVISTREAMINFOA ;

/* Variables and functions */
 scalar_t__ AVIERR_BADSIZE ; 
 scalar_t__ AVIERR_OK ; 
 scalar_t__ AVIStreamInfoA (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  AVIStreamRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateEditableStream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ EditStreamSetInfoA (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int ICQUALITY_HIGH ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_EditStreamSetInfo(void)
{
    PAVISTREAM stream = NULL;
    HRESULT hres;
    AVISTREAMINFOA info, info2;

    hres = CreateEditableStream(&stream, NULL);
    ok(hres == AVIERR_OK, "got 0x%08X, expected AVIERR_OK\n", hres);

    /* Size parameter is somehow checked (notice the crash with size=-1 below) */
    hres = EditStreamSetInfoA(stream, NULL, 0);
    ok( hres == AVIERR_BADSIZE, "got 0x%08X, expected AVIERR_BADSIZE\n", hres);

    hres = EditStreamSetInfoA(stream, NULL, sizeof(AVISTREAMINFOA)-1 );
    ok( hres == AVIERR_BADSIZE, "got 0x%08X, expected AVIERR_BADSIZE\n", hres);

    if(0)
    {   
        /* Crashing - first parameter not checked */
        EditStreamSetInfoA(NULL, &info, sizeof(info) );

        /* Crashing - second parameter not checked */
        EditStreamSetInfoA(stream, NULL, sizeof(AVISTREAMINFOA) );

        EditStreamSetInfoA(stream, NULL, -1);
    }

    hres = AVIStreamInfoA(stream, &info, sizeof(info) );
    ok( hres == 0, "got 0x%08X, expected 0\n", hres);

             /* Does the function check what's it's updating ? */

#define IS_INFO_UPDATED(m) do { \
    hres = EditStreamSetInfoA(stream, &info, sizeof(info) ); \
    ok( hres == 0, "got 0x%08X, expected 0\n", hres); \
    hres = AVIStreamInfoA(stream, &info2, sizeof(info2) ); \
    ok( hres == 0, "got 0x%08X, expected 0\n", hres); \
    ok( info2.m == info.m, "EditStreamSetInfo did not update "#m" parameter\n" ); \
    } while(0)

    info.dwStart++;
    IS_INFO_UPDATED(dwStart);
    info.dwStart = 0;
    IS_INFO_UPDATED(dwStart);

    info.wPriority++;
    IS_INFO_UPDATED(wPriority);
    info.wPriority = 0;
    IS_INFO_UPDATED(wPriority);

    info.wLanguage++;
    IS_INFO_UPDATED(wLanguage);
    info.wLanguage = 0;
    IS_INFO_UPDATED(wLanguage);

    info.dwScale++;
    IS_INFO_UPDATED(dwScale);
    info.dwScale = 0;
    IS_INFO_UPDATED(dwScale);

    info.dwRate++;
    IS_INFO_UPDATED(dwRate);
    info.dwRate = 0;
    IS_INFO_UPDATED(dwRate);

    info.dwQuality++;
    IS_INFO_UPDATED(dwQuality);
    info.dwQuality = 0;
    IS_INFO_UPDATED(dwQuality);
    info.dwQuality = -2;
    IS_INFO_UPDATED(dwQuality);
    info.dwQuality = ICQUALITY_HIGH+1;
    IS_INFO_UPDATED(dwQuality);

    info.rcFrame.left = 0;
    IS_INFO_UPDATED(rcFrame.left);
    info.rcFrame.top = 0;
    IS_INFO_UPDATED(rcFrame.top);
    info.rcFrame.right = 0;
    IS_INFO_UPDATED(rcFrame.right);
    info.rcFrame.bottom = 0;
    IS_INFO_UPDATED(rcFrame.bottom);

    info.rcFrame.left = -1;
    IS_INFO_UPDATED(rcFrame.left);
    info.rcFrame.top = -1;
    IS_INFO_UPDATED(rcFrame.top);
    info.rcFrame.right = -1;
    IS_INFO_UPDATED(rcFrame.right);
    info.rcFrame.bottom = -1;
    IS_INFO_UPDATED(rcFrame.bottom);
    AVIStreamRelease(stream);
#undef IS_INFO_UPDATED
}