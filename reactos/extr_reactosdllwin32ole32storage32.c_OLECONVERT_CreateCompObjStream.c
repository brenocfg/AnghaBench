#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pCompObjUnknown2 ;
typedef  int /*<<< orphan*/  pCompObjUnknown1 ;
typedef  int WCHAR ;
struct TYPE_3__ {int* byUnknown1; int* byUnknown2; int dwOleTypeNameLength; int* strOleTypeName; int dwProgIDNameLength; int* strProgIDName; int dwCLSIDNameLength; int* strCLSIDName; int /*<<< orphan*/  clsid; } ;
typedef  TYPE_1__ OLECONVERT_ISTORAGE_COMPOBJ ;
typedef  int /*<<< orphan*/  LPSTORAGE ;
typedef  char* LPCSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorageCompObj ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ CLSIDFromProgID (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int OLESTREAM_MAX_STR_LEN ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegQueryValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WriteClassStm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ open_classes_key (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int*,char*) ; 
 void* strlen (char*) ; 

HRESULT OLECONVERT_CreateCompObjStream(LPSTORAGE pStorage, LPCSTR strOleTypeName)
{
    IStream *pStream;
    HRESULT hStorageRes, hRes = S_OK;
    OLECONVERT_ISTORAGE_COMPOBJ IStorageCompObj;
    static const WCHAR wstrStreamName[] = {1,'C', 'o', 'm', 'p', 'O', 'b', 'j', 0};
    WCHAR bufferW[OLESTREAM_MAX_STR_LEN];

    static const BYTE pCompObjUnknown1[] = {0x01, 0x00, 0xFE, 0xFF, 0x03, 0x0A, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};
    static const BYTE pCompObjUnknown2[] = {0xF4, 0x39, 0xB2, 0x71};

    /* Initialize the CompObj structure */
    memset(&IStorageCompObj, 0, sizeof(IStorageCompObj));
    memcpy(IStorageCompObj.byUnknown1, pCompObjUnknown1, sizeof(pCompObjUnknown1));
    memcpy(IStorageCompObj.byUnknown2, pCompObjUnknown2, sizeof(pCompObjUnknown2));


    /*  Create a CompObj stream if it doesn't exist */
    hStorageRes = IStorage_CreateStream(pStorage, wstrStreamName,
        STGM_WRITE  | STGM_SHARE_EXCLUSIVE, 0, 0, &pStream );
    if(hStorageRes == S_OK)
    {
        /* copy the OleTypeName to the compobj struct */
        IStorageCompObj.dwOleTypeNameLength = strlen(strOleTypeName)+1;
        strcpy(IStorageCompObj.strOleTypeName, strOleTypeName);

        /* copy the OleTypeName to the compobj struct */
        /* Note: in the test made, these were Identical      */
        IStorageCompObj.dwProgIDNameLength = strlen(strOleTypeName)+1;
        strcpy(IStorageCompObj.strProgIDName, strOleTypeName);

        /* Get the CLSID */
        MultiByteToWideChar( CP_ACP, 0, IStorageCompObj.strProgIDName, -1,
                             bufferW, OLESTREAM_MAX_STR_LEN );
        hRes = CLSIDFromProgID(bufferW, &(IStorageCompObj.clsid));

        if(hRes == S_OK)
        {
            HKEY hKey;
            LONG hErr;
            /* Get the CLSID Default Name from the Registry */
            hErr = open_classes_key(HKEY_CLASSES_ROOT, bufferW, MAXIMUM_ALLOWED, &hKey);
            if(hErr == ERROR_SUCCESS)
            {
                char strTemp[OLESTREAM_MAX_STR_LEN];
                IStorageCompObj.dwCLSIDNameLength = OLESTREAM_MAX_STR_LEN;
                hErr = RegQueryValueA(hKey, NULL, strTemp, (LONG*) &(IStorageCompObj.dwCLSIDNameLength));
                if(hErr == ERROR_SUCCESS)
                {
                    strcpy(IStorageCompObj.strCLSIDName, strTemp);
                }
                RegCloseKey(hKey);
            }
        }

        /* Write CompObj Structure to stream */
        hRes = IStream_Write(pStream, IStorageCompObj.byUnknown1, sizeof(IStorageCompObj.byUnknown1), NULL);

        WriteClassStm(pStream,&(IStorageCompObj.clsid));

        hRes = IStream_Write(pStream, &(IStorageCompObj.dwCLSIDNameLength), sizeof(IStorageCompObj.dwCLSIDNameLength), NULL);
        if(IStorageCompObj.dwCLSIDNameLength > 0)
        {
            hRes = IStream_Write(pStream, IStorageCompObj.strCLSIDName, IStorageCompObj.dwCLSIDNameLength, NULL);
        }
        hRes = IStream_Write(pStream, &(IStorageCompObj.dwOleTypeNameLength) , sizeof(IStorageCompObj.dwOleTypeNameLength), NULL);
        if(IStorageCompObj.dwOleTypeNameLength > 0)
        {
            hRes = IStream_Write(pStream, IStorageCompObj.strOleTypeName , IStorageCompObj.dwOleTypeNameLength, NULL);
        }
        hRes = IStream_Write(pStream, &(IStorageCompObj.dwProgIDNameLength) , sizeof(IStorageCompObj.dwProgIDNameLength), NULL);
        if(IStorageCompObj.dwProgIDNameLength > 0)
        {
            hRes = IStream_Write(pStream, IStorageCompObj.strProgIDName , IStorageCompObj.dwProgIDNameLength, NULL);
        }
        hRes = IStream_Write(pStream, IStorageCompObj.byUnknown2 , sizeof(IStorageCompObj.byUnknown2), NULL);
        IStream_Release(pStream);
    }
    return hRes;
}