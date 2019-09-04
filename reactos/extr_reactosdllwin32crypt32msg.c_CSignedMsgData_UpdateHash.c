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
struct TYPE_5__ {size_t cSignerHandle; TYPE_1__* signerHandles; } ;
struct TYPE_4__ {int /*<<< orphan*/  contentHash; } ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CSignedMsgData ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptHashData (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL CSignedMsgData_UpdateHash(CSignedMsgData *msg_data,
 const BYTE *pbData, DWORD cbData)
{
    DWORD i;
    BOOL ret = TRUE;

    for (i = 0; ret && i < msg_data->cSignerHandle; i++)
        ret = CryptHashData(msg_data->signerHandles[i].contentHash, pbData,
         cbData, 0);
    return ret;
}