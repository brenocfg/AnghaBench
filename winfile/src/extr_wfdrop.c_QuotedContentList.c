#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sm_content ;
typedef  char WCHAR ;
struct TYPE_25__ {char* cFileName; } ;
struct TYPE_24__ {unsigned int cItems; TYPE_6__* fgd; } ;
struct TYPE_23__ {unsigned short member_0; int member_3; unsigned int lindex; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_22__ {TYPE_1__* lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/  hGlobal; int /*<<< orphan*/  pstm; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {scalar_t__ (* QueryGetData ) (TYPE_3__*,TYPE_4__*) ;scalar_t__ (* GetData ) (TYPE_3__*,TYPE_4__*,TYPE_2__*) ;} ;
typedef  char TCHAR ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  char* LPWSTR ;
typedef  TYPE_3__ IDataObject ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  TYPE_4__ FORMATETC ;
typedef  TYPE_5__ FILEGROUPDESCRIPTOR ;
typedef  TYPE_6__ FILEDESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (char*) ; 
 int /*<<< orphan*/  CFSTR_FILECONTENTS ; 
 int /*<<< orphan*/  CFSTR_FILEDESCRIPTOR ; 
 int /*<<< orphan*/  CheckEsc (char*) ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int /*<<< orphan*/  GetTempPath (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 unsigned short RegisterClipboardFormat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StreamToFile (int /*<<< orphan*/ ,char*) ; 
 char* TEXT (char*) ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 int /*<<< orphan*/  TYMED_ISTREAM ; 
 int /*<<< orphan*/  lstrcat (char*,char*) ; 
 int /*<<< orphan*/  lstrcpy (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ stub2 (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ stub3 (TYPE_3__*,TYPE_4__*,TYPE_2__*) ; 
 scalar_t__ stub4 (TYPE_3__*,TYPE_4__*,TYPE_2__*) ; 
 int wcslen (char*) ; 

LPWSTR QuotedContentList(IDataObject *pDataObject)
{
    FILEGROUPDESCRIPTOR *file_group_descriptor;
    FILEDESCRIPTOR file_descriptor;
	HRESULT hr;
	LPWSTR szFiles = NULL;

    unsigned short cp_format_descriptor = RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR);
    unsigned short cp_format_contents = RegisterClipboardFormat(CFSTR_FILECONTENTS);

    //Set up format structure for the descriptor and contents
    FORMATETC descriptor_format = {cp_format_descriptor, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
    FORMATETC contents_format = {cp_format_contents, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

    // Check for descriptor format type
    hr = pDataObject->lpVtbl->QueryGetData(pDataObject, &descriptor_format);
    if (hr == S_OK) 
	{ 
		// Check for contents format type
        hr = pDataObject->lpVtbl->QueryGetData(pDataObject, &contents_format);
        if (hr == S_OK)
		{ 
            // Get the descriptor information
            STGMEDIUM sm_desc= {0,0,0};
            STGMEDIUM sm_content = {0,0,0};
			unsigned int file_index, cchTempPath, cchFiles;
            WCHAR szTempPath[MAX_PATH+1];

            hr = pDataObject->lpVtbl->GetData(pDataObject, &descriptor_format, &sm_desc);
			if (hr != S_OK)
				return NULL;

            file_group_descriptor = (FILEGROUPDESCRIPTOR *) GlobalLock(sm_desc.hGlobal);

			GetTempPath(MAX_PATH, szTempPath);
			cchTempPath = wcslen(szTempPath);

			// calc total size of file names
			cchFiles = 0;
            for (file_index = 0; file_index < file_group_descriptor->cItems; file_index++) 
			{
                file_descriptor = file_group_descriptor->fgd[file_index];
				cchFiles += 1 + cchTempPath + 1 + wcslen(file_descriptor.cFileName) + 2;
			}

			szFiles = (LPWSTR)LocalAlloc(LMEM_FIXED, cchFiles * sizeof(WCHAR));
			szFiles[0] = '\0';

            // For each file, get the name and copy the stream to a file
            for (file_index = 0; file_index < file_group_descriptor->cItems; file_index++)
			{
                file_descriptor = file_group_descriptor->fgd[file_index];
                contents_format.lindex = file_index;
				memset(&sm_content, 0, sizeof(sm_content));
                hr = pDataObject->lpVtbl->GetData(pDataObject, &contents_format, &sm_content);

                if (hr == S_OK) 
				{
					// Dump stream to a file
					TCHAR szTempFile[MAXPATHLEN*2+1];

					lstrcpy(szTempFile, szTempPath);
		            AddBackslash(szTempFile);
				    lstrcat(szTempFile, file_descriptor.cFileName);

					// TODO: make sure all directories between the temp directory and the file have been created
					// paste from zip archives result in file_descriptor.cFileName with intermediate directories

					hr = StreamToFile(sm_content.pstm, szTempFile);

					if (hr == S_OK)
					{
						CheckEsc(szTempFile);

						if (szFiles[0] != '\0')
							lstrcat(szFiles, TEXT(" "));
						lstrcat(szFiles, szTempFile);
					}

					ReleaseStgMedium(&sm_content);
                }
            }

            GlobalUnlock(sm_desc.hGlobal);
            ReleaseStgMedium(&sm_desc);

			if (szFiles[0] == '\0')
			{
				// nothing to copy
				MessageBeep(0);
				LocalFree((HLOCAL)szFiles);	
				szFiles = NULL;
			}
        }
	}
    return szFiles;
}