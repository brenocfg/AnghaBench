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

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int LC_ALL ; 
 int LC_MONETARY ; 
 int LC_NUMERIC ; 
 int /*<<< orphan*/  LOCALE_IDEFAULTANSICODEPAGE ; 
 int /*<<< orphan*/  LOCALE_IDEFAULTCODEPAGE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* setlocale (int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_setlocale(void)
{
    static const char lc_all[] = "LC_COLLATE=C;LC_CTYPE=C;"
        "LC_MONETARY=Greek_Greece.1253;LC_NUMERIC=Polish_Poland.1250;LC_TIME=C";

    char *ret, buf[100];

    ret = setlocale(20, "C");
    ok(ret == NULL, "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "C");
    ok(!strcmp(ret, "C"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, NULL);
    ok(!strcmp(ret, "C"), "ret = %s\n", ret);

    if(!setlocale(LC_NUMERIC, "Polish")
            || !setlocale(LC_NUMERIC, "Greek")
            || !setlocale(LC_NUMERIC, "German")
            || !setlocale(LC_NUMERIC, "English")) {
        win_skip("System with limited locales\n");
        return;
    }

    ret = setlocale(LC_NUMERIC, "Polish");
    ok(!strcmp(ret, "Polish_Poland.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_MONETARY, "Greek");
    ok(!strcmp(ret, "Greek_Greece.1253"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, NULL);
    ok(!strcmp(ret, lc_all), "ret = %s\n", ret);

    strcpy(buf, ret);
    ret = setlocale(LC_ALL, buf);
    ok(!strcmp(ret, lc_all), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "German");
    ok(!strcmp(ret, "German_Germany.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "american");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "american english");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "american-english");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "australian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_Australia.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "belgian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Dutch_Belgium.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "canadian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_Canada.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "chinese");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Chinese (Simplified)_People's Republic of China.936")
        || !strcmp(ret, "Chinese (Simplified)_China.936")
        || broken(!strcmp(ret, "Chinese_Taiwan.950")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "chinese-simplified");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Chinese (Simplified)_People's Republic of China.936")
        || !strcmp(ret, "Chinese (Simplified)_China.936")
        || broken(!strcmp(ret, "Chinese_People's Republic of China.936"))
        || broken(!strcmp(ret, "Chinese_Taiwan.950")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "chinese-traditional");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Chinese (Traditional)_Taiwan.950")
        || broken(!strcmp(ret, "Chinese_Taiwan.950")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "chs");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Chinese (Simplified)_People's Republic of China.936")
        || !strcmp(ret, "Chinese (Simplified)_China.936")
        || broken(!strcmp(ret, "Chinese_People's Republic of China.936")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "cht");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Chinese (Traditional)_Taiwan.950")
        || broken(!strcmp(ret, "Chinese_Taiwan.950")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "Chinese_China.936");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
    {
        trace("Chinese_China.936=%s\n", ret);
        ok(!strcmp(ret, "Chinese (Simplified)_People's Republic of China.936") /* Vista - Win7 */
        || !strcmp(ret, "Chinese (Simplified)_China.936") /* Win8 - Win10 */
        || broken(!strcmp(ret, "Chinese_People's Republic of China.936")), "ret = %s\n", ret);
    }

    ret = setlocale(LC_ALL, "csy");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Czech_Czech Republic.1250")
        || !strcmp(ret, "Czech_Czechia.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "czech");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Czech_Czech Republic.1250")
        || !strcmp(ret, "Czech_Czechia.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "dan");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Danish_Denmark.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "danish");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Danish_Denmark.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "dea");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Austria.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "des");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Switzerland.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "deu");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Germany.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "dutch");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Dutch_Netherlands.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "dutch-belgian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Dutch_Belgium.1252")
        || broken(!strcmp(ret, "Dutch_Netherlands.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "ena");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_Australia.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "ell");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Greek_Greece.1253"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "enc");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_Canada.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "eng");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United Kingdom.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "enu");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "enz");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_New Zealand.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-american");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-aus");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_Australia.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-can");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_Canada.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-nz");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_New Zealand.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-uk");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United Kingdom.1252")
        || broken(!strcmp(ret, "English_United States.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-us");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "english-usa");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "esm");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Spanish_Mexico.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "esn");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Spanish_Spain.1252")
        || broken(!strcmp(ret, "Spanish - Modern Sort_Spain.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "esp");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Spanish_Spain.1252")
        || broken(!strcmp(ret, "Spanish - Traditional Sort_Spain.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "fin");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Finnish_Finland.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "finnish");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Finnish_Finland.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "fra");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_France.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "frb");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_Belgium.1252")
        || broken(!strcmp(ret, "French_France.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "frc");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_Canada.1252")
        || broken(!strcmp(ret, "French_France.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "french");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_France.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "french-belgian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_Belgium.1252")
        || broken(!strcmp(ret, "French_France.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "french-canadian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_Canada.1252")
        || broken(!strcmp(ret, "French_France.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "french-swiss");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_Switzerland.1252")
        || broken(!strcmp(ret, "French_France.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "frs");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "French_Switzerland.1252")
        || broken(!strcmp(ret, "French_France.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "german");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Germany.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "german-austrian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Austria.1252")
        || broken(!strcmp(ret, "German_Germany.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "german-swiss");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Switzerland.1252")
        || broken(!strcmp(ret, "German_Germany.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "greek");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Greek_Greece.1253"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "hun");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Hungarian_Hungary.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "hungarian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Hungarian_Hungary.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "icelandic");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Icelandic_Iceland.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "isl");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Icelandic_Iceland.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "ita");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Italian_Italy.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "italian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Italian_Italy.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "italian-swiss");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Italian_Switzerland.1252")
        || broken(!strcmp(ret, "Italian_Italy.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "its");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Italian_Switzerland.1252")
        || broken(!strcmp(ret, "Italian_Italy.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "japanese");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Japanese_Japan.932"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "jpn");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Japanese_Japan.932"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "korean");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Korean_Korea.949"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "korean");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Korean_Korea.949"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "nlb");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Dutch_Belgium.1252")
        || broken(!strcmp(ret, "Dutch_Netherlands.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "nld");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Dutch_Netherlands.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "non");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp( ret, "Norwegian-Nynorsk_Norway.1252") /* XP - Win10 */
        || !strcmp(ret, "Norwegian (Nynorsk)_Norway.1252")
        || broken(!strcmp(ret, "Norwegian (Bokm\xe5l)_Norway.1252"))
        || broken(!strcmp(ret, "Norwegian_Norway.1252")), /* WinME */
           "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "nor");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Norwegian (Bokm\xe5l)_Norway.1252") /* XP - Win8 */
        || !strcmp(ret, "Norwegian Bokm\xe5l_Norway.1252") /* Win10 */
        || !strcmp(ret, "Norwegian (Bokmal)_Norway.1252")
        || broken(!strcmp(ret, "Norwegian_Norway.1252")), /* WinME */
           "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "norwegian-bokmal");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Norwegian (Bokm\xe5l)_Norway.1252") /* XP - Win8 */
        || !strcmp(ret, "Norwegian Bokm\xe5l_Norway.1252") /* Win10 */
        || !strcmp(ret, "Norwegian (Bokmal)_Norway.1252")
        || broken(!strcmp(ret, "Norwegian_Norway.1252")), /* WinME */
           "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "norwegian-nynorsk");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Norwegian-Nynorsk_Norway.1252") /* Vista - Win10 */
        || !strcmp(ret, "Norwegian (Nynorsk)_Norway.1252")
        || broken(!strcmp(ret, "Norwegian_Norway.1252")) /* WinME */
        || broken(!strcmp(ret, "Norwegian (Bokmal)_Norway.1252"))
        || broken(!strcmp(ret, "Norwegian (Bokm\xe5l)_Norway.1252")) /* XP & 2003 */,
           "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "plk");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Polish_Poland.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "polish");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Polish_Poland.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "portuguese");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Portuguese_Brazil.1252")
        || broken(!strcmp(ret, "Portuguese_Portugal.1252")) /* NT4 */, "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "portuguese-brazil");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Portuguese_Brazil.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "ptb");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Portuguese_Brazil.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "ptg");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Portuguese_Portugal.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "rus");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Russian_Russia.1251"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "russian");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Russian_Russia.1251"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "sky");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Slovak_Slovakia.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "slovak");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Slovak_Slovakia.1250"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "spanish");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Spanish_Spain.1252")
        || broken(!strcmp(ret, "Spanish - Traditional Sort_Spain.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "spanish-mexican");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Spanish_Mexico.1252")
        || broken(!strcmp(ret, "Spanish_Spain.1252")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "spanish-modern");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Spanish - Modern Sort_Spain.1252")
           || !strcmp(ret, "Spanish_Spain.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "sve");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Swedish_Sweden.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "swedish");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Swedish_Sweden.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "swiss");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "German_Switzerland.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "trk");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Turkish_Turkey.1254"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "turkish");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "Turkish_Turkey.1254"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "uk");
    ok(ret != NULL, "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United Kingdom.1252")
        || broken(!strcmp(ret, "Ukrainian_Ukraine.1251")), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "us");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "usa");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret)
        ok(!strcmp(ret, "English_United States.1252"), "ret = %s\n", ret);

    ret = setlocale(LC_ALL, "English_United States.ACP");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret) {
        strcpy(buf, "English_United States.");
        GetLocaleInfoA(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT),
                LOCALE_IDEFAULTANSICODEPAGE, buf+strlen(buf), 80);
        ok(!strcmp(ret, buf), "ret = %s, expected %s\n", ret, buf);
    }

    ret = setlocale(LC_ALL, "English_United States.OCP");
    ok(ret != NULL || broken (ret == NULL), "ret == NULL\n");
    if(ret) {
        strcpy(buf, "English_United States.");
        GetLocaleInfoA(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT),
                LOCALE_IDEFAULTCODEPAGE, buf+strlen(buf), 80);
        ok(!strcmp(ret, buf), "ret = %s, expected %s\n", ret, buf);
    }

    ret = setlocale(LC_ALL, "English_United States.UTF8");
    ok(ret == NULL, "ret != NULL\n");

    ret = setlocale(LC_ALL, "en-US");
    ok(ret == NULL || broken (ret != NULL), "ret != NULL\n"); /* XP & 2003 */
}