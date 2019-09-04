#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  size_t DWORD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BASE64_DECODE_INVALID ; 
 int BASE64_DECODE_PADDING ; 
 int BASE64_DECODE_WHITESPACE ; 
 size_t CRYPT_STRING_BASE64 ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int decodeBase64Byte (int) ; 

__attribute__((used)) static LONG Base64ToBinary(const void* pszString, BOOL wide, DWORD cchString,
 BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags)
{
    DWORD cbIn, cbValid, cbOut, hasPadding;
    BYTE block[4];
    for (cbIn = cbValid = cbOut = hasPadding = 0; cbIn < cchString; ++cbIn)
    {
        int c = wide ? (int)((WCHAR*)pszString)[cbIn] : (int)((char*)pszString)[cbIn];
        int d = decodeBase64Byte(c);
        if (d == BASE64_DECODE_INVALID)
            goto invalid;
        if (d == BASE64_DECODE_WHITESPACE)
            continue;

        /* When padding starts, data is not acceptable */
        if (hasPadding && d != BASE64_DECODE_PADDING)
            goto invalid;

        /* Padding after a full block (like "VVVV=") is ok and stops decoding */
        if (d == BASE64_DECODE_PADDING && (cbValid & 3) == 0)
            break;

        cbValid += 1;

        if (d == BASE64_DECODE_PADDING)
        {
            hasPadding = 1;
            /* When padding reaches a full block, stop decoding */
            if ((cbValid & 3) == 0)
                break;
            continue;
        }

        /* cbOut is incremented in the 4-char block as follows: "1-23" */
        if ((cbValid & 3) != 2)
            cbOut += 1;
    }
    /* Fail if the block has bad padding; omitting padding is fine */
    if ((cbValid & 3) != 0 && hasPadding)
        goto invalid;
    /* Check available buffer size */
    if (pbBinary && *pcbBinary && cbOut > *pcbBinary)
        goto overflow;
    /* Convert the data; this step depends on the validity checks above! */
    if (pbBinary) for (cbIn = cbValid = cbOut = 0; cbIn < cchString; ++cbIn)
    {
        int c = wide ? (int)((WCHAR*)pszString)[cbIn] : (int)((char*)pszString)[cbIn];
        int d = decodeBase64Byte(c);
        if (d == BASE64_DECODE_WHITESPACE)
            continue;
        if (d == BASE64_DECODE_PADDING)
            break;
        block[cbValid & 3] = d;
        cbValid += 1;
        switch (cbValid & 3) {
        case 1:
            pbBinary[cbOut++] = (block[0] << 2);
            break;
        case 2:
            pbBinary[cbOut-1] = (block[0] << 2) | (block[1] >> 4);
            break;
        case 3:
            pbBinary[cbOut++] = (block[1] << 4) | (block[2] >> 2);
            break;
        case 0:
            pbBinary[cbOut++] = (block[2] << 6) | (block[3] >> 0);
            break;
        }
    }
    *pcbBinary = cbOut;
    if (pdwSkip)
        *pdwSkip = 0;
    if (pdwFlags)
        *pdwFlags = CRYPT_STRING_BASE64;
    return ERROR_SUCCESS;
overflow:
    return ERROR_INSUFFICIENT_BUFFER;
invalid:
    *pcbBinary = cbOut;
    return ERROR_INVALID_DATA;
}