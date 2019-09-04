#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_7__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_8__ {TYPE_1__ Parameters; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_10__ {TYPE_3__ PublicKey; TYPE_2__ Algorithm; } ;
typedef  TYPE_4__ CERT_PUBLIC_KEY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void comparePublicKeyInfo(const CERT_PUBLIC_KEY_INFO *expected,
 const CERT_PUBLIC_KEY_INFO *got)
{
    ok(!strcmp(expected->Algorithm.pszObjId, got->Algorithm.pszObjId),
     "Expected OID %s, got %s\n", expected->Algorithm.pszObjId,
     got->Algorithm.pszObjId);
    ok(expected->Algorithm.Parameters.cbData ==
     got->Algorithm.Parameters.cbData,
     "Expected parameters of %d bytes, got %d\n",
     expected->Algorithm.Parameters.cbData, got->Algorithm.Parameters.cbData);
    if (expected->Algorithm.Parameters.cbData)
        ok(!memcmp(expected->Algorithm.Parameters.pbData,
         got->Algorithm.Parameters.pbData, got->Algorithm.Parameters.cbData),
         "Unexpected algorithm parameters\n");
    ok(expected->PublicKey.cbData == got->PublicKey.cbData,
     "Expected public key of %d bytes, got %d\n",
     expected->PublicKey.cbData, got->PublicKey.cbData);
    if (expected->PublicKey.cbData)
        ok(!memcmp(expected->PublicKey.pbData, got->PublicKey.pbData,
         got->PublicKey.cbData), "Unexpected public key value\n");
}