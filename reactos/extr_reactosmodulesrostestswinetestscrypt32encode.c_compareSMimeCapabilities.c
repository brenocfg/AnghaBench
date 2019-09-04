#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cCapability; TYPE_2__* rgCapability; } ;
struct TYPE_6__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_7__ {TYPE_1__ Parameters; int /*<<< orphan*/  pszObjId; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  size_t DWORD ;
typedef  TYPE_3__ CRYPT_SMIME_CAPABILITIES ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,size_t,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compareSMimeCapabilities(LPCSTR header,
 const CRYPT_SMIME_CAPABILITIES *expected, const CRYPT_SMIME_CAPABILITIES *got)
{
    DWORD i;

    ok(got->cCapability == expected->cCapability,
     "%s: expected %d capabilities, got %d\n", header, expected->cCapability,
     got->cCapability);
    for (i = 0; i < expected->cCapability; i++)
    {
        ok(!strcmp(expected->rgCapability[i].pszObjId,
         got->rgCapability[i].pszObjId), "%s[%d]: expected %s, got %s\n",
         header, i, expected->rgCapability[i].pszObjId,
         got->rgCapability[i].pszObjId);
        ok(expected->rgCapability[i].Parameters.cbData ==
         got->rgCapability[i].Parameters.cbData,
         "%s[%d]: expected %d bytes, got %d\n", header, i,
         expected->rgCapability[i].Parameters.cbData,
         got->rgCapability[i].Parameters.cbData);
        if (expected->rgCapability[i].Parameters.cbData)
            ok(!memcmp(expected->rgCapability[i].Parameters.pbData,
             got->rgCapability[i].Parameters.pbData,
             expected->rgCapability[i].Parameters.cbData),
             "%s[%d]: unexpected value\n", header, i);
    }
}