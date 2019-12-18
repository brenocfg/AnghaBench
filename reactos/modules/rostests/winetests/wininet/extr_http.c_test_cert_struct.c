#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_7__ {int /*<<< orphan*/  ex_issuer; int /*<<< orphan*/  ex_subject; } ;
typedef  TYPE_1__ cert_struct_test_t ;
struct TYPE_8__ {int lpszSubjectInfo; int lpszIssuerInfo; int lpszSignatureAlgName; int lpszEncryptionAlgName; int lpszProtocolName; int dwKeySize; } ;
typedef  TYPE_2__ INTERNET_CERTIFICATE_INFOA ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/  INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT ; 
 int InternetQueryOptionA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  release_cert_info (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_cert_struct(HINTERNET req, const cert_struct_test_t *test)
{
    INTERNET_CERTIFICATE_INFOA info;
    DWORD size;
    BOOL res;

    memset(&info, 0x5, sizeof(info));

    size = sizeof(info);
    res = InternetQueryOptionA(req, INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT, &info, &size);
    ok(res, "InternetQueryOption failed: %u\n", GetLastError());
    ok(size == sizeof(info), "size = %u\n", size);

    ok(!strcmp(info.lpszSubjectInfo, test->ex_subject), "lpszSubjectInfo = %s\n", info.lpszSubjectInfo);
    ok(!strcmp(info.lpszIssuerInfo, test->ex_issuer), "lpszIssuerInfo = %s\n", info.lpszIssuerInfo);
    ok(!info.lpszSignatureAlgName, "lpszSignatureAlgName = %s\n", info.lpszSignatureAlgName);
    ok(!info.lpszEncryptionAlgName, "lpszEncryptionAlgName = %s\n", info.lpszEncryptionAlgName);
    ok(!info.lpszProtocolName, "lpszProtocolName = %s\n", info.lpszProtocolName);
    ok(info.dwKeySize >= 128 && info.dwKeySize <= 256, "dwKeySize = %u\n", info.dwKeySize);

    release_cert_info(&info);
}