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
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IID_IXMLDOMNode ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IXMLDOMDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_loadXML (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IXMLDOMDocument_transformNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int compareIgnoreReturns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 char* szBasicTransformOutput ; 
 char* szBasicTransformSSXMLPart1 ; 
 char* szBasicTransformSSXMLPart2 ; 
 char* szBasicTransformXML ; 
 char* szTypeValueXML ; 

__attribute__((used)) static void test_TransformWithLoadingLocalFile(void)
{
    IXMLDOMDocument *doc;
    IXMLDOMDocument *xsl;
    IXMLDOMNode *pNode;
    VARIANT_BOOL bSucc;
    HRESULT hr;
    HANDLE file;
    DWORD dwWritten;
    char lpPathBuffer[MAX_PATH];
    int i;

    /* Create a Temp File. */
    GetTempPathA(MAX_PATH, lpPathBuffer);
    strcat(lpPathBuffer, "customers.xml" );

    file = CreateFileA(lpPathBuffer, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    ok(file != INVALID_HANDLE_VALUE, "Could not create file: %u\n", GetLastError());
    if(file == INVALID_HANDLE_VALUE)
        return;

    WriteFile(file, szBasicTransformXML, strlen(szBasicTransformXML), &dwWritten, NULL);
    CloseHandle(file);

    /* Correct path to not include an escape character. */
    for(i=0; i < strlen(lpPathBuffer); i++)
    {
        if(lpPathBuffer[i] == '\\')
            lpPathBuffer[i] = '/';
    }

    doc = create_document(&IID_IXMLDOMDocument);
    xsl = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_loadXML(doc, _bstr_(szTypeValueXML), &bSucc);
    ok(hr == S_OK, "ret %08x\n", hr );
    ok(bSucc == VARIANT_TRUE, "Expected VARIANT_TRUE got VARIANT_FALSE\n");
    if(bSucc == VARIANT_TRUE)
    {
        BSTR sXSL;
        BSTR sPart1 = _bstr_(szBasicTransformSSXMLPart1);
        BSTR sPart2 = _bstr_(szBasicTransformSSXMLPart2);
        BSTR sFileName = _bstr_(lpPathBuffer);
        int nLength = lstrlenW(sPart1) + lstrlenW(sPart2) + lstrlenW(sFileName) + 1;

        sXSL = SysAllocStringLen(NULL, nLength);
        lstrcpyW(sXSL, sPart1);
        lstrcatW(sXSL, sFileName);
        lstrcatW(sXSL, sPart2);

        hr = IXMLDOMDocument_loadXML(xsl, sXSL, &bSucc);
        ok(hr == S_OK, "ret %08x\n", hr );
        ok(bSucc == VARIANT_TRUE, "Expected VARIANT_TRUE got VARIANT_FALSE\n");
        if(bSucc == VARIANT_TRUE)
        {
            BSTR sResult;

            hr = IXMLDOMDocument_QueryInterface(xsl, &IID_IXMLDOMNode, (void**)&pNode );
            ok(hr == S_OK, "ret %08x\n", hr );
            if(hr == S_OK)
            {
                /* This will load the temp file via the XSL */
                hr = IXMLDOMDocument_transformNode(doc, pNode, &sResult);
                ok(hr == S_OK, "ret %08x\n", hr );
                if(hr == S_OK)
                {
                    ok( compareIgnoreReturns( sResult, _bstr_(szBasicTransformOutput)), "Stylesheet output not correct\n");
                    SysFreeString(sResult);
                }

                IXMLDOMNode_Release(pNode);
            }
        }

        SysFreeString(sXSL);
    }

    IXMLDOMDocument_Release(doc);
    IXMLDOMDocument_Release(xsl);

    DeleteFileA(lpPathBuffer);
    free_bstrs();
}