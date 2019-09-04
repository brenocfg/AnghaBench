#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ authAttrHash; scalar_t__ contentHash; } ;
struct TYPE_4__ {size_t cSignerHandle; TYPE_2__* signerHandles; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CSignedMsgData ;

/* Variables and functions */
 int /*<<< orphan*/  CryptDestroyHash (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_2__*) ; 

__attribute__((used)) static void CSignedMsgData_CloseHandles(CSignedMsgData *msg_data)
{
    DWORD i;

    for (i = 0; i < msg_data->cSignerHandle; i++)
    {
        if (msg_data->signerHandles[i].contentHash)
            CryptDestroyHash(msg_data->signerHandles[i].contentHash);
        if (msg_data->signerHandles[i].authAttrHash)
            CryptDestroyHash(msg_data->signerHandles[i].authAttrHash);
    }
    CryptMemFree(msg_data->signerHandles);
    msg_data->signerHandles = NULL;
    msg_data->cSignerHandle = 0;
}