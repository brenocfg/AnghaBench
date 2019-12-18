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
typedef  scalar_t__ syskind_t ;
typedef  int ULONG ;
typedef  scalar_t__ LPCSTR ;
typedef  int LCID ;

/* Variables and functions */
 int /*<<< orphan*/  LANGIDFROMLCID (int) ; 
#define  LANG_AFRIKAANS 220 
#define  LANG_ALBANIAN 219 
#define  LANG_ARABIC 218 
#define  LANG_ARMENIAN 217 
#define  LANG_ASSAMESE 216 
#define  LANG_AZERI 215 
#define  LANG_BASQUE 214 
#define  LANG_BELARUSIAN 213 
#define  LANG_BENGALI 212 
#define  LANG_BRETON 211 
#define  LANG_BULGARIAN 210 
#define  LANG_CATALAN 209 
#define  LANG_CHINESE 208 
#define  LANG_CORNISH 207 
#define  LANG_CZECH 206 
#define  LANG_DANISH 205 
#define  LANG_DIVEHI 204 
#define  LANG_DUTCH 203 
#define  LANG_ENGLISH 202 
#define  LANG_ESPERANTO 201 
#define  LANG_ESTONIAN 200 
#define  LANG_FAEROESE 199 
#define  LANG_FARSI 198 
#define  LANG_FINNISH 197 
#define  LANG_FRENCH 196 
#define  LANG_GAELIC 195 
#define  LANG_GALICIAN 194 
#define  LANG_GEORGIAN 193 
#define  LANG_GERMAN 192 
#define  LANG_GREEK 191 
#define  LANG_GUJARATI 190 
#define  LANG_HEBREW 189 
#define  LANG_HINDI 188 
#define  LANG_HUNGARIAN 187 
#define  LANG_ICELANDIC 186 
#define  LANG_INDONESIAN 185 
#define  LANG_IRISH 184 
#define  LANG_ITALIAN 183 
#define  LANG_JAPANESE 182 
#define  LANG_KANNADA 181 
#define  LANG_KASHMIRI 180 
#define  LANG_KAZAK 179 
#define  LANG_KONKANI 178 
#define  LANG_KOREAN 177 
#define  LANG_KYRGYZ 176 
#define  LANG_LATVIAN 175 
#define  LANG_LITHUANIAN 174 
#define  LANG_MACEDONIAN 173 
#define  LANG_MALAY 172 
#define  LANG_MALAYALAM 171 
#define  LANG_MALTESE 170 
#define  LANG_MANIPURI 169 
#define  LANG_MARATHI 168 
#define  LANG_MONGOLIAN 167 
#define  LANG_NEPALI 166 
#define  LANG_NEUTRAL 165 
#define  LANG_NORWEGIAN 164 
#define  LANG_ORIYA 163 
#define  LANG_POLISH 162 
#define  LANG_PORTUGUESE 161 
#define  LANG_PUNJABI 160 
#define  LANG_ROMANIAN 159 
#define  LANG_ROMANSH 158 
#define  LANG_RUSSIAN 157 
#define  LANG_SAMI 156 
#define  LANG_SANSKRIT 155 
#define  LANG_SERBIAN 154 
#define  LANG_SINDHI 153 
#define  LANG_SLOVAK 152 
#define  LANG_SLOVENIAN 151 
#define  LANG_SPANISH 150 
#define  LANG_SUTU 149 
#define  LANG_SWAHILI 148 
#define  LANG_SWEDISH 147 
#define  LANG_SYRIAC 146 
#define  LANG_TAJIK 145 
#define  LANG_TAMIL 144 
#define  LANG_TATAR 143 
#define  LANG_TELUGU 142 
#define  LANG_THAI 141 
#define  LANG_TSONGA 140 
#define  LANG_TSWANA 139 
#define  LANG_TURKISH 138 
#define  LANG_UKRAINIAN 137 
#define  LANG_UPPER_SORBIAN 136 
#define  LANG_URDU 135 
#define  LANG_UZBEK 134 
#define  LANG_VENDA 133 
#define  LANG_VIETNAMESE 132 
#define  LANG_WALON 131 
#define  LANG_WELSH 130 
#define  LANG_XHOSA 129 
#define  LANG_ZULU 128 
 unsigned char* Lookup_112 ; 
 unsigned char* Lookup_128 ; 
 unsigned char* Lookup_144 ; 
 unsigned char* Lookup_16 ; 
 unsigned char* Lookup_160 ; 
 unsigned char* Lookup_176 ; 
 unsigned char* Lookup_208 ; 
 unsigned char* Lookup_224 ; 
 unsigned char* Lookup_32 ; 
 unsigned char* Lookup_48 ; 
 unsigned char* Lookup_64 ; 
 unsigned char* Lookup_80 ; 
 int PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_NORWEGIAN_NYNORSK ; 
 scalar_t__ SYS_MAC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

unsigned int lhash_val_of_name_sys( syskind_t skind, LCID lcid, LPCSTR lpStr)
{
  ULONG nOffset, nMask = skind == SYS_MAC ? 1 : 0;
  ULONG nHiWord, nLoWord = 0x0deadbee;
  const unsigned char *str = (const unsigned char *)lpStr, *pnLookup = NULL;

  if (!str)
    return 0;

  switch (PRIMARYLANGID(LANGIDFROMLCID(lcid)))
  {
  default:
    fprintf(stderr, "Unknown lcid %x, treating as latin-based, please report\n", lcid);
    /* .. Fall Through .. */
  case LANG_AFRIKAANS:  case LANG_ALBANIAN:   case LANG_ARMENIAN:
  case LANG_ASSAMESE:   case LANG_AZERI:      case LANG_BASQUE:
  case LANG_BELARUSIAN: case LANG_BENGALI:    case LANG_BULGARIAN:
  case LANG_CATALAN:    case LANG_DANISH:     case LANG_DIVEHI:
  case LANG_DUTCH:      case LANG_ENGLISH:    case LANG_ESTONIAN:
  case LANG_FAEROESE:   case LANG_FINNISH:    case LANG_FRENCH:
  case LANG_GALICIAN:   case LANG_GEORGIAN:   case LANG_GERMAN:
  case LANG_GUJARATI:   case LANG_HINDI:      case LANG_INDONESIAN:
  case LANG_ITALIAN:    case LANG_KANNADA:    case LANG_KASHMIRI:
  case LANG_KAZAK:      case LANG_KONKANI:    case LANG_KYRGYZ:
  case LANG_LATVIAN:    case LANG_LITHUANIAN: case LANG_MACEDONIAN:
  case LANG_MALAY:      case LANG_MALAYALAM:  case LANG_MANIPURI:
  case LANG_MARATHI:    case LANG_MONGOLIAN:  case LANG_NEPALI:
  case LANG_ORIYA:      case LANG_PORTUGUESE: case LANG_PUNJABI:
  case LANG_ROMANIAN:   case LANG_SANSKRIT:   case LANG_SERBIAN:
  case LANG_SINDHI:     case LANG_SLOVENIAN:  case LANG_SWAHILI:
  case LANG_SWEDISH:    case LANG_SYRIAC:     case LANG_TAMIL:
  case LANG_TATAR:      case LANG_TELUGU:     case LANG_THAI:
  case LANG_UKRAINIAN:  case LANG_URDU:       case LANG_UZBEK:
  case LANG_VIETNAMESE: case LANG_MALTESE:    case LANG_IRISH:
  case LANG_SAMI:       case LANG_UPPER_SORBIAN: case LANG_TSWANA:
  case LANG_XHOSA:      case LANG_ZULU:       case LANG_WELSH:
  case LANG_BRETON:     case LANG_NEUTRAL:
/* some languages not in all windows versions or ReactOS */
#ifdef LANG_GAELIC
  case LANG_GAELIC:
#endif
#ifdef LANG_TAJIK
  case LANG_TAJIK:
#endif
#ifdef LANG_ROMANSH
  case LANG_ROMANSH:
#endif
#ifdef LANG_SUTU
  case LANG_SUTU:
#endif
#ifdef LANG_TSONGA
  case LANG_TSONGA:
#endif
#ifdef LANG_VENDA
  case LANG_VENDA:
#endif
#ifdef LANG_ESPERANTO
  case LANG_ESPERANTO:
#endif
#ifdef LANG_WALON
  case LANG_WALON:
#endif
#ifdef LANG_CORNISH
  case LANG_CORNISH:
#endif
    nOffset = 16;
    pnLookup = Lookup_16;
    break;
  case LANG_CZECH:  case LANG_HUNGARIAN:  case LANG_POLISH:
  case LANG_SLOVAK: case LANG_SPANISH:
    nOffset = 32;
    pnLookup = Lookup_32;
    break;
  case LANG_HEBREW:
    nOffset = 48;
    pnLookup = Lookup_48;
    break;
  case LANG_JAPANESE:
    nOffset = 64;
    pnLookup = Lookup_64;
    break;
  case LANG_KOREAN:
    nOffset = 80;
    pnLookup = Lookup_80;
    break;
  case LANG_CHINESE:
    nOffset = 112;
    pnLookup = Lookup_112;
    break;
  case LANG_GREEK:
    nOffset = 128;
    pnLookup = Lookup_128;
    break;
  case LANG_ICELANDIC:
    nOffset = 144;
    pnLookup = Lookup_144;
    break;
  case LANG_TURKISH:
    nOffset = 160;
    pnLookup = Lookup_160;
    break;
  case LANG_NORWEGIAN:
    if (SUBLANGID(LANGIDFROMLCID(lcid)) == SUBLANG_NORWEGIAN_NYNORSK)
    {
      nOffset = 176;
      pnLookup = Lookup_176;
    }
    else
    {
      nOffset = 16;
      pnLookup = Lookup_16;
    }
    break;
  case LANG_ARABIC:
  case LANG_FARSI:
    nOffset = 208;
    pnLookup = Lookup_208;
    break;
  case LANG_RUSSIAN:
    nOffset = 224;
    pnLookup = Lookup_224;
    break;
  }

  nHiWord = (nOffset | nMask) << 16;

  while (*str)
  {
    nLoWord = 37 * nLoWord + pnLookup[*str > 0x7f && nMask ? *str + 0x80 : *str];
    str++;
  }
  /* Constrain to a prime modulo and sizeof(WORD) */
  nLoWord = (nLoWord % 65599) & 0xffff;

  return nHiWord | nLoWord;
}