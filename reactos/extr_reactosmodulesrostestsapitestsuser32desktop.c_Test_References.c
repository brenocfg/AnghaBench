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
typedef  int /*<<< orphan*/  objectInfo ;
typedef  int ULONG ;
struct TYPE_3__ {int HandleCount; int PointerCount; int /*<<< orphan*/  member_0; } ;
typedef  char* PCWSTR ;
typedef  TYPE_1__ OBJECT_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * HWINSTA ;
typedef  int /*<<< orphan*/ * HDESK ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseDesktop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseWindowStation (int /*<<< orphan*/ *) ; 
 int ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/ * GetProcessWindowStation () ; 
 int /*<<< orphan*/ * GetThreadDesktop (int /*<<< orphan*/ ) ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  NtQueryObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectBasicInformation ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetProcessWindowStation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetThreadDesktop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_desk (char*,int*) ; 
 int /*<<< orphan*/ * create_winsta (char*,int*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * open_desk (char*,int*) ; 
 int /*<<< orphan*/ * open_winsta (char*,int*) ; 

__attribute__((used)) static void Test_References(void)
{
    PCWSTR winstaName = L"RefTestWinsta";
    PCWSTR deskName = L"RefTestDesktop";
    HWINSTA hwinsta;
    HWINSTA hwinsta2;
    HWINSTA hwinstaProcess;
    DWORD error;
    NTSTATUS status;
    OBJECT_BASIC_INFORMATION objectInfo = { 0 };
    HDESK hdesk;
    HDESK hdesk1;
    BOOL ret;
    ULONG baseRefs;

#define check_ref(handle, hdlcnt, ptrcnt) \
    status = NtQueryObject(handle, ObjectBasicInformation, &objectInfo, sizeof(objectInfo), NULL);  \
    ok(status == STATUS_SUCCESS, "status = 0x%lx\n", status);                                       \
    ok(objectInfo.HandleCount == (hdlcnt), "HandleCount = %lu, expected %lu\n", objectInfo.HandleCount, (ULONG)(hdlcnt));  \
    ok(objectInfo.PointerCount == (ptrcnt), "PointerCount = %lu, expected %lu\n", objectInfo.PointerCount, (ULONG)(ptrcnt));

    /* Winsta shouldn't exist */
    hwinsta = open_winsta(winstaName, &error);
    ok(hwinsta == NULL && error == ERROR_FILE_NOT_FOUND, "Got 0x%p, 0x%lx\n", hwinsta, error);

    /* Create it -- we get 1/4 instead of 1/3 because Winstas are kept in a list */
    hwinsta = create_winsta(winstaName, &error);
    ok(hwinsta != NULL && error == NO_ERROR, "Got 0x%p, 0x%lx\n", hwinsta, error);
    check_ref(hwinsta, 1, 4);
    baseRefs = objectInfo.PointerCount;
    ok(baseRefs == 4, "Window station initially has %lu references, expected 4\n", baseRefs);
    check_ref(hwinsta, 1, baseRefs);

    /* Open a second handle */
    hwinsta2 = open_winsta(winstaName, &error);
    ok(hwinsta2 != NULL && error == 0xfeedf00d, "Got 0x%p, 0x%lx\n", hwinsta, error);
    check_ref(hwinsta, 2, baseRefs + 1);

    /* Close second handle -- back to 1/4 */
    ret = CloseHandle(hwinsta2);
    ok(ret == TRUE, "ret = %d\n", ret);
    check_ref(hwinsta, 1, baseRefs);

    /* Same game but using CloseWindowStation */
    hwinsta2 = open_winsta(winstaName, &error);
    ok(hwinsta2 != NULL && error == 0xfeedf00d, "Got 0x%p, 0x%lx\n", hwinsta, error);
    check_ref(hwinsta, 2, baseRefs + 1);
    ret = CloseWindowStation(hwinsta2);
    ok(ret == TRUE, "ret = %d\n", ret);
    check_ref(hwinsta, 1, baseRefs);

    /* Set it as the process Winsta */
    hwinstaProcess = GetProcessWindowStation();
    SetProcessWindowStation(hwinsta);
    check_ref(hwinsta, 2, baseRefs + 2);

    /* Create a desktop. It takes a reference */
    hdesk = create_desk(deskName, &error);
    ok(hdesk != NULL && error == 0xfeedf00d, "Got 0x%p, 0x%lx\n", hdesk, error);
    check_ref(hwinsta, 2, baseRefs + 3);

    /* CloseHandle fails, must use CloseDesktop */
    ret = CloseHandle(hdesk);
    ok(ret == FALSE, "ret = %d\n", ret);
    check_ref(hwinsta, 2, baseRefs + 3);
    ret = CloseDesktop(hdesk);
    ok(ret == TRUE, "ret = %d\n", ret);
    check_ref(hwinsta, 2, baseRefs + 2); // 2/7 on Win7?

    /* Desktop no longer exists */
    hdesk = open_desk(deskName, &error);
    ok(hdesk == NULL && error == ERROR_FILE_NOT_FOUND, "Got 0x%p, 0x%lx\n", hdesk, error);
    check_ref(hwinsta, 2, baseRefs + 2);

    /* Restore the original process Winsta */
    SetProcessWindowStation(hwinstaProcess);
    check_ref(hwinsta, 1, baseRefs);

    /* Close our last handle */
    ret = CloseHandle(hwinsta);
    ok(ret == TRUE, "ret = %d\n", ret);

    /* Winsta no longer exists */
    hwinsta = open_winsta(winstaName, &error);
    ok(hwinsta == NULL && error == ERROR_FILE_NOT_FOUND, "Got 0x%p, 0x%lx\n", hwinsta, error);

    /* Create the Winsta again, and close it while there's still a desktop */
    hwinsta = create_winsta(winstaName, &error);
    ok(hwinsta != NULL && error == NO_ERROR, "Got 0x%p, 0x%lx\n", hwinsta, error);
    check_ref(hwinsta, 1, baseRefs);
    hwinstaProcess = GetProcessWindowStation();
    SetProcessWindowStation(hwinsta);
    check_ref(hwinsta, 2, baseRefs + 2);

    hdesk = create_desk(deskName, &error);
    ok(hdesk != NULL && error == 0xfeedf00d, "Got 0x%p, 0x%lx\n", hdesk, error);
    check_ref(hwinsta, 2, baseRefs + 3);

    /* The reference from the desktop is still there, hence 1/5 */
    SetProcessWindowStation(hwinstaProcess);
    check_ref(hwinsta, 1, baseRefs + 1);
    ret = CloseHandle(hwinsta);
    ok(ret == TRUE, "ret = %d\n", ret);
    hwinsta = open_winsta(winstaName, &error);
    ok(hwinsta == NULL && error == ERROR_FILE_NOT_FOUND, "Got 0x%p, 0x%lx\n", hwinsta, error);

    /* Test references by SetThreadDesktop */
    hdesk1 = GetThreadDesktop(GetCurrentThreadId());
    ok (hdesk1 != hdesk, "Expected the new desktop not to be the thread desktop\n");

    check_ref(hdesk, 1, 8);
    baseRefs = objectInfo.PointerCount;
    ok(baseRefs == 8, "Desktop initially has %lu references, expected 8\n", baseRefs);
    check_ref(hdesk, 1, baseRefs);

    SetThreadDesktop(hdesk);
    check_ref(hdesk, 1, baseRefs + 1);
    ok (GetThreadDesktop(GetCurrentThreadId()) == hdesk, "Expected GetThreadDesktop to return hdesk\n");

    SetThreadDesktop(hdesk1);
    check_ref(hdesk, 1, baseRefs);
    ok (GetThreadDesktop(GetCurrentThreadId()) == hdesk1, "Expected GetThreadDesktop to return hdesk1\n");
}