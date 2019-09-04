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
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__ enveloped_data; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CRYPT_ENVELOPED_DATA ;
typedef  TYPE_3__ CRYPT_DER_BLOB ;
typedef  TYPE_4__ CDecodeMsg ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_AsnDecodePKCSEnvelopedData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 

__attribute__((used)) static BOOL CDecodeMsg_DecodeEnvelopedContent(CDecodeMsg *msg,
 const CRYPT_DER_BLOB *blob)
{
    BOOL ret;
    CRYPT_ENVELOPED_DATA *envelopedData;
    DWORD size;

    ret = CRYPT_AsnDecodePKCSEnvelopedData(blob->pbData, blob->cbData,
     CRYPT_DECODE_ALLOC_FLAG, NULL, (CRYPT_ENVELOPED_DATA *)&envelopedData,
     &size);
    if (ret)
        msg->u.enveloped_data.data = envelopedData;
    return ret;
}