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
typedef  int /*<<< orphan*/  IWMReaderTypeNegotiation ;
typedef  int /*<<< orphan*/  IWMReaderTimecode ;
typedef  int /*<<< orphan*/  IWMReaderStreamClock ;
typedef  int /*<<< orphan*/  IWMReaderPlaylistBurn ;
typedef  int /*<<< orphan*/  IWMReaderNetworkConfig2 ;
typedef  int /*<<< orphan*/  IWMReaderNetworkConfig ;
typedef  int /*<<< orphan*/  IWMReaderAdvanced2 ;
typedef  int /*<<< orphan*/  IWMReaderAdvanced ;
typedef  int /*<<< orphan*/  IWMReaderAccelerator ;
typedef  int /*<<< orphan*/  IWMReader ;
typedef  int /*<<< orphan*/  IWMProfile3 ;
typedef  int /*<<< orphan*/  IWMProfile2 ;
typedef  int /*<<< orphan*/  IWMProfile ;
typedef  int /*<<< orphan*/  IWMPacketSize2 ;
typedef  int /*<<< orphan*/  IWMPacketSize ;
typedef  int /*<<< orphan*/  IWMLanguageList ;
typedef  int /*<<< orphan*/  IWMHeaderInfo3 ;
typedef  int /*<<< orphan*/  IWMHeaderInfo2 ;
typedef  int /*<<< orphan*/  IWMHeaderInfo ;
typedef  int /*<<< orphan*/  IWMDRMReader3 ;
typedef  int /*<<< orphan*/  IWMDRMReader2 ;
typedef  int /*<<< orphan*/  IWMDRMReader ;
typedef  int /*<<< orphan*/  IReferenceClock ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 int /*<<< orphan*/  IID_IWMDRMReader ; 
 int /*<<< orphan*/  IID_IWMDRMReader2 ; 
 int /*<<< orphan*/  IID_IWMDRMReader3 ; 
 int /*<<< orphan*/  IID_IWMHeaderInfo ; 
 int /*<<< orphan*/  IID_IWMHeaderInfo2 ; 
 int /*<<< orphan*/  IID_IWMHeaderInfo3 ; 
 int /*<<< orphan*/  IID_IWMLanguageList ; 
 int /*<<< orphan*/  IID_IWMPacketSize ; 
 int /*<<< orphan*/  IID_IWMPacketSize2 ; 
 int /*<<< orphan*/  IID_IWMProfile ; 
 int /*<<< orphan*/  IID_IWMProfile2 ; 
 int /*<<< orphan*/  IID_IWMProfile3 ; 
 int /*<<< orphan*/  IID_IWMReaderAccelerator ; 
 int /*<<< orphan*/  IID_IWMReaderAdvanced ; 
 int /*<<< orphan*/  IID_IWMReaderAdvanced2 ; 
 int /*<<< orphan*/  IID_IWMReaderNetworkConfig ; 
 int /*<<< orphan*/  IID_IWMReaderNetworkConfig2 ; 
 int /*<<< orphan*/  IID_IWMReaderPlaylistBurn ; 
 int /*<<< orphan*/  IID_IWMReaderStreamClock ; 
 int /*<<< orphan*/  IID_IWMReaderTimecode ; 
 int /*<<< orphan*/  IID_IWMReaderTypeNegotiation ; 
 int /*<<< orphan*/  IReferenceClock_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMHeaderInfo2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMHeaderInfo3_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMHeaderInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMLanguageList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMPacketSize2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMPacketSize_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMProfile2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMProfile3_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMProfile_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderAccelerator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderAdvanced2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderAdvanced_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderNetworkConfig2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderNetworkConfig_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderPlaylistBurn_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderStreamClock_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderTimecode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWMReaderTypeNegotiation_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWMReader_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWMReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WMCreateReader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_wmreader_interfaces(void)
{
    HRESULT hr;
    IWMReader          *reader;
    IWMReaderAdvanced  *advanced;
    IWMReaderAdvanced2 *advanced2;
    IWMHeaderInfo      *header;
    IWMHeaderInfo2     *header2;
    IWMHeaderInfo3     *header3;
    IWMProfile         *profile;
    IWMProfile2        *profile2;
    IWMProfile3        *profile3;
    IWMPacketSize      *packet;
    IWMPacketSize2     *packet2;
    IWMReaderAccelerator     *accel;
    IWMReaderTimecode        *timecode;
    IWMReaderNetworkConfig   *netconfig;
    IWMReaderNetworkConfig2  *netconfig2;
    IWMReaderStreamClock     *clock;
    IWMReaderTypeNegotiation *negotiation;
    IWMDRMReader       *drmreader;
    IWMDRMReader2      *drmreader2;
    IWMDRMReader3      *drmreader3;
    IWMReaderPlaylistBurn *playlist;
    IWMLanguageList       *langlist;
    IReferenceClock       *refclock;

    hr = WMCreateReader( NULL, 0, &reader );
    ok(hr == S_OK, "WMCreateReader failed 0x%08x\n", hr);
    if(FAILED(hr))
    {
        win_skip("Failed to create IWMReader\n");
        return;
    }

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderAdvanced, (void **)&advanced);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderAdvanced2, (void **)&advanced2);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMHeaderInfo, (void **)&header);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMHeaderInfo2, (void **)&header2);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMHeaderInfo3, (void **)&header3);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMProfile, (void **)&profile);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMProfile2, (void **)&profile2);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMProfile3, (void **)&profile3);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMPacketSize, (void **)&packet);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMPacketSize2, (void **)&packet2);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderAccelerator, (void **)&accel);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderTimecode, (void **)&timecode);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderNetworkConfig, (void **)&netconfig);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderNetworkConfig2, (void **)&netconfig2);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderStreamClock, (void **)&clock);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderTypeNegotiation, (void **)&negotiation);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMDRMReader, (void **)&drmreader);
    ok(hr == E_NOINTERFACE, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMDRMReader2, (void **)&drmreader2);
    ok(hr == E_NOINTERFACE, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMDRMReader3, (void **)&drmreader3);
    ok(hr == E_NOINTERFACE, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderPlaylistBurn, (void **)&playlist);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMLanguageList, (void **)&langlist);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IReferenceClock, (void **)&refclock);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    if(packet)
        IWMPacketSize_Release(packet);
    if(packet2)
        IWMPacketSize2_Release(packet2);
    if(advanced)
        IWMReaderAdvanced_Release(advanced);
    if(advanced2)
        IWMReaderAdvanced2_Release(advanced2);
    if(profile)
        IWMProfile_Release(profile);
    if(profile2)
        IWMProfile2_Release(profile2);
    if(profile3)
        IWMProfile3_Release(profile3);
    if(header)
        IWMHeaderInfo_Release(header);
    if(header2)
        IWMHeaderInfo2_Release(header2);
    if(header3)
        IWMHeaderInfo3_Release(header3);
    if(accel)
        IWMReaderAccelerator_Release(accel);
    if(timecode)
        IWMReaderTimecode_Release(timecode);
    if(netconfig)
        IWMReaderNetworkConfig_Release(netconfig);
    if(netconfig2)
        IWMReaderNetworkConfig2_Release(netconfig2);
    if(clock)
        IWMReaderStreamClock_Release(clock);
    if(negotiation)
        IWMReaderTypeNegotiation_Release(negotiation);
    if(playlist)
        IWMReaderPlaylistBurn_Release(playlist);
    if(langlist)
        IWMLanguageList_Release(langlist);
    if(refclock)
        IReferenceClock_Release(refclock);

    IWMReader_Release(reader);
}