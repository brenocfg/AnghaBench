#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
struct TYPE_4__ {char* filename; int /*<<< orphan*/  LastWriteTime; int /*<<< orphan*/  encoding; int /*<<< orphan*/ * section; scalar_t__ changed; } ;
typedef  TYPE_1__ PROFILE ;
typedef  int /*<<< orphan*/  LastWriteTime ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char const* LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* CurProfile ; 
 int /*<<< orphan*/  ENCODING_ANSI ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetFileTime (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFullPathNameW (char const*,int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 TYPE_1__** MRUProfile ; 
 int N_CACHED_PROFILES ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PROFILE_FlushFile () ; 
 int /*<<< orphan*/  PROFILE_Free (int /*<<< orphan*/ *) ; 
 void* PROFILE_Load (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROFILE_ReleaseFile () ; 
 scalar_t__ RELATIVE_PATH ; 
 scalar_t__ RtlDetermineDosPathNameType_U (char const*) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int,...) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int debugstr_w (char*) ; 
 scalar_t__ is_not_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strchrW (char const*,char) ; 
 int /*<<< orphan*/  strcmpiW (char*,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 
 char* wininiW ; 

__attribute__((used)) static BOOL PROFILE_Open( LPCWSTR filename, BOOL write_access )
{
    WCHAR buffer[MAX_PATH];
    HANDLE hFile = INVALID_HANDLE_VALUE;
    FILETIME LastWriteTime;
    int i,j;
    PROFILE *tempProfile;
    
    ZeroMemory(&LastWriteTime, sizeof(LastWriteTime));

    /* First time around */

    if(!CurProfile)
       for(i=0;i<N_CACHED_PROFILES;i++)
       {
          MRUProfile[i]=HeapAlloc( GetProcessHeap(), 0, sizeof(PROFILE) );
          if(MRUProfile[i] == NULL) break;
          MRUProfile[i]->changed=FALSE;
          MRUProfile[i]->section=NULL;
          MRUProfile[i]->filename=NULL;
          MRUProfile[i]->encoding=ENCODING_ANSI;
          ZeroMemory(&MRUProfile[i]->LastWriteTime, sizeof(FILETIME));
       }

    if (!filename)
	filename = wininiW;

#ifdef __REACTOS__
    if ((RtlDetermineDosPathNameType_U(filename) == RtlPathTypeRelative) &&
#else
    if ((RtlDetermineDosPathNameType_U(filename) == RELATIVE_PATH) &&
#endif
        !strchrW(filename, '\\') && !strchrW(filename, '/'))
    {
        static const WCHAR wszSeparator[] = {'\\', 0};
        WCHAR windirW[MAX_PATH];
        GetWindowsDirectoryW( windirW, MAX_PATH );
        strcpyW(buffer, windirW);
        strcatW(buffer, wszSeparator);
        strcatW(buffer, filename);
    }
    else
    {
        LPWSTR dummy;
        GetFullPathNameW(filename, sizeof(buffer)/sizeof(buffer[0]), buffer, &dummy);
    }
        
    TRACE("path: %s\n", debugstr_w(buffer));

    hFile = CreateFileW(buffer, GENERIC_READ | (write_access ? GENERIC_WRITE : 0),
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((hFile == INVALID_HANDLE_VALUE) && (GetLastError() != ERROR_FILE_NOT_FOUND))
    {
        WARN("Error %d opening file %s\n", GetLastError(), debugstr_w(buffer));
        return FALSE;
    }

    for(i=0;i<N_CACHED_PROFILES;i++)
    {
        if ((MRUProfile[i]->filename && !strcmpiW( buffer, MRUProfile[i]->filename )))
        {
            TRACE("MRU Filename: %s, new filename: %s\n", debugstr_w(MRUProfile[i]->filename), debugstr_w(buffer));
            if(i)
            {
                PROFILE_FlushFile();
                tempProfile=MRUProfile[i];
                for(j=i;j>0;j--)
                    MRUProfile[j]=MRUProfile[j-1];
                CurProfile=tempProfile;
            }

            if (hFile != INVALID_HANDLE_VALUE)
            {
                GetFileTime(hFile, NULL, NULL, &LastWriteTime);
                if (!memcmp( &CurProfile->LastWriteTime, &LastWriteTime, sizeof(FILETIME) ) &&
                    is_not_current(&LastWriteTime))
                    TRACE("(%s): already opened (mru=%d)\n",
                          debugstr_w(buffer), i);
                else
                {
                    TRACE("(%s): already opened, needs refreshing (mru=%d)\n",
                          debugstr_w(buffer), i);
                    PROFILE_Free(CurProfile->section);
                    CurProfile->section = PROFILE_Load(hFile, &CurProfile->encoding);
                    CurProfile->LastWriteTime = LastWriteTime;
                }
                CloseHandle(hFile);
                return TRUE;
            }
            else TRACE("(%s): already opened, not yet created (mru=%d)\n",
                       debugstr_w(buffer), i);
        }
    }

    /* Flush the old current profile */
    PROFILE_FlushFile();

    /* Make the oldest profile the current one only in order to get rid of it */
    if(i==N_CACHED_PROFILES)
      {
       tempProfile=MRUProfile[N_CACHED_PROFILES-1];
       for(i=N_CACHED_PROFILES-1;i>0;i--)
          MRUProfile[i]=MRUProfile[i-1];
       CurProfile=tempProfile;
      }
    if(CurProfile->filename) PROFILE_ReleaseFile();

    /* OK, now that CurProfile is definitely free we assign it our new file */
    CurProfile->filename  = HeapAlloc( GetProcessHeap(), 0, (strlenW(buffer)+1) * sizeof(WCHAR) );
    strcpyW( CurProfile->filename, buffer );

    if (hFile != INVALID_HANDLE_VALUE)
    {
        CurProfile->section = PROFILE_Load(hFile, &CurProfile->encoding);
        GetFileTime(hFile, NULL, NULL, &CurProfile->LastWriteTime);
        CloseHandle(hFile);
    }
    else
    {
        /* Does not exist yet, we will create it in PROFILE_FlushFile */
        WARN("profile file %s not found\n", debugstr_w(buffer) );
    }
    return TRUE;
}