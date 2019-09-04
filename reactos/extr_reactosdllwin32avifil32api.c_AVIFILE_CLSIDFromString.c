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
typedef  scalar_t__ LPCSTR ;
typedef  int* LPCLSID ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CO_E_CLASSSTRING ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int const*,int*) ; 
 int lstrlenA (scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT AVIFILE_CLSIDFromString(LPCSTR idstr, LPCLSID id)
{
  BYTE const *s;
  BYTE *p;
  INT   i;
  BYTE table[256];

  if (!idstr) {
    memset(id, 0, sizeof(CLSID));
    return S_OK;
  }

  /* validate the CLSID string */
  if (lstrlenA(idstr) != 38)
    return CO_E_CLASSSTRING;

  s = (BYTE const*)idstr;
  if ((s[0]!='{') || (s[9]!='-') || (s[14]!='-') || (s[19]!='-') ||
      (s[24]!='-') || (s[37]!='}'))
    return CO_E_CLASSSTRING;

  for (i = 1; i < 37; i++) {
    if ((i == 9) || (i == 14) || (i == 19) || (i == 24))
      continue;
    if (!(((s[i] >= '0') && (s[i] <= '9'))  ||
        ((s[i] >= 'a') && (s[i] <= 'f'))  ||
        ((s[i] >= 'A') && (s[i] <= 'F')))
       )
      return CO_E_CLASSSTRING;
  }

  TRACE("%s -> %p\n", s, id);

  /* quick lookup table */
  memset(table, 0, 256);

  for (i = 0; i < 10; i++)
    table['0' + i] = i;

  for (i = 0; i < 6; i++) {
    table['A' + i] = i+10;
    table['a' + i] = i+10;
  }

  /* in form {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX} */
  p = (BYTE *) id;

  s++;	/* skip leading brace  */
  for (i = 0; i < 4; i++) {
    p[3 - i] = table[*s]<<4 | table[*(s+1)];
    s += 2;
  }
  p += 4;
  s++;	/* skip - */

  for (i = 0; i < 2; i++) {
    p[1-i] = table[*s]<<4 | table[*(s+1)];
    s += 2;
  }
  p += 2;
  s++;	/* skip - */

  for (i = 0; i < 2; i++) {
    p[1-i] = table[*s]<<4 | table[*(s+1)];
    s += 2;
  }
  p += 2;
  s++;	/* skip - */

  /* these are just sequential bytes */
  for (i = 0; i < 2; i++) {
    *p++ = table[*s]<<4 | table[*(s+1)];
    s += 2;
  }
  s++;	/* skip - */

  for (i = 0; i < 6; i++) {
    *p++ = table[*s]<<4 | table[*(s+1)];
    s += 2;
  }

  return S_OK;
}