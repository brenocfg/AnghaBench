#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ CredentialBlobSize; scalar_t__ UserName; scalar_t__ TargetAlias; int /*<<< orphan*/  Persist; int /*<<< orphan*/  CredentialBlob; int /*<<< orphan*/  LastWritten; scalar_t__ Comment; scalar_t__ TargetName; int /*<<< orphan*/  Type; int /*<<< orphan*/  Flags; } ;
struct TYPE_5__ {char* TargetName; char* Comment; scalar_t__ CredentialBlobSize; char* TargetAlias; char* UserName; int /*<<< orphan*/ * Attributes; scalar_t__ AttributeCount; int /*<<< orphan*/  Persist; int /*<<< orphan*/ * CredentialBlob; int /*<<< orphan*/  LastWritten; int /*<<< orphan*/  Type; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__* PCREDENTIALA ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_2__ CREDENTIALW ;
typedef  int /*<<< orphan*/  CREDENTIALA ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static INT convert_PCREDENTIALW_to_PCREDENTIALA(const CREDENTIALW *CredentialW, PCREDENTIALA CredentialA, DWORD len)
{
    char *buffer;
    INT string_len;
    INT needed = sizeof(CREDENTIALA);

    if (!CredentialA)
    {
        if (CredentialW->TargetName)
            needed += WideCharToMultiByte(CP_ACP, 0, CredentialW->TargetName, -1, NULL, 0, NULL, NULL);
        if (CredentialW->Comment)
            needed += WideCharToMultiByte(CP_ACP, 0, CredentialW->Comment, -1, NULL, 0, NULL, NULL);
        needed += CredentialW->CredentialBlobSize;
        if (CredentialW->TargetAlias)
            needed += WideCharToMultiByte(CP_ACP, 0, CredentialW->TargetAlias, -1, NULL, 0, NULL, NULL);
        if (CredentialW->UserName)
            needed += WideCharToMultiByte(CP_ACP, 0, CredentialW->UserName, -1, NULL, 0, NULL, NULL);

        return needed;
    }


    buffer = (char *)CredentialA + sizeof(CREDENTIALA);
    len -= sizeof(CREDENTIALA);
    CredentialA->Flags = CredentialW->Flags;
    CredentialA->Type = CredentialW->Type;

    if (CredentialW->TargetName)
    {
        CredentialA->TargetName = buffer;
        string_len = WideCharToMultiByte(CP_ACP, 0, CredentialW->TargetName, -1, buffer, len, NULL, NULL);
        buffer += string_len;
        needed += string_len;
        len -= string_len;
    }
    else
        CredentialA->TargetName = NULL;
    if (CredentialW->Comment)
    {
        CredentialA->Comment = buffer;
        string_len = WideCharToMultiByte(CP_ACP, 0, CredentialW->Comment, -1, buffer, len, NULL, NULL);
        buffer += string_len;
        needed += string_len;
        len -= string_len;
    }
    else
        CredentialA->Comment = NULL;
    CredentialA->LastWritten = CredentialW->LastWritten;
    CredentialA->CredentialBlobSize = CredentialW->CredentialBlobSize;
    if (CredentialW->CredentialBlobSize && (CredentialW->CredentialBlobSize <= len))
    {
        CredentialA->CredentialBlob =(LPBYTE)buffer;
        memcpy(CredentialA->CredentialBlob, CredentialW->CredentialBlob,
               CredentialW->CredentialBlobSize);
        buffer += CredentialW->CredentialBlobSize;
        needed += CredentialW->CredentialBlobSize;
        len -= CredentialW->CredentialBlobSize;
    }
    else
        CredentialA->CredentialBlob = NULL;
    CredentialA->Persist = CredentialW->Persist;
    CredentialA->AttributeCount = 0;
    CredentialA->Attributes = NULL; /* FIXME */
    if (CredentialW->TargetAlias)
    {
        CredentialA->TargetAlias = buffer;
        string_len = WideCharToMultiByte(CP_ACP, 0, CredentialW->TargetAlias, -1, buffer, len, NULL, NULL);
        buffer += string_len;
        needed += string_len;
        len -= string_len;
    }
    else
        CredentialA->TargetAlias = NULL;
    if (CredentialW->UserName)
    {
        CredentialA->UserName = buffer;
        string_len = WideCharToMultiByte(CP_ACP, 0, CredentialW->UserName, -1, buffer, len, NULL, NULL);
        needed += string_len;
    }
    else
        CredentialA->UserName = NULL;

    return needed;
}