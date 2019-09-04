#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UINT16 ;
typedef  int UINT ;
struct TYPE_28__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  OffsetToData; } ;
struct TYPE_27__ {int NumberOfNamedEntries; int NumberOfIdEntries; } ;
struct TYPE_26__ {int Id; int OffsetToDirectory; } ;
struct TYPE_20__ {int /*<<< orphan*/  biSizeImage; } ;
struct TYPE_25__ {TYPE_1__ icHeader; } ;
struct TYPE_24__ {int idCount; scalar_t__ idEntries; } ;
struct TYPE_23__ {int id; } ;
struct TYPE_22__ {scalar_t__ type_id; int count; } ;
struct TYPE_21__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ NE_TYPEINFO ;
typedef  TYPE_4__ NE_NAMEINFO ;
typedef  TYPE_5__* LPicoICONDIR ;
typedef  TYPE_6__* LPICONIMAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int INT ;
typedef  TYPE_7__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  TYPE_8__ IMAGE_RESOURCE_DIRECTORY ;
typedef  TYPE_9__ IMAGE_RESOURCE_DATA_ENTRY ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  scalar_t__ HICON ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateIconFromResourceEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetFileSize (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HIWORD (int) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ICO_GetIconDirectory (int /*<<< orphan*/ *,TYPE_5__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ICO_LoadIcon (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMAGE_DIRECTORY_ENTRY_RESOURCE ; 
 scalar_t__ IMAGE_NT_SIGNATURE ; 
 scalar_t__ IMAGE_OS2_SIGNATURE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int LOWORD (int) ; 
 int LookupIconIdFromDirectoryEx (int /*<<< orphan*/ *,int,int,int,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NE_RSCTYPE_GROUP_ICON ; 
 scalar_t__ NE_RSCTYPE_ICON ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PAGE_READONLY ; 
 int RT_GROUP_ICON ; 
 int RT_ICON ; 
 TYPE_8__* RtlImageDirectoryEntryToData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlImageNtHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RtlImageRvaToVa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SEC_COMMIT ; 
 scalar_t__ SearchPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int TRUE ; 
 scalar_t__ USER32_GetResourceTable (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * USER32_LoadResource (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int abs (int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_8__* find_entry_by_id (TYPE_8__ const*,int,TYPE_8__ const*) ; 
 TYPE_8__* find_entry_default (TYPE_8__ const*,TYPE_8__ const*) ; 
 scalar_t__ get_best_icon_file_offset (int /*<<< orphan*/ *,scalar_t__,int,int,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ICO_ExtractIconExW(
	LPCWSTR lpszExeFileName,
	HICON * RetPtr,
	INT nIconIndex,
	UINT nIcons,
	UINT cxDesired,
	UINT cyDesired,
	UINT *pIconId,
	UINT flags)
{
	UINT		ret = 0;
	UINT		cx1, cx2, cy1, cy2;
	LPBYTE		pData;
	DWORD		sig;
	HANDLE		hFile;
	UINT16		iconDirCount = 0,iconCount = 0;
	LPBYTE		peimage;
	HANDLE		fmapping;
	DWORD		fsizeh,fsizel;
#ifdef __REACTOS__
    WCHAR		szExpandedExePath[MAX_PATH];
#endif
        WCHAR		szExePath[MAX_PATH];
        DWORD		dwSearchReturn;

	TRACE("%s, %d, %d %p 0x%08x\n", debugstr_w(lpszExeFileName), nIconIndex, nIcons, pIconId, flags);

#ifdef __REACTOS__
    if (RetPtr)
        *RetPtr = NULL;

    if (ExpandEnvironmentStringsW(lpszExeFileName, szExpandedExePath, ARRAY_SIZE(szExpandedExePath)))
        lpszExeFileName = szExpandedExePath;
#endif

        dwSearchReturn = SearchPathW(NULL, lpszExeFileName, NULL, ARRAY_SIZE(szExePath), szExePath, NULL);
        if ((dwSearchReturn == 0) || (dwSearchReturn > ARRAY_SIZE(szExePath)))
        {
            WARN("File %s not found or path too long\n", debugstr_w(lpszExeFileName));
            return -1;
        }

	hFile = CreateFileW(szExePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE) return ret;
	fsizel = GetFileSize(hFile,&fsizeh);

	/* Map the file */
	fmapping = CreateFileMappingW(hFile, NULL, PAGE_READONLY | SEC_COMMIT, 0, 0, NULL);
	CloseHandle(hFile);
	if (!fmapping)
	{
          WARN("CreateFileMapping error %ld\n", GetLastError() );
	  return 0xFFFFFFFF;
	}

	if (!(peimage = MapViewOfFile(fmapping, FILE_MAP_READ, 0, 0, 0)))
	{
          WARN("MapViewOfFile error %ld\n", GetLastError() );
	  CloseHandle(fmapping);
	  return 0xFFFFFFFF;
	}
	CloseHandle(fmapping);

	cx1 = LOWORD(cxDesired);
	cx2 = HIWORD(cxDesired);
	cy1 = LOWORD(cyDesired);
	cy2 = HIWORD(cyDesired);

	if (pIconId) /* Invalidate first icon identifier */
		*pIconId = 0xFFFFFFFF;

	if (!pIconId) /* if no icon identifier array present use the icon handle array as intermediate storage */
	  pIconId = (UINT*)RetPtr;

	sig = USER32_GetResourceTable(peimage, fsizel, &pData);

/* NE exe/dll */
	if (sig==IMAGE_OS2_SIGNATURE)
	{
	  BYTE		*pCIDir = 0;
	  NE_TYPEINFO	*pTInfo = (NE_TYPEINFO*)(pData + 2);
	  NE_NAMEINFO	*pIconStorage = NULL;
	  NE_NAMEINFO	*pIconDir = NULL;
	  LPicoICONDIR	lpiID = NULL;
	  ULONG		uSize = 0;

          TRACE("-- OS2/icon Signature (0x%08x)\n", sig);

	  if (pData == (BYTE*)-1)
	  {
	    pCIDir = ICO_GetIconDirectory(peimage, &lpiID, &uSize);	/* check for .ICO file */
	    if (pCIDir)
	    {
	      iconDirCount = 1; iconCount = lpiID->idCount;
              TRACE("-- icon found %p 0x%08x 0x%08x 0x%08x\n", pCIDir, uSize, iconDirCount, iconCount);
	    }
	  }
	  else while (pTInfo->type_id && !(pIconStorage && pIconDir))
	  {
	    if (pTInfo->type_id == NE_RSCTYPE_GROUP_ICON)	/* find icon directory and icon repository */
	    {
	      iconDirCount = pTInfo->count;
	      pIconDir = ((NE_NAMEINFO*)(pTInfo + 1));
	      TRACE("\tfound directory - %i icon families\n", iconDirCount);
	    }
	    if (pTInfo->type_id == NE_RSCTYPE_ICON)
	    {
	      iconCount = pTInfo->count;
	      pIconStorage = ((NE_NAMEINFO*)(pTInfo + 1));
	      TRACE("\ttotal icons - %i\n", iconCount);
	    }
	    pTInfo = (NE_TYPEINFO *)((char*)(pTInfo+1)+pTInfo->count*sizeof(NE_NAMEINFO));
	  }

	  if ((pIconStorage && pIconDir) || lpiID)	  /* load resources and create icons */
	  {
	    if (nIcons == 0)
	    {
	      ret = iconDirCount;
              if (lpiID)	/* *.ico file, deallocate heap pointer*/
	        HeapFree(GetProcessHeap(), 0, pCIDir);
	    }
	    else if (nIconIndex < iconDirCount)
	    {
	      UINT16   i, icon;
	      if (nIcons > iconDirCount - nIconIndex)
	        nIcons = iconDirCount - nIconIndex;

	      for (i = 0; i < nIcons; i++)
	      {
	        /* .ICO files have only one icon directory */
	        if (lpiID == NULL)	/* not *.ico */
	          pCIDir = USER32_LoadResource(peimage, pIconDir + i + nIconIndex, *(WORD*)pData, &uSize);
	        pIconId[i] = LookupIconIdFromDirectoryEx(pCIDir, TRUE, cx1, cy1, flags);
                if (cx2 && cy2) pIconId[++i] = LookupIconIdFromDirectoryEx(pCIDir, TRUE,  cx2, cy2, flags);
	      }
              if (lpiID)	/* *.ico file, deallocate heap pointer*/
	        HeapFree(GetProcessHeap(), 0, pCIDir);

	      for (icon = 0; icon < nIcons; icon++)
	      {
	        pCIDir = NULL;
	        if (lpiID)
	          pCIDir = ICO_LoadIcon(peimage, lpiID->idEntries + (int)pIconId[icon], &uSize);
	        else
	          for (i = 0; i < iconCount; i++)
	            if (pIconStorage[i].id == ((int)pIconId[icon] | 0x8000) )
	              pCIDir = USER32_LoadResource(peimage, pIconStorage + i, *(WORD*)pData, &uSize);

	        if (pCIDir)
                {
	          RetPtr[icon] = CreateIconFromResourceEx(pCIDir, uSize, TRUE, 0x00030000,
                                                                 cx1, cy1, flags);
                  if (cx2 && cy2)
                      RetPtr[++icon] = CreateIconFromResourceEx(pCIDir, uSize, TRUE, 0x00030000,
                                                                       cx2, cy2, flags);
                }
	        else
	          RetPtr[icon] = 0;
	      }
	      ret = icon;	/* return number of retrieved icons */
	    }
	  }
	}
    else
    if (sig == 1 || sig == 2) /* .ICO or .CUR file */
    {
        TRACE("-- icon Signature (0x%08x)\n", sig);

        if (pData == (BYTE*)-1)
        {
            INT cx[2] = {cx1, cx2}, cy[2] = {cy1, cy2};
            INT index;

            for(index = 0; index < (cx2 || cy2 ? 2 : 1); index++)
            {
                DWORD dataOffset;
                LPBYTE imageData;
                POINT hotSpot;
                LPICONIMAGE entry;

                dataOffset = get_best_icon_file_offset(peimage, fsizel, cx[index], cy[index], sig == 1, flags, sig == 1 ? NULL : &hotSpot);

                if (dataOffset)
                {
                    HICON icon;
                    WORD *cursorData = NULL;

                    imageData = peimage + dataOffset;
                    entry = (LPICONIMAGE)(imageData);

                    if(sig == 2)
                    {
                        /* we need to prepend the bitmap data with hot spots for CreateIconFromResourceEx */
                        cursorData = HeapAlloc(GetProcessHeap(), 0, entry->icHeader.biSizeImage + 2 * sizeof(WORD));

                        if(!cursorData)
                            continue;

                        cursorData[0] = hotSpot.x;
                        cursorData[1] = hotSpot.y;

                        memcpy(cursorData + 2, imageData, entry->icHeader.biSizeImage);

                        imageData = (LPBYTE)cursorData;
                    }

                    icon = CreateIconFromResourceEx(imageData, entry->icHeader.biSizeImage, sig == 1, 0x00030000, cx[index], cy[index], flags);

                    if (icon)
                    {
                        RetPtr[index] = icon;
                        iconCount = 1;
                    }

                    if(cursorData != NULL)
                        HeapFree(GetProcessHeap(), 0, cursorData);
                }
            }

        }
        ret = iconCount;	/* return number of retrieved icons */
    }
/* end ico file */

/* exe/dll */
	else if( sig == IMAGE_NT_SIGNATURE )
	{
        BYTE *idata, *igdata;
        const IMAGE_RESOURCE_DIRECTORY *rootresdir, *iconresdir, *icongroupresdir;
        const IMAGE_RESOURCE_DATA_ENTRY *idataent, *igdataent;
        const IMAGE_RESOURCE_DIRECTORY_ENTRY *xresent;
        ULONG size;
        UINT i;

        rootresdir = RtlImageDirectoryEntryToData((HMODULE)peimage, FALSE, IMAGE_DIRECTORY_ENTRY_RESOURCE, &size);
        if (!rootresdir)
        {
            WARN("haven't found section for resource directory.\n");
            goto end;
        }

	  /* search for the group icon directory */
	  if (!(icongroupresdir = find_entry_by_id(rootresdir, LOWORD(RT_GROUP_ICON), rootresdir)))
	  {
	    WARN("No Icongroupresourcedirectory!\n");
	    goto end;		/* failure */
	  }
	  iconDirCount = icongroupresdir->NumberOfNamedEntries + icongroupresdir->NumberOfIdEntries;

	  /* only number of icons requested */
	  if( !pIconId )
	  {
	    ret = iconDirCount;
	    goto end;		/* success */
	  }

	  if( nIconIndex < 0 )
	  {
	    /* search resource id */
	    int n = 0;
	    int iId = abs(nIconIndex);
	    const IMAGE_RESOURCE_DIRECTORY_ENTRY* xprdeTmp = (const IMAGE_RESOURCE_DIRECTORY_ENTRY*)(icongroupresdir+1);

	    while(n<iconDirCount && xprdeTmp)
	    {
              if(xprdeTmp->Id ==  iId)
              {
                  nIconIndex = n;
                  break;
              }
              n++;
              xprdeTmp++;
	    }
	    if (nIconIndex < 0)
	    {
	      WARN("resource id %d not found\n", iId);
	      goto end;		/* failure */
	    }
	  }
	  else
	  {
	    /* check nIconIndex to be in range */
	    if (nIconIndex >= iconDirCount)
	    {
	      WARN("nIconIndex %d is larger than iconDirCount %d\n",nIconIndex,iconDirCount);
	      goto end;		/* failure */
	    }
	  }

	  /* assure we don't get too much */
	  if( nIcons > iconDirCount - nIconIndex )
	    nIcons = iconDirCount - nIconIndex;

	  /* starting from specified index */
	  xresent = (const IMAGE_RESOURCE_DIRECTORY_ENTRY*)(icongroupresdir+1) + nIconIndex;

	  for (i=0; i < nIcons; i++,xresent++)
	  {
	    const IMAGE_RESOURCE_DIRECTORY *resdir;

	    /* go down this resource entry, name */
            resdir = (const IMAGE_RESOURCE_DIRECTORY *)((const char *)rootresdir + xresent->OffsetToDirectory);

	    /* default language (0) */
	    resdir = find_entry_default(resdir,rootresdir);
	    igdataent = (const IMAGE_RESOURCE_DATA_ENTRY*)resdir;

	    /* lookup address in mapped image for virtual address */
        igdata = RtlImageRvaToVa(RtlImageNtHeader((HMODULE)peimage), (HMODULE)peimage, igdataent->OffsetToData, NULL);
        if (!igdata)
	    {
	      FIXME("no matching real address for icongroup!\n");
	      goto end;	/* failure */
	    }
	    pIconId[i] = LookupIconIdFromDirectoryEx(igdata, TRUE, cx1, cy1, flags);
            if (cx2 && cy2) pIconId[++i] = LookupIconIdFromDirectoryEx(igdata, TRUE, cx2, cy2, flags);
	  }

	  if (!(iconresdir=find_entry_by_id(rootresdir,LOWORD(RT_ICON),rootresdir)))
	  {
	    WARN("No Iconresourcedirectory!\n");
	    goto end;		/* failure */
	  }

	  for (i=0; i<nIcons; i++)
	  {
	    const IMAGE_RESOURCE_DIRECTORY *xresdir;
	    xresdir = find_entry_by_id(iconresdir, LOWORD(pIconId[i]), rootresdir);
            if( !xresdir )
            {
              WARN("icon entry %d not found\n", LOWORD(pIconId[i]));
	      RetPtr[i]=0;
	      continue;
            }
	    xresdir = find_entry_default(xresdir, rootresdir);
	    idataent = (const IMAGE_RESOURCE_DATA_ENTRY*)xresdir;

        idata = RtlImageRvaToVa(RtlImageNtHeader((HMODULE)peimage), (HMODULE)peimage, idataent->OffsetToData, NULL);
        if (!idata)
	    {
	      WARN("no matching real address found for icondata!\n");
	      RetPtr[i]=0;
	      continue;
	    }
	    RetPtr[i] = CreateIconFromResourceEx(idata, idataent->Size, TRUE, 0x00030000, cx1, cy1, flags);
            if (cx2 && cy2)
                RetPtr[++i] = CreateIconFromResourceEx(idata, idataent->Size, TRUE, 0x00030000, cx2, cy2, flags);
	  }
	  ret = i;	/* return number of retrieved icons */
	}			/* if(sig == IMAGE_NT_SIGNATURE) */

end:
	UnmapViewOfFile(peimage);	/* success */
	return ret;
}