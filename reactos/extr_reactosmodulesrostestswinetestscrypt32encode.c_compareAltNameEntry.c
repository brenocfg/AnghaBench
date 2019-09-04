#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_9__ {TYPE_1__ IPAddress; int /*<<< orphan*/  pwszURL; } ;
struct TYPE_8__ {int dwAltNameChoice; } ;
typedef  TYPE_2__ CERT_ALT_NAME_ENTRY ;

/* Variables and functions */
#define  CERT_ALT_NAME_DIRECTORY_NAME 135 
#define  CERT_ALT_NAME_DNS_NAME 134 
#define  CERT_ALT_NAME_EDI_PARTY_NAME 133 
#define  CERT_ALT_NAME_IP_ADDRESS 132 
#define  CERT_ALT_NAME_REGISTERED_ID 131 
#define  CERT_ALT_NAME_RFC822_NAME 130 
#define  CERT_ALT_NAME_URL 129 
#define  CERT_ALT_NAME_X400_ADDRESS 128 
 TYPE_5__ U (TYPE_2__ const) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void compareAltNameEntry(const CERT_ALT_NAME_ENTRY *expected,
 const CERT_ALT_NAME_ENTRY *got)
{
    ok(expected->dwAltNameChoice == got->dwAltNameChoice,
     "Expected name choice %d, got %d\n", expected->dwAltNameChoice,
     got->dwAltNameChoice);
    if (expected->dwAltNameChoice == got->dwAltNameChoice)
    {
        switch (got->dwAltNameChoice)
        {
        case CERT_ALT_NAME_RFC822_NAME:
        case CERT_ALT_NAME_DNS_NAME:
        case CERT_ALT_NAME_EDI_PARTY_NAME:
        case CERT_ALT_NAME_URL:
        case CERT_ALT_NAME_REGISTERED_ID:
            ok((!U(*expected).pwszURL && !U(*got).pwszURL) ||
             (!U(*expected).pwszURL && !lstrlenW(U(*got).pwszURL)) ||
             (!U(*got).pwszURL && !lstrlenW(U(*expected).pwszURL)) ||
             !lstrcmpW(U(*expected).pwszURL, U(*got).pwszURL),
             "Unexpected name\n");
            break;
        case CERT_ALT_NAME_X400_ADDRESS:
        case CERT_ALT_NAME_DIRECTORY_NAME:
        case CERT_ALT_NAME_IP_ADDRESS:
            ok(U(*got).IPAddress.cbData == U(*expected).IPAddress.cbData,
               "Unexpected IP address length %d\n", U(*got).IPAddress.cbData);
            ok(!memcmp(U(*got).IPAddress.pbData, U(*expected).IPAddress.pbData,
                       U(*got).IPAddress.cbData), "Unexpected value\n");
            break;
        }
    }
}