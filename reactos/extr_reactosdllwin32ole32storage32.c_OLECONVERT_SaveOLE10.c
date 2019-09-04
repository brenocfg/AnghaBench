#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* lpstbl; } ;
struct TYPE_15__ {scalar_t__ dwOleID; scalar_t__ dwTypeID; int dwOleTypeNameLength; void* strOleTypeName; int dwDataLength; scalar_t__ pData; int /*<<< orphan*/  dwMetaFileHeight; int /*<<< orphan*/  dwMetaFileWidth; } ;
struct TYPE_14__ {int (* Put ) (TYPE_3__*,void*,int) ;} ;
typedef  TYPE_2__ OLECONVERT_OLESTREAM_DATA ;
typedef  TYPE_3__* LPOLESTREAM ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CONVERT10_E_OLESTREAM_PUT ; 
 scalar_t__ OLESTREAM_ID ; 
 scalar_t__ S_OK ; 
 int stub1 (TYPE_3__*,void*,int) ; 
 int stub2 (TYPE_3__*,void*,int) ; 
 int stub3 (TYPE_3__*,void*,int) ; 
 int stub4 (TYPE_3__*,void*,int) ; 
 int stub5 (TYPE_3__*,void*,int) ; 
 int stub6 (TYPE_3__*,void*,int) ; 
 int stub7 (TYPE_3__*,void*,int) ; 
 int stub8 (TYPE_3__*,void*,int) ; 

__attribute__((used)) static HRESULT OLECONVERT_SaveOLE10(OLECONVERT_OLESTREAM_DATA *pData, LPOLESTREAM pOleStream)
{
    DWORD dwSize;
    HRESULT hRes = S_OK;


   /* Set the OleID */
    dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)&(pData->dwOleID), sizeof(pData->dwOleID));
    if(dwSize != sizeof(pData->dwOleID))
    {
        hRes = CONVERT10_E_OLESTREAM_PUT;
    }

    if(hRes == S_OK)
    {
        /* Set the TypeID */
        dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)&(pData->dwTypeID), sizeof(pData->dwTypeID));
        if(dwSize != sizeof(pData->dwTypeID))
        {
            hRes = CONVERT10_E_OLESTREAM_PUT;
        }
    }

    if(pData->dwOleID == OLESTREAM_ID && pData->dwTypeID != 0 && hRes == S_OK)
    {
        /* Set the Length of the OleTypeName */
        dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)&(pData->dwOleTypeNameLength), sizeof(pData->dwOleTypeNameLength));
        if(dwSize != sizeof(pData->dwOleTypeNameLength))
        {
            hRes = CONVERT10_E_OLESTREAM_PUT;
        }

        if(hRes == S_OK)
        {
            if(pData->dwOleTypeNameLength > 0)
            {
                /* Set the OleTypeName */
                dwSize = pOleStream->lpstbl->Put(pOleStream, pData->strOleTypeName, pData->dwOleTypeNameLength);
                if(dwSize != pData->dwOleTypeNameLength)
                {
                    hRes = CONVERT10_E_OLESTREAM_PUT;
                }
            }
        }

        if(hRes == S_OK)
        {
            /* Set the width of the Metafile */
            dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)&(pData->dwMetaFileWidth), sizeof(pData->dwMetaFileWidth));
            if(dwSize != sizeof(pData->dwMetaFileWidth))
            {
                hRes = CONVERT10_E_OLESTREAM_PUT;
            }
        }

        if(hRes == S_OK)
        {
            /* Set the height of the Metafile */
            dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)&(pData->dwMetaFileHeight), sizeof(pData->dwMetaFileHeight));
            if(dwSize != sizeof(pData->dwMetaFileHeight))
            {
                hRes = CONVERT10_E_OLESTREAM_PUT;
            }
        }

        if(hRes == S_OK)
        {
            /* Set the length of the Data */
            dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)&(pData->dwDataLength), sizeof(pData->dwDataLength));
            if(dwSize != sizeof(pData->dwDataLength))
            {
                hRes = CONVERT10_E_OLESTREAM_PUT;
            }
        }

        if(hRes == S_OK)
        {
            if(pData->dwDataLength > 0)
            {
                /* Set the Data (eg. IStorage, Metafile, Bitmap) */
                dwSize = pOleStream->lpstbl->Put(pOleStream, (void *)  pData->pData, pData->dwDataLength);
                if(dwSize != pData->dwDataLength)
                {
                    hRes = CONVERT10_E_OLESTREAM_PUT;
                }
            }
        }
    }
    return hRes;
}