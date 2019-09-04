#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_8__ {int options; scalar_t__ dlg_type; size_t filetypeindex; char const* default_ext; int /*<<< orphan*/ * psia_results; int /*<<< orphan*/  custom_title; int /*<<< orphan*/  dlg_hwnd; int /*<<< orphan*/  peb; TYPE_1__* filterspecs; scalar_t__ filterspec_count; scalar_t__ psi_folder; } ;
struct TYPE_7__ {int /*<<< orphan*/  pszSpec; } ;
typedef  int /*<<< orphan*/  SFGAOF ;
typedef  int /*<<< orphan*/  PCUITEMID_CHILD_ARRAY ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IShellItem ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FileDialogImpl ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  COMDLG32_GetCanonicalPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  COMDLG32_SHSimpleIDListFromPathAW (char*) ; 
 int COMDLG32_SplitFileNames (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  COMDLG32_hInstance ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILEDLG95_OnOpenMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILEDLG95_ValidatePathAction (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int FOS_FILEMUSTEXIST ; 
 int FOS_NOVALIDATE ; 
 int FOS_OVERWRITEPROMPT ; 
 int FOS_PICKFOLDERS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_FILENOTEXISTING ; 
 int /*<<< orphan*/  IDS_INVALID_FOLDERNAME ; 
 int /*<<< orphan*/  IExplorerBrowser_BrowseToObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellItemArray_GetAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellItemArray_GetItemAt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IShellItemArray_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellItem_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITEMDLG_TYPE_SAVE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
#define  ONOPEN_BROWSE 130 
#define  ONOPEN_OPEN 129 
#define  ONOPEN_SEARCH 128 
 int /*<<< orphan*/  PathFileExistsW (char*) ; 
 char* PathFindExtensionW (char*) ; 
 int /*<<< orphan*/  SBSP_DEFBROWSER ; 
 int /*<<< orphan*/  SFGAO_FOLDER ; 
 int /*<<< orphan*/  SHCreateShellItemArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SHGetIDListFromObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIATTRIBFLAGS_AND ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  events_OnFileOk (TYPE_2__*) ; 
 int /*<<< orphan*/  events_OnOverwrite (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int get_file_name (TYPE_2__*,int /*<<< orphan*/ **) ; 
 char* get_first_ext_from_spec (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 scalar_t__ lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 scalar_t__ lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shell_item_exists (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT on_default_action(FileDialogImpl *This)
{
    IShellFolder *psf_parent, *psf_desktop;
    LPITEMIDLIST *pidla;
    LPITEMIDLIST current_folder;
    LPWSTR fn_iter, files = NULL, tmp_files;
    UINT file_count = 0, len, i;
    int open_action;
    HRESULT hr, ret = E_FAIL;

    len = get_file_name(This, &tmp_files);
    if(len)
    {
        UINT size_used;
        file_count = COMDLG32_SplitFileNames(tmp_files, len, &files, &size_used);
        CoTaskMemFree(tmp_files);
    }
    if(!file_count) return E_FAIL;

    hr = SHGetIDListFromObject((IUnknown*)This->psi_folder, &current_folder);
    if(FAILED(hr))
    {
        ERR("Failed to get pidl for current directory.\n");
        HeapFree(GetProcessHeap(), 0, files);
        return hr;
    }

    TRACE("Acting on %d file(s).\n", file_count);

    pidla = HeapAlloc(GetProcessHeap(), 0, sizeof(LPITEMIDLIST) * file_count);
    open_action = ONOPEN_OPEN;
    fn_iter = files;

    for(i = 0; i < file_count && open_action == ONOPEN_OPEN; i++)
    {
        WCHAR canon_filename[MAX_PATH];
        psf_parent = NULL;

        COMDLG32_GetCanonicalPath(current_folder, fn_iter, canon_filename);

        if( (This->options & FOS_NOVALIDATE) &&
            !(This->options & FOS_FILEMUSTEXIST) )
            open_action = ONOPEN_OPEN;
        else
            open_action = ONOPEN_BROWSE;

        open_action = FILEDLG95_ValidatePathAction(canon_filename, &psf_parent, This->dlg_hwnd,
                                                   This->options & ~FOS_FILEMUSTEXIST,
                                                   (This->dlg_type == ITEMDLG_TYPE_SAVE),
                                                   open_action);

        /* Add the proper extension */
        if(open_action == ONOPEN_OPEN)
        {
            static const WCHAR dotW[] = {'.',0};

            if(This->dlg_type == ITEMDLG_TYPE_SAVE)
            {
                WCHAR extbuf[MAX_PATH], *newext = NULL;

                if(This->filterspec_count)
                {
                    newext = get_first_ext_from_spec(extbuf, This->filterspecs[This->filetypeindex].pszSpec);
                }
                else if(This->default_ext)
                {
                    lstrcpyW(extbuf, dotW);
                    lstrcatW(extbuf, This->default_ext);
                    newext = extbuf;
                }

                if(newext)
                {
                    WCHAR *ext = PathFindExtensionW(canon_filename);
                    if(lstrcmpW(ext, newext))
                        lstrcatW(canon_filename, newext);
                }
            }
            else
            {
                if( !(This->options & FOS_NOVALIDATE) && (This->options & FOS_FILEMUSTEXIST) &&
                    !PathFileExistsW(canon_filename))
                {
                    if(This->default_ext)
                    {
                        lstrcatW(canon_filename, dotW);
                        lstrcatW(canon_filename, This->default_ext);

                        if(!PathFileExistsW(canon_filename))
                        {
                            FILEDLG95_OnOpenMessage(This->dlg_hwnd, 0, IDS_FILENOTEXISTING);
                            open_action = ONOPEN_BROWSE;
                        }
                    }
                    else
                    {
                        FILEDLG95_OnOpenMessage(This->dlg_hwnd, 0, IDS_FILENOTEXISTING);
                        open_action = ONOPEN_BROWSE;
                    }
                }
            }
        }

        pidla[i] = COMDLG32_SHSimpleIDListFromPathAW(canon_filename);

        if(psf_parent && !(open_action == ONOPEN_BROWSE))
            IShellFolder_Release(psf_parent);

        fn_iter += (WCHAR)lstrlenW(fn_iter) + 1;
    }

    HeapFree(GetProcessHeap(), 0, files);
    ILFree(current_folder);

    if((This->options & FOS_PICKFOLDERS) && open_action == ONOPEN_BROWSE)
        open_action = ONOPEN_OPEN; /* FIXME: Multiple folders? */

    switch(open_action)
    {
    case ONOPEN_SEARCH:
        FIXME("Filtering not implemented.\n");
        break;

    case ONOPEN_BROWSE:
        hr = IExplorerBrowser_BrowseToObject(This->peb, (IUnknown*)psf_parent, SBSP_DEFBROWSER);
        if(FAILED(hr))
            ERR("Failed to browse to directory: %08x\n", hr);

        IShellFolder_Release(psf_parent);
        break;

    case ONOPEN_OPEN:
        hr = SHGetDesktopFolder(&psf_desktop);
        if(SUCCEEDED(hr))
        {
            if(This->psia_results)
            {
                IShellItemArray_Release(This->psia_results);
                This->psia_results = NULL;
            }

            hr = SHCreateShellItemArray(NULL, psf_desktop, file_count, (PCUITEMID_CHILD_ARRAY)pidla,
                                        &This->psia_results);

            IShellFolder_Release(psf_desktop);

            if(FAILED(hr))
                break;

            if(This->options & FOS_PICKFOLDERS)
            {
                SFGAOF attributes;
                hr = IShellItemArray_GetAttributes(This->psia_results, SIATTRIBFLAGS_AND, SFGAO_FOLDER, &attributes);
                if(hr != S_OK)
                {
                    WCHAR buf[64];
                    LoadStringW(COMDLG32_hInstance, IDS_INVALID_FOLDERNAME, buf, ARRAY_SIZE(buf));

                    MessageBoxW(This->dlg_hwnd, buf, This->custom_title, MB_OK | MB_ICONEXCLAMATION);

                    IShellItemArray_Release(This->psia_results);
                    This->psia_results = NULL;
                    break;
                }
            }

            if((This->options & FOS_OVERWRITEPROMPT) && This->dlg_type == ITEMDLG_TYPE_SAVE)
            {
                IShellItem *shellitem;

                for (i=0; SUCCEEDED(hr) && i<file_count; i++)
                {
                    hr = IShellItemArray_GetItemAt(This->psia_results, i, &shellitem);
                    if (SUCCEEDED(hr))
                    {
                        if (shell_item_exists(shellitem))
                            hr = events_OnOverwrite(This, shellitem);

                        IShellItem_Release(shellitem);
                    }
                }

                if (FAILED(hr))
                    break;
            }

            if(events_OnFileOk(This) == S_OK)
                ret = S_OK;
        }
        break;

    default:
        ERR("Failed.\n");
        break;
    }

    /* Clean up */
    for(i = 0; i < file_count; i++)
        ILFree(pidla[i]);
    HeapFree(GetProcessHeap(), 0, pidla);

    /* Success closes the dialog */
    return ret;
}