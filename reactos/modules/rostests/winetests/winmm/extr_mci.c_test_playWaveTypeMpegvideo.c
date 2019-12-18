#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ dwReturn; int /*<<< orphan*/  dwItem; } ;
typedef  TYPE_1__ MCI_STATUS_PARMS ;
typedef  int /*<<< orphan*/  MCI_PLAY_PARMS ;
typedef  scalar_t__ MCIERROR ;
typedef  int MCIDEVICEID ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  char* DWORD ;

/* Variables and functions */
 scalar_t__ MCIERR_OUTOFRANGE ; 
 scalar_t__ MCI_MODE_PLAY ; 
 int /*<<< orphan*/  MCI_PLAY ; 
 int /*<<< orphan*/  MCI_STATUS ; 
 int /*<<< orphan*/  MCI_STATUS_ITEM ; 
 int /*<<< orphan*/  MCI_STATUS_MODE ; 
 char* dbg_mcierr (scalar_t__) ; 
 int mciGetDeviceIDA (char*) ; 
 scalar_t__ mciSendCommandA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mciSendStringA (char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ ok_saved ; 
 int /*<<< orphan*/  skip (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_playWaveTypeMpegvideo(void)
{
    MCIERROR err;
    MCIDEVICEID wDeviceID;
    MCI_PLAY_PARMS play_parm;
    MCI_STATUS_PARMS status_parm;
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    err = mciSendStringA("open tempfile.wav type MPEGVideo alias mysound", NULL, 0, NULL);
    ok(err==ok_saved,"mci open tempfile.wav type MPEGVideo returned %s\n", dbg_mcierr(err));
    if(err) {
        skip("Cannot open tempfile.wav type MPEGVideo for playing (%s), skipping\n", dbg_mcierr(err));
        return;
    }

    wDeviceID = mciGetDeviceIDA("mysound");
    ok(wDeviceID == 1, "mciGetDeviceIDA mysound returned %u, expected 1\n", wDeviceID);

    err = mciSendCommandA(wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&play_parm);
    ok(!err,"mciCommand play returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("status mysound mode", buf, sizeof(buf), NULL);
    ok(!err,"mci status mode returned %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"playing"), "mci status mode: %s\n", buf);

    status_parm.dwItem = MCI_STATUS_MODE;
    err = mciSendCommandA(wDeviceID, MCI_STATUS,
                          MCI_STATUS_ITEM,
                          (DWORD_PTR)&status_parm);
    ok(!err,"mciCommand status mode returned %s\n", dbg_mcierr(err));
    ok(status_parm.dwReturn == MCI_MODE_PLAY,
       "mciCommand status mode: %u\n", (DWORD)status_parm.dwReturn);

    err = mciSendStringA("setaudio mysound volume to 1000", NULL, 0, NULL);
    ok(!err,"mci setaudio volume to 1000 returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("status mysound mode", buf, sizeof(buf), NULL);
    ok(!err,"mci status mode returned %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"playing"), "mci status mode: %s\n", buf);

    err = mciSendStringA("setaudio mysound volume to 1001", NULL, 0, NULL);
    ok(err==MCIERR_OUTOFRANGE,"mci setaudio volume to 1001 returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("status mysound mode", buf, sizeof(buf), NULL);
    ok(!err,"mci status mode returned %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"playing"), "mci status mode: %s\n", buf);

    err = mciSendStringA("close mysound", NULL, 0, NULL);
    ok(!err,"mci close returned %s\n", dbg_mcierr(err));
}