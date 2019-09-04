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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int CANOF_PARSE_DISPLAY_NAME ; 
 int CANOF_SET_DEFAULT_VALUES ; 
 int /*<<< orphan*/ * CreateAssemblyNameObject (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAssemblyName_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  const* wine10W ; 
 int /*<<< orphan*/  const* wine1W ; 
 int /*<<< orphan*/  const* wine2W ; 
 int /*<<< orphan*/  const* wine3W ; 
 int /*<<< orphan*/  const* wine4W ; 
 int /*<<< orphan*/  const* wine5W ; 
 int /*<<< orphan*/  const* wine6W ; 
 int /*<<< orphan*/  const* wine7W ; 
 int /*<<< orphan*/  const* wine8W ; 
 int /*<<< orphan*/  const* wine9W ; 

__attribute__((used)) static void test_CreateAssemblyNameObject( void )
{
    static const WCHAR emptyW[] = {0};
    IAssemblyName *name;
    HRESULT hr;

    hr = CreateAssemblyNameObject( NULL, wine1W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr);

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine1W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    hr = CreateAssemblyNameObject( NULL, wine1W, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine1W, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    hr = CreateAssemblyNameObject( NULL, wine1W, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine1W, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    hr = CreateAssemblyNameObject( NULL, wine1W, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine1W, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine2W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine3W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine4W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == HRESULT_FROM_WIN32( ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME ),
        "expected ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine5W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == HRESULT_FROM_WIN32( ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME ),
        "expected ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine6W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine7W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine8W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine9W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine10W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );
}