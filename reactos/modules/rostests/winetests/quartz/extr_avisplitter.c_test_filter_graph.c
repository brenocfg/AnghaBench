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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * pFilter; } ;
typedef  TYPE_1__ PIN_INFO ;
typedef  scalar_t__ PIN_DIRECTION ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IFileSourceFilter ;
typedef  int /*<<< orphan*/  IEnumPins ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILTER_STATE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_AsyncReader ; 
 int /*<<< orphan*/  CLSID_NullRenderer ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ *) ; 
 scalar_t__ E_NOINTERFACE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ IBaseFilter_EnumPins (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBaseFilter_GetState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBaseFilter_Pause (int /*<<< orphan*/ *) ; 
 scalar_t__ IBaseFilter_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBaseFilter_Run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBaseFilter_Stop (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumPins_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumPins_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumPins_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ IFileSourceFilter_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFileSourceFilter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  IID_IFileSourceFilter ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IPin_Connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_ConnectedTo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPin_Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_QueryDirection (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IPin_QueryPinInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ PINDIR_OUTPUT ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  avifile ; 
 int /*<<< orphan*/ * load_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pAviSplitter ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_filter_graph(void)
{
    IFileSourceFilter *pfile = NULL;
    IBaseFilter *preader = NULL, *pavi = NULL;
    IEnumPins *enumpins = NULL;
    IPin *filepin = NULL, *avipin = NULL;
    HRESULT hr;
    HANDLE file = NULL;
    PIN_DIRECTION dir = PINDIR_OUTPUT;
    char buffer[13];
    DWORD readbytes;
    FILTER_STATE state;

    WCHAR *filename = load_resource(avifile);

    file = CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL);
    if (file == INVALID_HANDLE_VALUE)
    {
        skip("Could not read test file \"%s\", skipping test\n", wine_dbgstr_w(filename));
        DeleteFileW(filename);
        return;
    }

    memset(buffer, 0, 13);
    readbytes = 12;
    ReadFile(file, buffer, readbytes, &readbytes, NULL);
    CloseHandle(file);
    if (strncmp(buffer, "RIFF", 4) || strcmp(buffer + 8, "AVI "))
    {
        skip("%s is not an avi riff file, not doing the avi splitter test\n",
            wine_dbgstr_w(filename));
        DeleteFileW(filename);
        return;
    }

    hr = IUnknown_QueryInterface(pAviSplitter, &IID_IFileSourceFilter,
        (void **)&pfile);
    ok(hr == E_NOINTERFACE,
        "Avi splitter returns unexpected error: %08x\n", hr);
    if (pfile)
        IFileSourceFilter_Release(pfile);
    pfile = NULL;

    hr = CoCreateInstance(&CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER,
        &IID_IBaseFilter, (LPVOID*)&preader);
    ok(hr == S_OK, "Could not create asynchronous reader: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    hr = IBaseFilter_QueryInterface(preader, &IID_IFileSourceFilter,
        (void**)&pfile);
    ok(hr == S_OK, "Could not get IFileSourceFilter: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    hr = IUnknown_QueryInterface(pAviSplitter, &IID_IBaseFilter,
        (void**)&pavi);
    ok(hr == S_OK, "Could not get base filter: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    hr = IFileSourceFilter_Load(pfile, filename, NULL);
    if (hr != S_OK)
    {
        trace("Could not load file: %08x\n", hr);
        goto fail;
    }

    hr = IBaseFilter_EnumPins(preader, &enumpins);
    ok(hr == S_OK, "No enumpins: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    hr = IEnumPins_Next(enumpins, 1, &filepin, NULL);
    ok(hr == S_OK, "No pin: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    IEnumPins_Release(enumpins);
    enumpins = NULL;

    hr = IBaseFilter_EnumPins(pavi, &enumpins);
    ok(hr == S_OK, "No enumpins: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    hr = IEnumPins_Next(enumpins, 1, &avipin, NULL);
    ok(hr == S_OK, "No pin: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    hr = IPin_Connect(filepin, avipin, NULL);
    ok(hr == S_OK, "Could not connect: %08x\n", hr);
    if (hr != S_OK)
        goto fail;

    IPin_Release(avipin);
    avipin = NULL;

    IEnumPins_Reset(enumpins);

    /* Windows puts the pins in the order: Outputpins - Inputpin,
     * wine does the reverse, just don't test it for now
     * Hate to admit it, but windows way makes more sense
     */
    while (IEnumPins_Next(enumpins, 1, &avipin, NULL) == S_OK)
    {
        IPin_QueryDirection(avipin, &dir);
        if (dir == PINDIR_OUTPUT)
        {
            /* Well, connect it to a null renderer! */
            IBaseFilter *pnull = NULL;
            IEnumPins *nullenum = NULL;
            IPin *nullpin = NULL;

            hr = CoCreateInstance(&CLSID_NullRenderer, NULL,
                CLSCTX_INPROC_SERVER, &IID_IBaseFilter, (LPVOID*)&pnull);
            if (hr == REGDB_E_CLASSNOTREG)
            {
                win_skip("Null renderer not registered, skipping\n");
                break;
            }
            ok(hr == S_OK, "Could not create null renderer: %08x\n", hr);

            hr = IBaseFilter_EnumPins(pnull, &nullenum);
            ok(hr == S_OK, "Failed to enum pins, hr %#x.\n", hr);
            hr = IEnumPins_Next(nullenum, 1, &nullpin, NULL);
            ok(hr == S_OK, "Failed to get next pin, hr %#x.\n", hr);
            IEnumPins_Release(nullenum);
            IPin_QueryDirection(nullpin, &dir);

            hr = IPin_Connect(avipin, nullpin, NULL);
            ok(hr == S_OK, "Failed to connect output pin: %08x\n", hr);
            IPin_Release(nullpin);
            if (hr != S_OK)
            {
                IBaseFilter_Release(pnull);
                break;
            }
            IBaseFilter_Run(pnull, 0);
        }

        IPin_Release(avipin);
        avipin = NULL;
    }

    if (avipin)
        IPin_Release(avipin);
    avipin = NULL;

    if (hr != S_OK)
        goto fail2;
    /* At this point there is a minimalistic connected avi splitter that can
     * be used for all sorts of source filter tests. However that still needs
     * to be written at a later time.
     *
     * Interesting tests:
     * - Can you disconnect an output pin while running?
     *   Expecting: Yes
     * - Can you disconnect the pullpin while running?
     *   Expecting: No
     * - Is the reference count incremented during playback or when connected?
     *   Does this happen once for every output pin? Or is there something else
     *   going on.
     *   Expecting: You tell me
     */

    IBaseFilter_Run(preader, 0);
    IBaseFilter_Run(pavi, 0);
    IBaseFilter_GetState(pavi, INFINITE, &state);

    IBaseFilter_Pause(pavi);
    IBaseFilter_Pause(preader);
    IBaseFilter_Stop(pavi);
    IBaseFilter_Stop(preader);
    IBaseFilter_GetState(pavi, INFINITE, &state);
    IBaseFilter_GetState(preader, INFINITE, &state);

fail2:
    IEnumPins_Reset(enumpins);
    while (IEnumPins_Next(enumpins, 1, &avipin, NULL) == S_OK)
    {
        IPin *to = NULL;

        IPin_QueryDirection(avipin, &dir);
        IPin_ConnectedTo(avipin, &to);
        if (to)
        {
            IPin_Release(to);

            if (dir == PINDIR_OUTPUT)
            {
                PIN_INFO info;

                hr = IPin_QueryPinInfo(to, &info);
                ok(hr == S_OK, "Failed to query pin info, hr %#x.\n", hr);

                /* Release twice: Once normal, second from the
                 * previous while loop
                 */
                IBaseFilter_Stop(info.pFilter);
                IPin_Disconnect(to);
                IPin_Disconnect(avipin);
                IBaseFilter_Release(info.pFilter);
                IBaseFilter_Release(info.pFilter);
            }
            else
            {
                IPin_Disconnect(to);
                IPin_Disconnect(avipin);
            }
        }
        IPin_Release(avipin);
        avipin = NULL;
    }

fail:
    if (hr != S_OK)
        skip("Prerequisites not matched, skipping remainder of test\n");
    if (enumpins)
        IEnumPins_Release(enumpins);

    if (avipin)
        IPin_Release(avipin);
    if (filepin)
    {
        IPin *to = NULL;

        IPin_ConnectedTo(filepin, &to);
        if (to)
        {
            IPin_Disconnect(filepin);
            IPin_Disconnect(to);
        }
        IPin_Release(filepin);
    }

    if (preader)
        IBaseFilter_Release(preader);
    if (pavi)
        IBaseFilter_Release(pavi);
    if (pfile)
        IFileSourceFilter_Release(pfile);

    DeleteFileW(filename);
}