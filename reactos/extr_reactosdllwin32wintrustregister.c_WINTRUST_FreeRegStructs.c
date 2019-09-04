#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_36__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_35__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_34__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_33__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_32__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_31__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_30__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_29__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_28__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_27__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_26__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_25__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_24__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_23__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_22__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_21__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_20__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;
struct TYPE_19__ {int /*<<< orphan*/  pwszFunctionName; int /*<<< orphan*/  pwszDLLName; } ;

/* Variables and functions */
 TYPE_18__ DriverCleanupPolicy ; 
 TYPE_17__ DriverFinalPolicy ; 
 TYPE_16__ DriverInitializePolicy ; 
 TYPE_15__ GenericChainCertificateTrust ; 
 TYPE_14__ GenericChainFinalProv ; 
 TYPE_13__ HTTPSCertificateTrust ; 
 TYPE_12__ HTTPSFinalProv ; 
 TYPE_11__ OfficeCleanupPolicy ; 
 TYPE_10__ OfficeInitializePolicy ; 
 TYPE_9__ SoftpubCertCheck ; 
 TYPE_8__ SoftpubCertificate ; 
 TYPE_7__ SoftpubCleanup ; 
 TYPE_6__ SoftpubDefCertInit ; 
 TYPE_5__ SoftpubDumpStructure ; 
 TYPE_4__ SoftpubFinalPolicy ; 
 TYPE_3__ SoftpubInitialization ; 
 TYPE_2__ SoftpubMessage ; 
 TYPE_1__ SoftpubSignature ; 
 int /*<<< orphan*/  WINTRUST_Free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WINTRUST_FreeRegStructs(void)
{
#define WINTRUST_FREEREGENTRY( action ) \
    WINTRUST_Free(action.pwszDLLName); \
    WINTRUST_Free(action.pwszFunctionName);

    WINTRUST_FREEREGENTRY(SoftpubInitialization);
    WINTRUST_FREEREGENTRY(SoftpubMessage);
    WINTRUST_FREEREGENTRY(SoftpubSignature);
    WINTRUST_FREEREGENTRY(SoftpubCertificate);
    WINTRUST_FREEREGENTRY(SoftpubCertCheck);
    WINTRUST_FREEREGENTRY(SoftpubFinalPolicy);
    WINTRUST_FREEREGENTRY(SoftpubCleanup);
    WINTRUST_FREEREGENTRY(SoftpubDefCertInit);
    WINTRUST_FREEREGENTRY(SoftpubDumpStructure);
    WINTRUST_FREEREGENTRY(HTTPSCertificateTrust);
    WINTRUST_FREEREGENTRY(HTTPSFinalProv);
    WINTRUST_FREEREGENTRY(OfficeInitializePolicy);
    WINTRUST_FREEREGENTRY(OfficeCleanupPolicy);
    WINTRUST_FREEREGENTRY(DriverInitializePolicy);
    WINTRUST_FREEREGENTRY(DriverFinalPolicy);
    WINTRUST_FREEREGENTRY(DriverCleanupPolicy);
    WINTRUST_FREEREGENTRY(GenericChainCertificateTrust);
    WINTRUST_FREEREGENTRY(GenericChainFinalProv);

#undef WINTRUST_FREEREGENTRY
}