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
typedef  int /*<<< orphan*/  policyPara ;
struct TYPE_8__ {int cbSize; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int wDay; int wMonth; int wYear; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__ CERT_CHAIN_POLICY_PARA ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_CHAIN_POLICY_ALLOW_UNKNOWN_CA_FLAG ; 
 int /*<<< orphan*/  CERT_CHAIN_POLICY_AUTHENTICODE ; 
 int /*<<< orphan*/  CERT_CHAIN_POLICY_IGNORE_NOT_TIME_VALID_FLAG ; 
 int /*<<< orphan*/  CHECK_CHAIN_POLICY_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  CHECK_CHAIN_POLICY_STATUS_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  authenticodePolicyCheck ; 
 int /*<<< orphan*/  ignoredInvalidDateBasePolicyCheck ; 
 int /*<<< orphan*/  ignoredUnknownCAPolicyCheck ; 
 TYPE_1__ oct2007 ; 

__attribute__((used)) static void check_authenticode_policy(void)
{
    CERT_CHAIN_POLICY_PARA policyPara = { 0 };
    SYSTEMTIME epochStart = { 0 };

    /* The authenticode policy doesn't seem to check anything beyond the base
     * policy.  It might check for chains signed by the MS test cert, but none
     * of these chains is.
     */
    CHECK_CHAIN_POLICY_STATUS_ARRAY(CERT_CHAIN_POLICY_AUTHENTICODE, NULL,
     authenticodePolicyCheck, &oct2007, NULL);
    policyPara.cbSize = sizeof(policyPara);
    policyPara.dwFlags = CERT_CHAIN_POLICY_ALLOW_UNKNOWN_CA_FLAG;
    CHECK_CHAIN_POLICY_STATUS(CERT_CHAIN_POLICY_AUTHENTICODE, NULL,
     ignoredUnknownCAPolicyCheck, &oct2007, &policyPara);
    epochStart.wDay = epochStart.wMonth = 1;
    epochStart.wYear = 1601;
    CHECK_CHAIN_POLICY_STATUS(CERT_CHAIN_POLICY_AUTHENTICODE, NULL,
     ignoredUnknownCAPolicyCheck, &epochStart, &policyPara);
    policyPara.dwFlags = CERT_CHAIN_POLICY_IGNORE_NOT_TIME_VALID_FLAG;
    CHECK_CHAIN_POLICY_STATUS(CERT_CHAIN_POLICY_AUTHENTICODE, NULL,
     ignoredInvalidDateBasePolicyCheck, &oct2007, &policyPara);
}