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
typedef  float LONG ;
typedef  int /*<<< orphan*/  ITextFont ;
typedef  float HRESULT ;

/* Variables and functions */
 float ITextFont_GetAllCaps (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetAnimation (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetBackColor (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetBold (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetEmboss (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetEngrave (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetForeColor (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetHidden (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetItalic (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetKerning (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetLanguageID (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetOutline (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetPosition (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetProtected (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetShadow (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetSize (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetSmallCaps (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetSpacing (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetStrikeThrough (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetSubscript (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetSuperscript (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetUnderline (int /*<<< orphan*/ *,float*) ; 
 float ITextFont_GetWeight (int /*<<< orphan*/ *,float*) ; 
 float S_OK ; 
 int /*<<< orphan*/  ok (int,char*,float) ; 
 float tomFalse ; 
 float tomUndefined ; 

__attribute__((used)) static void test_textfont_undefined(ITextFont *font)
{
  float valuef;
  LONG value;
  HRESULT hr;

  value = tomFalse;
  hr = ITextFont_GetAllCaps(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetAnimation(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetBackColor(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetBold(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetEmboss(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetForeColor(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetHidden(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetEngrave(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetItalic(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  valuef = 0.0;
  hr = ITextFont_GetKerning(font, &valuef);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(valuef == tomUndefined, "got %.2f\n", valuef);

  value = tomFalse;
  hr = ITextFont_GetLanguageID(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetOutline(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  valuef = 0.0;
  hr = ITextFont_GetPosition(font, &valuef);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(valuef == tomUndefined, "got %.2f\n", valuef);

  value = tomFalse;
  hr = ITextFont_GetProtected(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetShadow(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  valuef = 0.0;
  hr = ITextFont_GetSize(font, &valuef);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(valuef == tomUndefined, "got %.2f\n", valuef);

  value = tomFalse;
  hr = ITextFont_GetSmallCaps(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  valuef = 0.0;
  hr = ITextFont_GetSpacing(font, &valuef);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(valuef == tomUndefined, "got %.2f\n", valuef);

  value = tomFalse;
  hr = ITextFont_GetStrikeThrough(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetSubscript(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetSuperscript(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetUnderline(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);

  value = tomFalse;
  hr = ITextFont_GetWeight(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomUndefined, "got %d\n", value);
}