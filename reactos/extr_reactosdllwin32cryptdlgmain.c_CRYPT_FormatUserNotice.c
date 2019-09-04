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
typedef  char WCHAR ;
struct TYPE_6__ {char* pszOrganization; int cNoticeNumbers; } ;
struct TYPE_5__ {char* pszDisplayText; TYPE_2__* pNoticeReference; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCWSTR ;
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  TYPE_1__ CERT_POLICY_QUALIFIER_USER_NOTICE ;
typedef  TYPE_2__ CERT_POLICY_QUALIFIER_NOTICE_REFERENCE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int CRYPT_FORMAT_STR_MULTI_LINE ; 
 int /*<<< orphan*/  CryptDecodeObjectEx (int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**,int*) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDS_NOTICE_NUM ; 
 int /*<<< orphan*/  IDS_NOTICE_REF ; 
 int /*<<< orphan*/  IDS_NOTICE_TEXT ; 
 int /*<<< orphan*/  IDS_ORGANIZATION ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_PKIX_POLICY_QUALIFIER_USERNOTICE ; 
 char* colonCrlf ; 
 char* colonSpace ; 
 char* commaSep ; 
 char* crlf ; 
 int /*<<< orphan*/  hInstance ; 
 char* indent ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlen (char*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL CRYPT_FormatUserNotice(DWORD dwCertEncodingType,
 DWORD dwFormatStrType, const BYTE *pbEncoded, DWORD cbEncoded,
 WCHAR *str, DWORD *pcchStr)
{
    BOOL ret;
    DWORD size, charsNeeded = 1;
    CERT_POLICY_QUALIFIER_USER_NOTICE *notice;

    if ((ret = CryptDecodeObjectEx(dwCertEncodingType,
     X509_PKIX_POLICY_QUALIFIER_USERNOTICE, pbEncoded, cbEncoded,
     CRYPT_DECODE_ALLOC_FLAG, NULL, &notice, &size)))
    {
        static const WCHAR numFmt[] = { '%','d',0 };
        CERT_POLICY_QUALIFIER_NOTICE_REFERENCE *pNoticeRef =
         notice->pNoticeReference;
        LPCWSTR headingSep, sep;
        DWORD headingSepLen, sepLen;
        LPWSTR noticeRef, organization, noticeNum, noticeText;
        DWORD noticeRefLen, organizationLen, noticeNumLen, noticeTextLen;
        WCHAR noticeNumStr[11];

        noticeRefLen = LoadStringW(hInstance, IDS_NOTICE_REF,
         (LPWSTR)&noticeRef, 0);
        organizationLen = LoadStringW(hInstance, IDS_ORGANIZATION,
         (LPWSTR)&organization, 0);
        noticeNumLen = LoadStringW(hInstance, IDS_NOTICE_NUM,
         (LPWSTR)&noticeNum, 0);
        noticeTextLen = LoadStringW(hInstance, IDS_NOTICE_TEXT,
         (LPWSTR)&noticeText, 0);
        if (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
        {
            headingSep = colonCrlf;
            sep = crlf;
        }
        else
        {
            headingSep = colonSpace;
            sep = commaSep;
        }
        sepLen = strlenW(sep);
        headingSepLen = strlenW(headingSep);

        if (pNoticeRef)
        {
            DWORD k;
            LPCSTR src;

            if (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            {
                charsNeeded += 3 * strlenW(indent);
                if (str && *pcchStr >= charsNeeded)
                {
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                }
            }
            charsNeeded += noticeRefLen;
            if (str && *pcchStr >= charsNeeded)
            {
                memcpy(str, noticeRef, noticeRefLen * sizeof(WCHAR));
                str += noticeRefLen;
            }
            charsNeeded += headingSepLen;
            if (str && *pcchStr >= charsNeeded)
            {
                strcpyW(str, headingSep);
                str += headingSepLen;
            }
            if (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            {
                charsNeeded += 4 * strlenW(indent);
                if (str && *pcchStr >= charsNeeded)
                {
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                }
            }
            charsNeeded += organizationLen;
            if (str && *pcchStr >= charsNeeded)
            {
                memcpy(str, organization, organizationLen * sizeof(WCHAR));
                str += organizationLen;
            }
            charsNeeded += strlen(pNoticeRef->pszOrganization);
            if (str && *pcchStr >= charsNeeded)
                for (src = pNoticeRef->pszOrganization; src && *src;
                 src++, str++)
                    *str = *src;
            charsNeeded += sepLen;
            if (str && *pcchStr >= charsNeeded)
            {
                strcpyW(str, sep);
                str += sepLen;
            }
            for (k = 0; k < pNoticeRef->cNoticeNumbers; k++)
            {
                if (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                {
                    charsNeeded += 4 * strlenW(indent);
                    if (str && *pcchStr >= charsNeeded)
                    {
                        strcpyW(str, indent);
                        str += strlenW(indent);
                        strcpyW(str, indent);
                        str += strlenW(indent);
                        strcpyW(str, indent);
                        str += strlenW(indent);
                        strcpyW(str, indent);
                        str += strlenW(indent);
                    }
                }
                charsNeeded += noticeNumLen;
                if (str && *pcchStr >= charsNeeded)
                {
                    memcpy(str, noticeNum, noticeNumLen * sizeof(WCHAR));
                    str += noticeNumLen;
                }
                sprintfW(noticeNumStr, numFmt, k + 1);
                charsNeeded += strlenW(noticeNumStr);
                if (str && *pcchStr >= charsNeeded)
                {
                    strcpyW(str, noticeNumStr);
                    str += strlenW(noticeNumStr);
                }
                charsNeeded += sepLen;
                if (str && *pcchStr >= charsNeeded)
                {
                    strcpyW(str, sep);
                    str += sepLen;
                }
            }
        }
        if (notice->pszDisplayText)
        {
            if (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            {
                charsNeeded += 3 * strlenW(indent);
                if (str && *pcchStr >= charsNeeded)
                {
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                    strcpyW(str, indent);
                    str += strlenW(indent);
                }
            }
            charsNeeded += noticeTextLen;
            if (str && *pcchStr >= charsNeeded)
            {
                memcpy(str, noticeText, noticeTextLen * sizeof(WCHAR));
                str += noticeTextLen;
            }
            charsNeeded += strlenW(notice->pszDisplayText);
            if (str && *pcchStr >= charsNeeded)
            {
                strcpyW(str, notice->pszDisplayText);
                str += strlenW(notice->pszDisplayText);
            }
            charsNeeded += sepLen;
            if (str && *pcchStr >= charsNeeded)
            {
                strcpyW(str, sep);
                str += sepLen;
            }
        }
        LocalFree(notice);
        if (!str)
            *pcchStr = charsNeeded;
        else if (*pcchStr < charsNeeded)
        {
            *pcchStr = charsNeeded;
            SetLastError(ERROR_MORE_DATA);
            ret = FALSE;
        }
        else
            *pcchStr = charsNeeded;
    }
    return ret;
}