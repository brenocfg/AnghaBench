#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ AuthenticationTarget; TYPE_5__* TransportCredentials; int /*<<< orphan*/  NumberOfAuthnSchemes; } ;
struct TYPE_12__ {TYPE_3__* QOS; } ;
struct TYPE_14__ {TYPE_4__ common; } ;
struct TYPE_13__ {int /*<<< orphan*/  Password; int /*<<< orphan*/  User; } ;
struct TYPE_11__ {TYPE_2__* qos; } ;
struct TYPE_9__ {TYPE_7__* HttpCredentials; } ;
struct TYPE_10__ {scalar_t__ AdditionalSecurityInfoType; TYPE_1__ u; } ;
typedef  TYPE_5__ SEC_WINNT_AUTH_IDENTITY_W ;
typedef  TYPE_6__ RpcConnection_http ;
typedef  TYPE_7__ RPC_HTTP_TRANSPORT_CREDENTIALS_W ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RPC_C_AUTHN_INFO_TYPE_HTTP ; 
 scalar_t__ RPC_C_HTTP_AUTHN_TARGET_SERVER ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL has_credentials(RpcConnection_http *httpc)
{
    RPC_HTTP_TRANSPORT_CREDENTIALS_W *creds;
    SEC_WINNT_AUTH_IDENTITY_W *id;

    if (!httpc->common.QOS || httpc->common.QOS->qos->AdditionalSecurityInfoType != RPC_C_AUTHN_INFO_TYPE_HTTP)
        return FALSE;

    creds = httpc->common.QOS->qos->u.HttpCredentials;
    if (creds->AuthenticationTarget != RPC_C_HTTP_AUTHN_TARGET_SERVER || !creds->NumberOfAuthnSchemes)
        return FALSE;

    id = creds->TransportCredentials;
    if (!id || !id->User || !id->Password) return FALSE;

    return TRUE;
}