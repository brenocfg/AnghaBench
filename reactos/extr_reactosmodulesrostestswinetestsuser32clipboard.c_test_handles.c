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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* HGLOBAL ;
typedef  void* HBITMAP ;
typedef  void* HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int CF_BITMAP ; 
 int CF_DIB ; 
 int CF_DIBV5 ; 
 int CF_DSPBITMAP ; 
 int CF_GDIOBJFIRST ; 
 int CF_LOCALE ; 
 int CF_OEMTEXT ; 
 int CF_PALETTE ; 
 int CF_PRIVATEFIRST ; 
 int CF_TEXT ; 
 int CF_UNICODETEXT ; 
 int CloseClipboard () ; 
 void* CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 void* CreatePalette (int /*<<< orphan*/ *) ; 
 int EmptyClipboard () ; 
 int /*<<< orphan*/  GMEM_FIXED ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 void* GetClipboardData (int) ; 
 scalar_t__ GetCurrentProcessId () ; 
 void* GetLastError () ; 
 scalar_t__ GetObjectType (void*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetWindowThreadProcessId (int /*<<< orphan*/ ,scalar_t__*) ; 
 void* GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GlobalFree (void*) ; 
 void* GlobalSize (void*) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ OBJ_BITMAP ; 
 scalar_t__ OBJ_PAL ; 
 int OpenClipboard (int /*<<< orphan*/ ) ; 
 int RegisterClipboardFormatA (char*) ; 
 void* SetClipboardData (int,void*) ; 
 void* bitmap ; 
 void* bitmap2 ; 
 scalar_t__ broken (int) ; 
 void* create_textA () ; 
 int format_id ; 
 int is_fixed (void*) ; 
 int is_freed (void*) ; 
 int is_moveable (void*) ; 
 int /*<<< orphan*/  logpalette ; 
 int /*<<< orphan*/  ok (int,char*,void*,...) ; 
 void* palette ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_handles( HWND hwnd )
{
    HGLOBAL h, htext, htext2, htext3, htext4, htext5;
    HGLOBAL hfixed, hfixed2, hmoveable, empty_fixed, empty_moveable;
    void *ptr;
    UINT format_id2 = RegisterClipboardFormatA( "another format" );
    BOOL r;
    HANDLE data;
    HBITMAP bitmap_temp;
    DWORD process;
    BOOL is_owner = (GetWindowThreadProcessId( hwnd, &process ) && process == GetCurrentProcessId());

    trace( "hwnd %p\n", hwnd );
    htext = create_textA();
    htext2 = create_textA();
    htext3 = create_textA();
    htext4 = create_textA();
    htext5 = create_textA();
    bitmap = CreateBitmap( 10, 10, 1, 1, NULL );
    bitmap2 = CreateBitmap( 10, 10, 1, 1, NULL );
    palette = CreatePalette( &logpalette );

    hfixed = GlobalAlloc( GMEM_FIXED, 17 );
    hfixed2 = GlobalAlloc( GMEM_FIXED, 17 );
    ok( is_fixed( hfixed ), "expected fixed mem %p\n", hfixed );
    ok( GlobalSize( hfixed ) == 17, "wrong size %lu\n", GlobalSize( hfixed ));

    hmoveable = GlobalAlloc( GMEM_MOVEABLE, 23 );
    ok( is_moveable( hmoveable ), "expected moveable mem %p\n", hmoveable );
    ok( GlobalSize( hmoveable ) == 23, "wrong size %lu\n", GlobalSize( hmoveable ));

    empty_fixed = GlobalAlloc( GMEM_FIXED, 0 );
    ok( is_fixed( empty_fixed ), "expected fixed mem %p\n", empty_fixed );

    empty_moveable = GlobalAlloc( GMEM_MOVEABLE, 0 );
    /* discarded handles can't be GlobalLock'ed */
    ok( is_freed( empty_moveable ), "expected free mem %p\n", empty_moveable );

    r = OpenClipboard( hwnd );
    ok( r, "gle %d\n", GetLastError() );
    r = EmptyClipboard();
    ok( r, "gle %d\n", GetLastError() );

    h = SetClipboardData( CF_TEXT, htext );
    ok( h == htext, "got %p\n", h );
    ok( is_moveable( h ), "expected moveable mem %p\n", h );
    h = SetClipboardData( format_id, htext2 );
    ok( h == htext2, "got %p\n", h );
    ok( is_moveable( h ), "expected moveable mem %p\n", h );
    bitmap_temp = CreateBitmap( 10, 10, 1, 1, NULL );
    h = SetClipboardData( CF_BITMAP, bitmap_temp );
    ok( h == bitmap_temp, "got %p\n", h );
    ok( GetObjectType( h ) == OBJ_BITMAP, "expected bitmap %p\n", h );
    h = SetClipboardData( CF_BITMAP, bitmap );
    ok( h == bitmap, "got %p\n", h );
    ok( GetObjectType( h ) == OBJ_BITMAP, "expected bitmap %p\n", h );
    ok( !GetObjectType( bitmap_temp ), "expected free object %p\n", bitmap_temp );
    h = SetClipboardData( CF_DSPBITMAP, bitmap2 );
    ok( h == bitmap2, "got %p\n", h );
    ok( GetObjectType( h ) == OBJ_BITMAP, "expected bitmap %p\n", h );
    h = SetClipboardData( CF_PALETTE, palette );
    ok( h == palette, "got %p\n", h );
    ok( GetObjectType( h ) == OBJ_PAL, "expected palette %p\n", h );
    h = SetClipboardData( CF_GDIOBJFIRST + 3, htext3 );
    ok( h == htext3, "got %p\n", h );
    ok( is_moveable( h ), "expected moveable mem %p\n", h );
    h = SetClipboardData( CF_PRIVATEFIRST + 7, htext5 );
    ok( h == htext5, "got %p\n", h );
    ok( is_moveable( h ), "expected moveable mem %p\n", h );
    h = SetClipboardData( format_id2, empty_moveable );
    ok( !h, "got %p\n", h );
    GlobalFree( empty_moveable );

    if (0)  /* crashes on vista64 */
    {
        ptr = HeapAlloc( GetProcessHeap(), 0, 0 );
        h = SetClipboardData( format_id2, ptr );
        ok( !h, "got %p\n", h );
        HeapFree( GetProcessHeap(), 0, ptr );
    }

    h = SetClipboardData( format_id2, empty_fixed );
    ok( h == empty_fixed, "got %p\n", h );
    ok( is_fixed( h ), "expected fixed mem %p\n", h );
    h = SetClipboardData( 0xdeadbeef, hfixed2 );
    ok( h == hfixed2, "got %p\n", h );
    ok( is_fixed( h ), "expected fixed mem %p\n", h );
    h = SetClipboardData( 0xdeadbabe, hmoveable );
    ok( h == hmoveable, "got %p\n", h );
    ok( is_moveable( h ), "expected moveable mem %p\n", h );

    ptr = HeapAlloc( GetProcessHeap(), 0, 37 );
    h = SetClipboardData( 0xdeadfade, ptr );
    ok( h == ptr || !h, "got %p\n", h );
    if (!h)  /* heap blocks are rejected on >= win8 */
    {
        HeapFree( GetProcessHeap(), 0, ptr );
        ptr = NULL;
    }

    data = GetClipboardData( CF_TEXT );
    ok( data == htext, "wrong data %p\n", data );
    ok( is_moveable( data ), "expected moveable mem %p\n", data );

    data = GetClipboardData( format_id );
    ok( data == htext2, "wrong data %p, cf %08x\n", data, format_id );
    ok( is_moveable( data ), "expected moveable mem %p\n", data );

    data = GetClipboardData( CF_GDIOBJFIRST + 3 );
    ok( data == htext3, "wrong data %p\n", data );
    ok( is_moveable( data ), "expected moveable mem %p\n", data );

    data = GetClipboardData( CF_PRIVATEFIRST + 7 );
    ok( data == htext5, "wrong data %p\n", data );
    ok( is_moveable( data ), "expected moveable mem %p\n", data );

    data = GetClipboardData( format_id2 );
    ok( data == empty_fixed, "wrong data %p\n", data );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );

    data = GetClipboardData( 0xdeadbeef );
    ok( data == hfixed2, "wrong data %p\n", data );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );

    data = GetClipboardData( 0xdeadbabe );
    ok( data == hmoveable, "wrong data %p\n", data );
    ok( is_moveable( data ), "expected moveable mem %p\n", data );

    data = GetClipboardData( 0xdeadfade );
    ok( data == ptr, "wrong data %p\n", data );

    h = SetClipboardData( CF_PRIVATEFIRST + 7, htext4 );
    ok( h == htext4, "got %p\n", h );
    ok( is_moveable( h ), "expected moveable mem %p\n", h );
    ok( is_freed( htext5 ), "expected freed mem %p\n", htext5 );

    h = SetClipboardData( 0xdeadbeef, hfixed );
    ok( h == hfixed, "got %p\n", h );
    ok( is_fixed( h ), "expected fixed mem %p\n", h );
    if (0) /* this test is unreliable / crashes */
        ok( is_freed( hfixed2 ), "expected freed mem %p\n", hfixed2 );

    r = CloseClipboard();
    ok( r, "gle %d\n", GetLastError() );

    /* data handles are still valid */
    ok( is_moveable( htext ), "expected moveable mem %p\n", htext );
    ok( is_moveable( htext2 ), "expected moveable mem %p\n", htext2 );
    ok( is_moveable( htext3 ), "expected moveable mem %p\n", htext3 );
    ok( is_moveable( htext4 ), "expected moveable mem %p\n", htext4 );
    ok( GetObjectType( bitmap ) == OBJ_BITMAP, "expected bitmap %p\n", bitmap );
    ok( GetObjectType( bitmap2 ) == OBJ_BITMAP, "expected bitmap %p\n", bitmap2 );
    ok( GetObjectType( palette ) == OBJ_PAL, "expected palette %p\n", palette );
    ok( is_fixed( hfixed ), "expected fixed mem %p\n", hfixed );
    ok( is_moveable( hmoveable ), "expected moveable mem %p\n", hmoveable );
    ok( is_fixed( empty_fixed ), "expected fixed mem %p\n", empty_fixed );

    r = OpenClipboard( hwnd );
    ok( r, "gle %d\n", GetLastError() );

    /* and now they are freed, unless we are the owner */
    if (!is_owner)
    {
        ok( is_freed( htext ), "expected freed mem %p\n", htext );
        ok( is_freed( htext2 ), "expected freed mem %p\n", htext2 );
        ok( is_freed( htext3 ), "expected freed mem %p\n", htext3 );
        ok( is_freed( htext4 ), "expected freed mem %p\n", htext4 );
        ok( is_freed( hmoveable ), "expected freed mem %p\n", hmoveable );

        data = GetClipboardData( CF_TEXT );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );

        data = GetClipboardData( format_id );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );

        data = GetClipboardData( CF_GDIOBJFIRST + 3 );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );

        data = GetClipboardData( CF_PRIVATEFIRST + 7 );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );

        data = GetClipboardData( format_id2 );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );
        ok( GlobalSize( data ) == 1, "wrong size %lu\n", GlobalSize( data ));

        data = GetClipboardData( 0xdeadbeef );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );
        ok( GlobalSize( data ) == 17, "wrong size %lu\n", GlobalSize( data ));

        data = GetClipboardData( 0xdeadbabe );
        ok( is_fixed( data ), "expected fixed mem %p\n", data );
        ok( GlobalSize( data ) == 23, "wrong size %lu\n", GlobalSize( data ));

        data = GetClipboardData( 0xdeadfade );
        ok( is_fixed( data ) || !ptr, "expected fixed mem %p\n", data );
        if (ptr) ok( GlobalSize( data ) == 37, "wrong size %lu\n", GlobalSize( data ));
    }
    else
    {
        ok( is_moveable( htext ), "expected moveable mem %p\n", htext );
        ok( is_moveable( htext2 ), "expected moveable mem %p\n", htext2 );
        ok( is_moveable( htext3 ), "expected moveable mem %p\n", htext3 );
        ok( is_moveable( htext4 ), "expected moveable mem %p\n", htext4 );
        ok( is_moveable( hmoveable ), "expected moveable mem %p\n", hmoveable );

        data = GetClipboardData( CF_TEXT );
        ok( data == htext, "wrong data %p\n", data );

        data = GetClipboardData( format_id );
        ok( data == htext2, "wrong data %p, cf %08x\n", data, format_id );

        data = GetClipboardData( CF_GDIOBJFIRST + 3 );
        ok( data == htext3, "wrong data %p\n", data );

        data = GetClipboardData( CF_PRIVATEFIRST + 7 );
        ok( data == htext4, "wrong data %p\n", data );

        data = GetClipboardData( format_id2 );
        ok( data == empty_fixed, "wrong data %p\n", data );

        data = GetClipboardData( 0xdeadbeef );
        ok( data == hfixed, "wrong data %p\n", data );

        data = GetClipboardData( 0xdeadbabe );
        ok( data == hmoveable, "wrong data %p\n", data );

        data = GetClipboardData( 0xdeadfade );
        ok( data == ptr, "wrong data %p\n", data );
    }

    data = GetClipboardData( CF_OEMTEXT );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );
    data = GetClipboardData( CF_UNICODETEXT );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );
    data = GetClipboardData( CF_LOCALE );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );
    data = GetClipboardData( CF_BITMAP );
    ok( data == bitmap, "expected bitmap %p\n", data );
    data = GetClipboardData( CF_DSPBITMAP );
    ok( data == bitmap2, "expected bitmap %p\n", data );
    data = GetClipboardData( CF_PALETTE );
    ok( data == palette, "expected palette %p\n", data );
    data = GetClipboardData( CF_DIB );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );
    data = GetClipboardData( CF_DIBV5 );
    ok( is_fixed( data ), "expected fixed mem %p\n", data );

    ok( GetObjectType( bitmap ) == OBJ_BITMAP, "expected bitmap %p\n", bitmap );
    ok( GetObjectType( bitmap2 ) == OBJ_BITMAP, "expected bitmap %p\n", bitmap2 );
    ok( GetObjectType( palette ) == OBJ_PAL, "expected palette %p\n", palette );
    ok( is_fixed( hfixed ), "expected fixed mem %p\n", hfixed );
    ok( is_fixed( empty_fixed ), "expected fixed mem %p\n", empty_fixed );

    r = EmptyClipboard();
    ok( r, "gle %d\n", GetLastError() );

    /* w2003, w2008 don't seem to free the data here */
    ok( is_freed( htext ) || broken( !is_freed( htext )), "expected freed mem %p\n", htext );
    ok( is_freed( htext2 ) || broken( !is_freed( htext2 )), "expected freed mem %p\n", htext2 );
    ok( is_freed( htext3 ) || broken( !is_freed( htext3 )), "expected freed mem %p\n", htext3 );
    ok( is_freed( htext4 ) || broken( !is_freed( htext4 )), "expected freed mem %p\n", htext4 );
    ok( is_freed( hmoveable ) || broken( !is_freed( hmoveable )), "expected freed mem %p\n", hmoveable );
    ok( is_fixed( empty_fixed ), "expected fixed mem %p\n", empty_fixed );
    ok( is_fixed( hfixed ), "expected fixed mem %p\n", hfixed );
    ok( !GetObjectType( bitmap ), "expected freed handle %p\n", bitmap );
    ok( !GetObjectType( bitmap2 ), "expected freed handle %p\n", bitmap2 );
    ok( !GetObjectType( palette ), "expected freed handle %p\n", palette );

    r = CloseClipboard();
    ok( r, "gle %d\n", GetLastError() );
}