#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {void* dwCallback; } ;
struct TYPE_10__ {void* dwReturn; int /*<<< orphan*/  dwItem; } ;
struct TYPE_9__ {int wDeviceID; void* lpstrDeviceType; } ;
struct TYPE_8__ {char* lpstrReturn; int dwRetSize; } ;
struct TYPE_7__ {char* lpstrReturn; int dwRetSize; int dwNumber; void* wDeviceType; void* dwCallback; } ;
struct TYPE_12__ {TYPE_5__ gen; TYPE_4__ caps; TYPE_3__ open; TYPE_2__ info; TYPE_1__ sys; } ;
typedef  TYPE_6__ MCI_PARMS_UNION ;
typedef  int MCIERROR ;
typedef  int MCIDEVICEID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  void* LPSTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  void* DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetThreadLocale () ; 
 int /*<<< orphan*/  LANGIDFROMLCID (int /*<<< orphan*/ ) ; 
 scalar_t__ LANG_ENGLISH ; 
 int MCIERR_CANNOT_USE_ALL ; 
 int MCIERR_DEVICE_TYPE_REQUIRED ; 
 int MCIERR_DUPLICATE_ALIAS ; 
 int MCIERR_FILE_NOT_FOUND ; 
 int MCIERR_INVALID_DEVICE_NAME ; 
 int MCIERR_INVALID_FILE ; 
 int MCIERR_NEW_REQUIRES_ALIAS ; 
 int MCIERR_PARAM_OVERFLOW ; 
 int MCIERR_UNRECOGNIZED_KEYWORD ; 
 int MCIERR_UNSUPPORTED_FUNCTION ; 
 int MCI_ALL_DEVICE_ID ; 
 int /*<<< orphan*/  MCI_CLOSE ; 
 void* MCI_DEVTYPE_WAVEFORM_AUDIO ; 
 int /*<<< orphan*/  MCI_GETDEVCAPS ; 
 int /*<<< orphan*/  MCI_GETDEVCAPS_DEVICE_TYPE ; 
 int MCI_GETDEVCAPS_ITEM ; 
 int /*<<< orphan*/  MCI_INFO ; 
 int MCI_INFO_PRODUCT ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int /*<<< orphan*/  MCI_OPEN ; 
 int MCI_OPEN_TYPE ; 
 int MCI_OPEN_TYPE_ID ; 
 int /*<<< orphan*/  MCI_SYSINFO ; 
 int MCI_SYSINFO_INSTALLNAME ; 
 int MCI_SYSINFO_NAME ; 
 int MCI_SYSINFO_OPEN ; 
 int MCI_SYSINFO_QUANTITY ; 
 int MCI_WAIT ; 
 int MMSYSERR_NOTSUPPORTED ; 
 scalar_t__ PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int atoi (char*) ; 
 scalar_t__ broken (int) ; 
 int dbg_mcierr (int) ; 
 int mciGetDeviceIDA (char*) ; 
 int mciSendCommandA (int,int /*<<< orphan*/ ,int,void*) ; 
 int mciSendCommandW (int,int /*<<< orphan*/ ,int,void*) ; 
 int mciSendStringA (char const*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_notification (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_openCloseWAVE(HWND hwnd)
{
    MCIERROR err;
    MCI_PARMS_UNION parm;
    const char command_open[] = "open new type waveaudio alias mysound notify";
    const char command_close_my[] = "close mysound notify";
    const char command_close_all[] = "close all notify";
    const char command_sysinfo[] = "sysinfo waveaudio quantity open";
    char buf[1024];
    DWORD intbuf[3] = { 0xDEADF00D, 99, 0xABADCAFE };
    memset(buf, 0, sizeof(buf));
    test_notification(hwnd, "-prior to any command-", 0);

    /* Avoid Sysinfo quantity with notify because Win9x and newer differ. */
    err = mciSendStringA("sysinfo all quantity", buf, sizeof(buf), hwnd);
    ok(!err,"mci sysinfo all quantity returned %s\n", dbg_mcierr(err));
    if(!err) trace("[MCI] with %s drivers\n", buf);

    parm.sys.lpstrReturn = (LPSTR)&intbuf[1];
    parm.sys.dwRetSize = sizeof(DWORD);
    parm.sys.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO; /* ignored */
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_QUANTITY | MCI_WAIT,
            (DWORD_PTR)&parm);
    ok(!err, "mciCommand sysinfo all quantity returned %s\n", dbg_mcierr(err));
    if(!err) ok(atoi(buf)==intbuf[1],"sysinfo all quantity string and command differ\n");

    parm.sys.dwRetSize = sizeof(DWORD)-1;
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_QUANTITY, (DWORD_PTR)&parm);
    ok(err == MCIERR_PARAM_OVERFLOW || broken(!err/* Win9x */),
            "mciCommand sysinfo with too small buffer returned %s\n", dbg_mcierr(err));

    err = mciSendStringA("open new type waveaudio alias r shareable", buf, sizeof(buf), NULL);
    ok(err==MCIERR_UNSUPPORTED_FUNCTION,"mci open new shareable returned %s\n", dbg_mcierr(err));
    if(!err) {
        err = mciSendStringA("close r", NULL, 0, NULL);
        ok(!err,"mci close shareable returned %s\n", dbg_mcierr(err));
    }

    err = mciGetDeviceIDA("waveaudio");
    ok(!err, "mciGetDeviceIDA waveaudio returned %u, expected 0\n", err);

    err = mciSendStringA(command_open, buf, sizeof(buf), hwnd);
    ok(!err,"mci %s returned %s\n", command_open, dbg_mcierr(err));
    ok(!strcmp(buf,"1"), "mci open deviceId: %s, expected 1\n", buf);
    /* Wine<=1.1.33 used to ignore anything past alias XY */
    test_notification(hwnd,"open new alias notify",MCI_NOTIFY_SUCCESSFUL);

    err = mciSendStringA("status mysound time format", buf, sizeof(buf), hwnd);
    ok(!err,"mci status time format returned %s\n", dbg_mcierr(err));
    if(!err) {
        if (PRIMARYLANGID(LANGIDFROMLCID(GetThreadLocale())) == LANG_ENGLISH)
            ok(!strcmp(buf,"milliseconds"), "mci status time format: %s\n", buf);
        else trace("locale-dependent time format: %s (ms)\n", buf);
    }

    memset(buf, 0, sizeof(buf));
    parm.sys.dwNumber = 1;
    parm.sys.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO; /* ignored */
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = sizeof(buf);
    parm.sys.dwCallback = (DWORD_PTR)hwnd;
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_SYSINFO,
            MCI_SYSINFO_NAME | MCI_SYSINFO_OPEN | MCI_NOTIFY, (DWORD_PTR)&parm);
    ok(!err,"mciCommand MCI_SYSINFO all name 1 open notify: %s\n", dbg_mcierr(err));
    if(!err) ok(!strcmp(buf,"mysound"), "sysinfo name returned %s\n", buf);
    test_notification(hwnd, "SYSINFO name notify\n", MCI_NOTIFY_SUCCESSFUL);

    memset(buf, 0, sizeof(buf));
    parm.sys.dwNumber = 1;
    parm.sys.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO; /* ignored */
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = 8; /* mysound\0 */
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_NAME | MCI_SYSINFO_OPEN,
            (DWORD_PTR)&parm);
    ok(!err,"mciCommand MCI_SYSINFO all name 1 open buffer[8]: %s\n", dbg_mcierr(err));
    if(!err) ok(!strcmp(buf,"mysound"), "sysinfo name returned %s\n", buf);

    memset(buf, 0, sizeof(buf));
    /* dwRetSize counts characters, not bytes, despite what MSDN says. */
    parm.sys.dwNumber = 1;
    parm.sys.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO; /* ignored */
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = 8; /* mysound\0 */
    /* MCI_..._PARMSA and PARMSW share the same layout, use one for both tests. */
    err = mciSendCommandW(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_NAME | MCI_SYSINFO_OPEN, (DWORD_PTR)&parm);
    ok(!err || broken(err==MMSYSERR_NOTSUPPORTED/* Win9x */), "mciCommandW MCI_SYSINFO all name 1 open buffer[8]: %s\n", dbg_mcierr(err));
    if(!err) ok(!strcmp_wa((LPWSTR)buf,"mysound"), "sysinfo name 1 open contents\n");

    memset(buf, 0, sizeof(buf));
    buf[0] = 'Y';
    parm.sys.dwNumber = 1;
    parm.sys.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO; /* ignored */
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = 7; /* too short for mysound\0 */
    err = mciSendCommandW(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_NAME | MCI_SYSINFO_OPEN, (DWORD_PTR)&parm);
    ok(err==MCIERR_PARAM_OVERFLOW || broken(err==MMSYSERR_NOTSUPPORTED/* Win9x */), "mciCommandW MCI_SYSINFO all name 1 open too small: %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"Y"), "output buffer %s\n", buf);

    /* Win9x overwrites the tiny buffer and returns success, newer versions signal overflow. */
    memset(buf, 0, sizeof(buf));
    buf[0] = 'Y';
    parm.sys.dwNumber = 1;
    parm.sys.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO; /* ignored */
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = 2; /* too short for mysound\0 */
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_NAME | MCI_SYSINFO_OPEN,
            (DWORD_PTR)&parm);
    ok(err==MCIERR_PARAM_OVERFLOW || broken(!err /* Win9x */),"mciCommand MCI_SYSINFO all name 1 open too small: %s\n", dbg_mcierr(err));
    ok(!strcmp(buf, err ? "Y" : "mysound"), "sysinfo short name returned %s\n", buf);

    err = mciSendStringA("sysinfo mysound quantity open", buf, sizeof(buf), hwnd);
    ok(err==MCIERR_DEVICE_TYPE_REQUIRED,"sysinfo alias quantity: %s\n", dbg_mcierr(err));

    err = mciSendStringA("sysinfo nosuchalias quantity open", buf, sizeof(buf), hwnd);
    ok(err==MCIERR_DEVICE_TYPE_REQUIRED,"sysinfo unknown quantity open: %s\n", dbg_mcierr(err));

    err = mciSendStringA("sysinfo all installname", buf, sizeof(buf), hwnd);
    ok(err==MCIERR_CANNOT_USE_ALL,"sysinfo all installname: %s\n", dbg_mcierr(err));

    buf[0] = 'M'; buf[1] = 0;
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = sizeof(buf);
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_INSTALLNAME, (DWORD_PTR)&parm);
    ok(err==MCIERR_CANNOT_USE_ALL,"mciCommand MCI_SYSINFO all installname: %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"M"), "output buffer %s\n", buf);

    err = mciSendStringA("sysinfo nodev installname", buf, sizeof(buf), hwnd);
    ok(err==MCIERR_INVALID_DEVICE_NAME,"sysinfo nodev installname: %s\n", dbg_mcierr(err));
    ok(!buf[0], "sysinfo error buffer %s\n", buf);

    buf[0] = 'K';
    parm.sys.lpstrReturn = buf;
    parm.sys.dwRetSize = sizeof(buf);
    err = mciSendCommandW(24000, MCI_SYSINFO, MCI_SYSINFO_INSTALLNAME, (DWORD_PTR)&parm);
    ok(err==MCIERR_INVALID_DEVICE_NAME || broken(err==MMSYSERR_NOTSUPPORTED/* Win9x */), "mciCommand MCI_SYSINFO nodev installname: %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"K"), "output buffer %s\n", buf);

    buf[0] = 0; buf[1] = 'A'; buf[2] = 'j'; buf[3] = 0;
    parm.info.lpstrReturn = buf;
    parm.info.dwRetSize = 2;
    err = mciSendCommandA(1, MCI_INFO, MCI_INFO_PRODUCT, (DWORD_PTR)&parm);
    ok(!err, "mciCommand MCI_INFO product: %s\n", dbg_mcierr(err));
    ok(buf[0] /* && !buf[1] */ && (buf[2] == 'j' || broken(!buf[2])), "info product output buffer %s\n", buf);
    /* Producing non-ASCII multi-byte output, native forgets to zero-terminate a too small buffer
     * with SendStringA, while SendStringW works correctly (jap. and chin. locale): ignore buf[1] */
    /* Bug in 64 bit Vista/w2k8/w7: mciSendStringW is used! (not in xp nor w2k3) */

    buf[0] = 'K'; buf[1] = 0;
    parm.info.dwRetSize = sizeof(buf);
    err = mciSendCommandW(1, MCI_INFO, 0x07000000, (DWORD_PTR)&parm);
    ok(err==MCIERR_UNRECOGNIZED_KEYWORD || broken(err==MMSYSERR_NOTSUPPORTED/* Win9x */), "mciCommand MCI_INFO other: %s\n", dbg_mcierr(err));
    ok(!strcmp(buf,"K"), "info output buffer %s\n", buf);

    err = mciGetDeviceIDA("all");
    ok(err == MCI_ALL_DEVICE_ID, "mciGetDeviceIDA all returned %u, expected MCI_ALL_DEVICE_ID\n", err);

    err = mciSendStringA(command_close_my, NULL, 0, hwnd);
    ok(!err,"mci %s returned %s\n", command_close_my, dbg_mcierr(err));
    test_notification(hwnd, command_close_my, MCI_NOTIFY_SUCCESSFUL);
    Sleep(5);
    test_notification(hwnd, command_close_my, 0);

    err = mciSendStringA("open no-such-file-exists.wav alias y buffer 6", buf, sizeof(buf), NULL);
    ok(err==MCIERR_FILE_NOT_FOUND,"open no-such-file.wav returned %s\n", dbg_mcierr(err));
    if(!err) {
        err = mciSendStringA("close y", NULL, 0, NULL);
        ok(!err,"close y returned %s\n", dbg_mcierr(err));
    }

    err = mciSendStringA("open no-such-dir\\file.wav alias y type waveaudio", buf, sizeof(buf), NULL);
    ok(err==MCIERR_FILE_NOT_FOUND || broken(err==MCIERR_INVALID_FILE /* Win9X */),"open no-such-dir/file.wav returned %s\n", dbg_mcierr(err));
    if(!err) {
        err = mciSendStringA("close y", NULL, 0, NULL);
        ok(!err,"close y returned %s\n", dbg_mcierr(err));
    }

    err = mciSendStringA("open ! alias no", buf, sizeof(buf), NULL);
    ok(err==MCIERR_INVALID_DEVICE_NAME,"open !(void): %s\n", dbg_mcierr(err));

    err = mciSendStringA("open !no-such-file-exists.wav alias no", buf, sizeof(buf), NULL);
    ok(err==MCIERR_FILE_NOT_FOUND || /* Win9X */err==MCIERR_INVALID_DEVICE_NAME,"open !name: %s\n", dbg_mcierr(err));

    /* FILE_NOT_FOUND stems from mciwave,
     * the complete name including ! is passed through since NT */
    err = mciSendStringA("open nosuchdevice!tempfile.wav alias no", buf, sizeof(buf), NULL);
    ok(err==MCIERR_FILE_NOT_FOUND || /* Win9X */err==MCIERR_INVALID_DEVICE_NAME,"open nosuchdevice!name: %s\n", dbg_mcierr(err));
    /* FIXME? use broken(INVALID_DEVICE_NAME) and have Wine not mimic Win9X? */

    err = mciSendStringA("close waveaudio", buf, sizeof(buf), NULL);
    ok(err==MCIERR_INVALID_DEVICE_NAME,"close waveaudio: %s\n", dbg_mcierr(err));

    err = mciSendStringA(command_close_all, NULL, 0, NULL);
    ok(!err,"mci %s (without buffer) returned %s\n", command_close_all, dbg_mcierr(err));

    err = mciSendStringA(command_close_all, buf, sizeof(buf), hwnd);
    ok(!err,"mci %s (with output buffer) returned %s\n", command_close_all, dbg_mcierr(err));
    ok(buf[0] == 0, "mci %s output buffer: %s\n", command_close_all, buf);
    /* No notification left, everything closed already */
    test_notification(hwnd, command_close_all, 0);
    /* TODO test close all sends one notification per open device */

    err = mciSendStringA(command_sysinfo, buf, sizeof(buf), NULL);
    ok(!err,"mci %s returned %s\n", command_sysinfo, dbg_mcierr(err));
    ok(buf[0] == '0' && buf[1] == 0, "mci %s, expected output buffer '0', got: '%s'\n", command_sysinfo, buf);

    err = mciSendStringA("open new type waveaudio", buf, sizeof(buf), NULL);
    ok(err==MCIERR_NEW_REQUIRES_ALIAS,"mci open new without alias returned %s\n", dbg_mcierr(err));

    parm.open.lpstrDeviceType = (LPSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
    err = mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID, (DWORD_PTR)&parm);
    ok(!err,"mciCommand OPEN_TYPE_ID waveaudio: %s\n", dbg_mcierr(err));

    if(!err) {
        MCIDEVICEID wDeviceID = parm.open.wDeviceID;
        parm.caps.dwItem = MCI_GETDEVCAPS_DEVICE_TYPE;
        err = mciSendCommandA(wDeviceID, MCI_GETDEVCAPS, MCI_GETDEVCAPS_ITEM, (DWORD_PTR)&parm);
        ok(!err,"mciCommand MCI_GETDEVCAPS device type: %s\n", dbg_mcierr(err));
        ok(MCI_DEVTYPE_WAVEFORM_AUDIO==parm.caps.dwReturn,"mciCommand GETDEVCAPS says %u, expected %u\n", parm.caps.dwReturn, MCI_DEVTYPE_WAVEFORM_AUDIO);
    }

    ok(0xDEADF00D==intbuf[0] && 0xABADCAFE==intbuf[2],"DWORD buffer corruption\n");

    err = mciGetDeviceIDA("waveaudio");
    ok(err == 1, "mciGetDeviceIDA waveaudio returned %u, expected 1\n", err);

    err = mciSendStringA("open no-such-file.wav alias waveaudio", buf, sizeof(buf), NULL);
    ok(err==MCIERR_DUPLICATE_ALIAS, "mci open alias waveaudio returned %s\n", dbg_mcierr(err));
    /* If it were not already in use, open avivideo alias waveaudio would succeed,
     * making for funny test cases. */

    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_WAIT, 0); /* from MSDN */
    ok(!err, "mciCommand close returned %s\n", dbg_mcierr(err));

    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_NOTIFY, 0);
    ok(!err, "mciCommand close returned %s\n", dbg_mcierr(err));

    parm.gen.dwCallback = (DWORD_PTR)hwnd;
    err = mciSendCommandA(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_NOTIFY, (DWORD_PTR)&parm);
    ok(!err, "mciCommand close returned %s\n", dbg_mcierr(err));
    test_notification(hwnd, command_close_all, 0); /* None left */
}