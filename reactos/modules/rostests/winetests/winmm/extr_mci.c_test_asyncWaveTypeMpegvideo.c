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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_NOTIFY_ABORTED ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUPERSEDED ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 char* dbg_mcierr (int) ; 
 int mciSendStringA (char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int ok_saved ; 
 int /*<<< orphan*/  skip (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_notification (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_asyncWaveTypeMpegvideo(HWND hwnd)
{
    MCIDEVICEID wDeviceID;
    int err;
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    err = mciSendStringA("open tempfile.wav alias mysound notify type mpegvideo", buf, sizeof(buf), hwnd);
    ok(err==ok_saved,"mci open tempfile.wav returned %s\n", dbg_mcierr(err));
    if(err) {
        skip("Cannot open tempfile.wav for playing (%s), skipping\n", dbg_mcierr(err));
        return;
    }
    ok(!strcmp(buf,"1"), "mci open deviceId: %s, expected 1\n", buf);
    wDeviceID = atoi(buf);
    ok(wDeviceID,"mci open DeviceID: %d\n", wDeviceID);
    test_notification(hwnd,"open alias notify",MCI_NOTIFY_SUCCESSFUL);

    err = mciSendStringA("play mysound notify", NULL, 0, hwnd);
    ok(!err,"mci play returned %s\n", dbg_mcierr(err));

    Sleep(500); /* milliseconds */

    err = mciSendStringA("pause mysound wait", NULL, 0, hwnd);
    ok(!err,"mci pause wait returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("status mysound mode notify", buf, sizeof(buf), hwnd);
    ok(!err,"mci status mode returned %s\n", dbg_mcierr(err));
    if(!err) ok(!strcmp(buf,"paused"), "mci status mode: %s\n", buf);
    test_notification(hwnd,"play (superseded)",MCI_NOTIFY_SUPERSEDED);
    test_notification(hwnd,"status",MCI_NOTIFY_SUCCESSFUL);

    err = mciSendStringA("seek mysound to start wait", NULL, 0, NULL);
    ok(!err,"mci seek to start wait returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("set mysound time format milliseconds", NULL, 0, NULL);
    ok(!err,"mci time format milliseconds returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("play mysound to 1500 notify", NULL, 0, hwnd);
    ok(!err,"mci play returned %s\n", dbg_mcierr(err));
    Sleep(200);
    test_notification(hwnd,"play",0);

    err = mciSendStringA("close mysound wait", NULL, 0, NULL);
    ok(!err,"mci close wait returned %s\n", dbg_mcierr(err));
    test_notification(hwnd,"play (aborted by close)",MCI_NOTIFY_ABORTED);
}