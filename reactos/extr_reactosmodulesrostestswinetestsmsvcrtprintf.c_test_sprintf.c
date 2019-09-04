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
typedef  char WCHAR ;
typedef  int ULONGLONG ;
typedef  int LONGLONG ;

/* Variables and functions */
 int IND ; 
 int INFINITY ; 
 int /*<<< orphan*/  LC_ALL ; 
 int NAN ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int sprintf (char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_sprintf( void )
{
    char buffer[100];
    const char *format;
    double pnumber=789456123;
    int x, r;
    WCHAR wide[] = { 'w','i','d','e',0};

    format = "%+#23.15e";
    r = sprintf(buffer,format,pnumber);
    ok(!strcmp(buffer,"+7.894561230000000e+008"),"+#23.15e failed: '%s'\n", buffer);
    ok( r==23, "return count wrong\n");

    format = "%-#23.15e";
    r = sprintf(buffer,format,pnumber);
    ok(!strcmp(buffer,"7.894561230000000e+008 "),"-#23.15e failed: '%s'\n", buffer);
    ok( r==23, "return count wrong\n");

    format = "%#23.15e";
    r = sprintf(buffer,format,pnumber);
    ok(!strcmp(buffer," 7.894561230000000e+008"),"#23.15e failed: '%s'\n", buffer);
    ok( r==23, "return count wrong\n");

    format = "%#1.1g";
    r = sprintf(buffer,format,pnumber);
    ok(!strcmp(buffer,"8.e+008"),"#1.1g failed: '%s'\n", buffer);
    ok( r==7, "return count wrong\n");

    format = "%I64d";
    r = sprintf(buffer,format,((ULONGLONG)0xffffffff)*0xffffffff);
    ok(!strcmp(buffer,"-8589934591"),"Problem with long long\n");
    ok( r==11, "return count wrong\n");

    format = "%+8I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"    +100") && r==8,"+8I64d failed: '%s'\n", buffer);

    format = "%+.8I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"+00000100") && r==9,"+.8I64d failed: '%s'\n", buffer);

    format = "%+10.8I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer," +00000100") && r==10,"+10.8I64d failed: '%s'\n", buffer);
    format = "%_1I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"_1I64d") && r==6,"_1I64d failed\n");

    format = "%-1.5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-00100") && r==6,"-1.5I64d failed: '%s'\n", buffer);

    format = "%5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"  100") && r==5,"5I64d failed: '%s'\n", buffer);

    format = "%5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer," -100") && r==5,"5I64d failed: '%s'\n", buffer);

    format = "%-5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"100  ") && r==5,"-5I64d failed: '%s'\n", buffer);

    format = "%-5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-100 ") && r==5,"-5I64d failed: '%s'\n", buffer);

    format = "%-.5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"00100") && r==5,"-.5I64d failed: '%s'\n", buffer);

    format = "%-.5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-00100") && r==6,"-.5I64d failed: '%s'\n", buffer);

    format = "%-8.5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"00100   ") && r==8,"-8.5I64d failed: '%s'\n", buffer);

    format = "%-8.5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-00100  ") && r==8,"-8.5I64d failed: '%s'\n", buffer);

    format = "%05I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"00100") && r==5,"05I64d failed: '%s'\n", buffer);

    format = "%05I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-0100") && r==5,"05I64d failed: '%s'\n", buffer);

    format = "% I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer," 100") && r==4,"' I64d' failed: '%s'\n", buffer);

    format = "% I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-100") && r==4,"' I64d' failed: '%s'\n", buffer);

    format = "% 5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"  100") && r==5,"' 5I64d' failed: '%s'\n", buffer);

    format = "% 5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer," -100") && r==5,"' 5I64d' failed: '%s'\n", buffer);

    format = "% .5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer," 00100") && r==6,"' .5I64d' failed: '%s'\n", buffer);

    format = "% .5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"-00100") && r==6,"' .5I64d' failed: '%s'\n", buffer);

    format = "% 8.5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"   00100") && r==8,"' 8.5I64d' failed: '%s'\n", buffer);

    format = "% 8.5I64d";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"  -00100") && r==8,"' 8.5I64d' failed: '%s'\n", buffer);

    format = "%.0I64d";
    r = sprintf(buffer,format,(LONGLONG)0);
    ok(r==0,".0I64d failed: '%s'\n", buffer);

    format = "%#+21.18I64x";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer," 0x00ffffffffffffff9c") && r==21,"#+21.18I64x failed: '%s'\n", buffer);

    format = "%#.25I64o";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"0001777777777777777777634") && r==25,"#.25I64o failed: '%s'\n", buffer);

    format = "%#+24.20I64o";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer," 01777777777777777777634") && r==24,"#+24.20I64o failed: '%s'\n", buffer);

    format = "%#+18.21I64X";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"0X00000FFFFFFFFFFFFFF9C") && r==23,"#+18.21I64X failed: '%s '\n", buffer);

    format = "%#+20.24I64o";
    r = sprintf(buffer,format,(LONGLONG)-100);
    ok(!strcmp(buffer,"001777777777777777777634") && r==24,"#+20.24I64o failed: '%s'\n", buffer);

    format = "%#+25.22I64u";
    r = sprintf(buffer,format,(LONGLONG)-1);
    ok(!strcmp(buffer,"   0018446744073709551615") && r==25,"#+25.22I64u conversion failed: '%s'\n", buffer);

    format = "%#+25.22I64u";
    r = sprintf(buffer,format,(LONGLONG)-1);
    ok(!strcmp(buffer,"   0018446744073709551615") && r==25,"#+25.22I64u failed: '%s'\n", buffer);

    format = "%#+30.25I64u";
    r = sprintf(buffer,format,(LONGLONG)-1);
    ok(!strcmp(buffer,"     0000018446744073709551615") && r==30,"#+30.25I64u failed: '%s'\n", buffer);

    format = "%+#25.22I64d";
    r = sprintf(buffer,format,(LONGLONG)-1);
    ok(!strcmp(buffer,"  -0000000000000000000001") && r==25,"+#25.22I64d failed: '%s'\n", buffer);

    format = "%#-8.5I64o";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"00144   ") && r==8,"-8.5I64o failed: '%s'\n", buffer);

    format = "%#-+ 08.5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"+00100  ") && r==8,"'#-+ 08.5I64d failed: '%s'\n", buffer);

    format = "%#-+ 08.5I64d";
    r = sprintf(buffer,format,(LONGLONG)100);
    ok(!strcmp(buffer,"+00100  ") && r==8,"#-+ 08.5I64d failed: '%s'\n", buffer);

    format = "%.80I64d";
    r = sprintf(buffer,format,(LONGLONG)1);
    ok(r==80,"%s format failed\n", format);

    format = "% .80I64d";
    r = sprintf(buffer,format,(LONGLONG)1);
    ok(r==81,"%s format failed\n", format);

    format = "% .80d";
    r = sprintf(buffer,format,1);
    ok(r==81,"%s format failed\n", format);

    format = "%lld";
    r = sprintf(buffer,format,((ULONGLONG)0xffffffff)*0xffffffff);
    ok( r == 1 || r == 11, "return count wrong %d\n", r);
    if (r == 11)  /* %ll works on Vista */
        ok(!strcmp(buffer, "-8589934591"), "Problem with \"ll\" interpretation '%s'\n", buffer);
    else
        ok(!strcmp(buffer, "1"), "Problem with \"ll\" interpretation '%s'\n", buffer);

    format = "%I";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer, "I"), "Problem with \"I\" interpretation\n");
    ok( r==1, "return count wrong\n");

    format = "%I0d";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"I0d"),"I0d failed\n");
    ok( r==3, "return count wrong\n");

    format = "%I32d";
    r = sprintf(buffer,format,1);
    if (r == 1)
    {
        ok(!strcmp(buffer,"1"),"I32d failed, got '%s'\n",buffer);
    }
    else
    {
        /* Older versions don't grok I32 format */
        ok(r == 4 && !strcmp(buffer,"I32d"),"I32d failed, got '%s',%d\n",buffer,r);
    }

    format = "%I64D";
    r = sprintf(buffer,format,(LONGLONG)-1);
    ok(!strcmp(buffer,"D"),"I64D failed: %s\n",buffer);
    ok( r==1, "return count wrong\n");

    format = "%zx";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer, "zx"), "Problem with \"z\" interpretation\n");
    ok( r==2, "return count wrong\n");

    format = "% d";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer, " 1"),"Problem with sign place-holder: '%s'\n",buffer);
    ok( r==2, "return count wrong\n");

    format = "%+ d";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer, "+1"),"Problem with sign flags: '%s'\n",buffer);
    ok( r==2, "return count wrong\n");

    format = "%S";
    r = sprintf(buffer,format,wide);
    ok(!strcmp(buffer,"wide"),"Problem with wide string format\n");
    ok( r==4, "return count wrong\n");

    format = "%04c";
    r = sprintf(buffer,format,'1');
    ok(!strcmp(buffer,"0001"),"Character not zero-prefixed \"%s\"\n",buffer);
    ok( r==4, "return count wrong\n");

    format = "%-04c";
    r = sprintf(buffer,format,'1');
    ok(!strcmp(buffer,"1   "),"Character zero-padded and/or not left-adjusted \"%s\"\n",buffer);
    ok( r==4, "return count wrong\n");

    format = "%#012x";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"0x0000000001"),"Hexadecimal zero-padded \"%s\"\n",buffer);
    ok( r==12, "return count wrong\n");

    r = sprintf(buffer,format,0);
    ok(!strcmp(buffer,"000000000000"),"Hexadecimal zero-padded \"%s\"\n",buffer);
    ok( r==12, "return count wrong\n");

    format = "%#04.8x";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"0x00000001"), "Hexadecimal zero-padded precision \"%s\"\n",buffer);
    ok( r==10, "return count wrong\n");

    r = sprintf(buffer,format,0);
    ok(!strcmp(buffer,"00000000"), "Hexadecimal zero-padded precision \"%s\"\n",buffer);
    ok( r==8, "return count wrong\n");

    format = "%#-08.2x";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"0x01    "), "Hexadecimal zero-padded not left-adjusted \"%s\"\n",buffer);
    ok( r==8, "return count wrong\n");

    r = sprintf(buffer,format,0);
    ok(!strcmp(buffer,"00      "), "Hexadecimal zero-padded not left-adjusted \"%s\"\n",buffer);
    ok( r==8, "return count wrong\n");

    format = "%#.0x";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"0x1"), "Hexadecimal zero-padded zero-precision \"%s\"\n",buffer);
    ok( r==3, "return count wrong\n");

    r = sprintf(buffer,format,0);
    ok(!strcmp(buffer,""), "Hexadecimal zero-padded zero-precision \"%s\"\n",buffer);
    ok( r==0, "return count wrong\n");

    format = "%#08o";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"00000001"), "Octal zero-padded \"%s\"\n",buffer);
    ok( r==8, "return count wrong\n");

    format = "%#o";
    r = sprintf(buffer,format,1);
    ok(!strcmp(buffer,"01"), "Octal zero-padded \"%s\"\n",buffer);
    ok( r==2, "return count wrong\n");

    r = sprintf(buffer,format,0);
    ok(!strcmp(buffer,"0"), "Octal zero-padded \"%s\"\n",buffer);
    ok( r==1, "return count wrong\n");

    if (sizeof(void *) == 8)
    {
        format = "%p";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"0000000000000039"),"Pointer formatted incorrectly \"%s\"\n",buffer);
        ok( r==16, "return count wrong\n");

        format = "%#020p";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"  0X0000000000000039"),"Pointer formatted incorrectly\n");
        ok( r==20, "return count wrong\n");

        format = "%Fp";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"0000000000000039"),"Pointer formatted incorrectly \"%s\"\n",buffer);
        ok( r==16, "return count wrong\n");

        format = "%Np";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"0000000000000039"),"Pointer formatted incorrectly \"%s\"\n",buffer);
        ok( r==16, "return count wrong\n");

        format = "%#-020p";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"0X0000000000000039  "),"Pointer formatted incorrectly\n");
        ok( r==20, "return count wrong\n");

        format = "%Ix %d";
        r = sprintf(buffer,format,(size_t)0x12345678123456,1);
        ok(!strcmp(buffer,"12345678123456 1"),"buffer = %s\n",buffer);
        ok( r==16, "return count wrong\n");
    }
    else
    {
        format = "%p";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"00000039"),"Pointer formatted incorrectly \"%s\"\n",buffer);
        ok( r==8, "return count wrong\n");

        format = "%#012p";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"  0X00000039"),"Pointer formatted incorrectly\n");
        ok( r==12, "return count wrong\n");

        format = "%Fp";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"00000039"),"Pointer formatted incorrectly \"%s\"\n",buffer);
        ok( r==8, "return count wrong\n");

        format = "%Np";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"00000039"),"Pointer formatted incorrectly \"%s\"\n",buffer);
        ok( r==8, "return count wrong\n");

        format = "%#-012p";
        r = sprintf(buffer,format,(void *)57);
        ok(!strcmp(buffer,"0X00000039  "),"Pointer formatted incorrectly\n");
        ok( r==12, "return count wrong\n");

        format = "%Ix %d";
        r = sprintf(buffer,format,0x123456,1);
        ok(!strcmp(buffer,"123456 1"),"buffer = %s\n",buffer);
        ok( r==8, "return count wrong\n");
    }

    format = "%04s";
    r = sprintf(buffer,format,"foo");
    ok(!strcmp(buffer,"0foo"),"String not zero-prefixed \"%s\"\n",buffer);
    ok( r==4, "return count wrong\n");

    format = "%.1s";
    r = sprintf(buffer,format,"foo");
    ok(!strcmp(buffer,"f"),"Precision ignored \"%s\"\n",buffer);
    ok( r==1, "return count wrong\n");

    format = "%.*s";
    r = sprintf(buffer,format,1,"foo");
    ok(!strcmp(buffer,"f"),"Precision ignored \"%s\"\n",buffer);
    ok( r==1, "return count wrong\n");

    format = "%*s";
    r = sprintf(buffer,format,-5,"foo");
    ok(!strcmp(buffer,"foo  "),"Negative field width ignored \"%s\"\n",buffer);
    ok( r==5, "return count wrong\n");

    format = "hello";
    r = sprintf(buffer, format);
    ok(!strcmp(buffer,"hello"), "failed\n");
    ok( r==5, "return count wrong\n");

    format = "%ws";
    r = sprintf(buffer, format, wide);
    ok(!strcmp(buffer,"wide"), "failed\n");
    ok( r==4, "return count wrong\n");

    format = "%-10ws";
    r = sprintf(buffer, format, wide );
    ok(!strcmp(buffer,"wide      "), "failed\n");
    ok( r==10, "return count wrong\n");

    format = "%10ws";
    r = sprintf(buffer, format, wide );
    ok(!strcmp(buffer,"      wide"), "failed\n");
    ok( r==10, "return count wrong\n");

    format = "%#+ -03whlls";
    r = sprintf(buffer, format, wide );
    ok(!strcmp(buffer,"wide"), "failed\n");
    ok( r==4, "return count wrong\n");

    format = "%w0s";
    r = sprintf(buffer, format, wide );
    ok(!strcmp(buffer,"0s"), "failed\n");
    ok( r==2, "return count wrong\n");

    format = "%w-s";
    r = sprintf(buffer, format, wide );
    ok(!strcmp(buffer,"-s"), "failed\n");
    ok( r==2, "return count wrong\n");

    format = "%ls";
    r = sprintf(buffer, format, wide );
    ok(!strcmp(buffer,"wide"), "failed\n");
    ok( r==4, "return count wrong\n");

    format = "%Ls";
    r = sprintf(buffer, format, "not wide" );
    ok(!strcmp(buffer,"not wide"), "failed\n");
    ok( r==8, "return count wrong\n");

    format = "%b";
    r = sprintf(buffer, format);
    ok(!strcmp(buffer,"b"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "%3c";
    r = sprintf(buffer, format,'a');
    ok(!strcmp(buffer,"  a"), "failed\n");
    ok( r==3, "return count wrong\n");

    format = "%3d";
    r = sprintf(buffer, format,1234);
    ok(!strcmp(buffer,"1234"), "failed\n");
    ok( r==4, "return count wrong\n");

    format = "%3h";
    r = sprintf(buffer, format);
    ok(!strcmp(buffer,""), "failed\n");
    ok( r==0, "return count wrong\n");

    format = "%j%k%m%q%r%t%v%y%z";
    r = sprintf(buffer, format);
    ok(!strcmp(buffer,"jkmqrtvyz"), "failed\n");
    ok( r==9, "return count wrong\n");

    format = "asdf%n";
    x = 0;
    r = sprintf(buffer, format, &x );
    if (r == -1)
    {
        /* %n format is disabled by default on vista */
        /* FIXME: should test with _set_printf_count_output */
        ok(x == 0, "should not write to x: %d\n", x);
    }
    else
    {
        ok(x == 4, "should write to x: %d\n", x);
        ok(!strcmp(buffer,"asdf"), "failed\n");
        ok( r==4, "return count wrong: %d\n", r);
    }

    format = "%-1d";
    r = sprintf(buffer, format,2);
    ok(!strcmp(buffer,"2"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "%2.4f";
    r = sprintf(buffer, format,8.6);
    ok(!strcmp(buffer,"8.6000"), "failed\n");
    ok( r==6, "return count wrong\n");

    format = "%0f";
    r = sprintf(buffer, format,0.6);
    ok(!strcmp(buffer,"0.600000"), "failed\n");
    ok( r==8, "return count wrong\n");

    format = "%.0f";
    r = sprintf(buffer, format,0.6);
    ok(!strcmp(buffer,"1"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "%2.4e";
    r = sprintf(buffer, format,8.6);
    ok(!strcmp(buffer,"8.6000e+000"), "failed\n");
    ok( r==11, "return count wrong\n");

    format = "% 2.4e";
    r = sprintf(buffer, format,8.6);
    ok(!strcmp(buffer," 8.6000e+000"), "failed: %s\n", buffer);
    ok( r==12, "return count wrong\n");

    format = "% 014.4e";
    r = sprintf(buffer, format,8.6);
    ok(!strcmp(buffer," 008.6000e+000"), "failed: %s\n", buffer);
    ok( r==14, "return count wrong\n");

    format = "% 2.4e";
    r = sprintf(buffer, format,-8.6);
    ok(!strcmp(buffer,"-8.6000e+000"), "failed: %s\n", buffer);
    ok( r==12, "return count wrong\n");

    format = "%+2.4e";
    r = sprintf(buffer, format,8.6);
    ok(!strcmp(buffer,"+8.6000e+000"), "failed: %s\n", buffer);
    ok( r==12, "return count wrong\n");

    format = "%2.4g";
    r = sprintf(buffer, format,8.6);
    ok(!strcmp(buffer,"8.6"), "failed\n");
    ok( r==3, "return count wrong\n");

    format = "%-i";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,"-1"), "failed\n");
    ok( r==2, "return count wrong\n");

    format = "%-i";
    r = sprintf(buffer, format,1);
    ok(!strcmp(buffer,"1"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "%+i";
    r = sprintf(buffer, format,1);
    ok(!strcmp(buffer,"+1"), "failed\n");
    ok( r==2, "return count wrong\n");

    format = "%o";
    r = sprintf(buffer, format,10);
    ok(!strcmp(buffer,"12"), "failed\n");
    ok( r==2, "return count wrong\n");

    format = "%p";
    r = sprintf(buffer, format,0);
    if (sizeof(void *) == 8)
    {
        ok(!strcmp(buffer,"0000000000000000"), "failed\n");
        ok( r==16, "return count wrong\n");
    }
    else
    {
        ok(!strcmp(buffer,"00000000"), "failed\n");
        ok( r==8, "return count wrong\n");
    }

    format = "%s";
    r = sprintf(buffer, format,0);
    ok(!strcmp(buffer,"(null)"), "failed\n");
    ok( r==6, "return count wrong\n");

    format = "%s";
    r = sprintf(buffer, format,"%%%%");
    ok(!strcmp(buffer,"%%%%"), "failed\n");
    ok( r==4, "return count wrong\n");

    format = "%u";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,"4294967295"), "failed\n");
    ok( r==10, "return count wrong\n");

    format = "%w";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,""), "failed\n");
    ok( r==0, "return count wrong\n");

    format = "%h";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,""), "failed\n");
    ok( r==0, "return count wrong\n");

    format = "%z";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,"z"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "%j";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,"j"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "%F";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,""), "failed\n");
    ok( r==0, "return count wrong\n");

    format = "%N";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,""), "failed\n");
    ok( r==0, "return count wrong\n");

    format = "%H";
    r = sprintf(buffer, format,-1);
    ok(!strcmp(buffer,"H"), "failed\n");
    ok( r==1, "return count wrong\n");

    format = "x%cx";
    r = sprintf(buffer, format, 0x100+'X');
    ok(!strcmp(buffer,"xXx"), "failed\n");
    ok( r==3, "return count wrong\n");

    format = "%%0";
    r = sprintf(buffer, format);
    ok(!strcmp(buffer,"%0"), "failed: \"%s\"\n", buffer);
    ok( r==2, "return count wrong\n");

    format = "%hx";
    r = sprintf(buffer, format, 0x12345);
    ok(!strcmp(buffer,"2345"), "failed \"%s\"\n", buffer);

    format = "%hhx";
    r = sprintf(buffer, format, 0x123);
    ok(!strcmp(buffer,"123"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, 0x12345);
    ok(!strcmp(buffer,"2345"), "failed \"%s\"\n", buffer);

    format = "%lf";
    r = sprintf(buffer, format, IND);
    ok(r==9, "r = %d\n", r);
    ok(!strcmp(buffer, "-1.#IND00"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, NAN);
    ok(r==8, "r = %d\n", r);
    ok(!strcmp(buffer, "1.#QNAN0"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, INFINITY);
    ok(r==8, "r = %d\n", r);
    ok(!strcmp(buffer, "1.#INF00"), "failed: \"%s\"\n", buffer);

    format = "%le";
    r = sprintf(buffer, format, IND);
    ok(r==14, "r = %d\n", r);
    ok(!strcmp(buffer, "-1.#IND00e+000"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, NAN);
    ok(r==13, "r = %d\n", r);
    ok(!strcmp(buffer, "1.#QNAN0e+000"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, INFINITY);
    ok(r==13, "r = %d\n", r);
    ok(!strcmp(buffer, "1.#INF00e+000"), "failed: \"%s\"\n", buffer);

    format = "%lg";
    r = sprintf(buffer, format, IND);
    ok(r==7, "r = %d\n", r);
    ok(!strcmp(buffer, "-1.#IND"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, NAN);
    ok(r==7, "r = %d\n", r);
    ok(!strcmp(buffer, "1.#QNAN"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, INFINITY);
    ok(r==6, "r = %d\n", r);
    ok(!strcmp(buffer, "1.#INF"), "failed: \"%s\"\n", buffer);

    format = "%010.2lf";
    r = sprintf(buffer, format, IND);
    ok(r==10, "r = %d\n", r);
    ok(!strcmp(buffer, "-000001.#J"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, NAN);
    ok(r==10, "r = %d\n", r);
    ok(!strcmp(buffer, "0000001.#R"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, INFINITY);
    ok(r==10, "r = %d\n", r);
    ok(!strcmp(buffer, "0000001.#J"), "failed: \"%s\"\n", buffer);

    format = "%c";
    r = sprintf(buffer, format, 'a');
    ok(r==1, "r = %d\n", r);
    ok(!strcmp(buffer, "a"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, 0xa082);
    ok(r==1, "r = %d\n", r);
    ok(!strcmp(buffer, "\x82"), "failed: \"%s\"\n", buffer);

    format = "%C";
    r = sprintf(buffer, format, 'a');
    ok(r==1, "r = %d\n", r);
    ok(!strcmp(buffer, "a"), "failed: \"%s\"\n", buffer);
    r = sprintf(buffer, format, 0x3042);
    ok(r==0, "r = %d\n", r);
    ok(!strcmp(buffer, ""), "failed: \"%s\"\n", buffer);

    if(!setlocale(LC_ALL, "Japanese_Japan.932")) {
        win_skip("Japanese_Japan.932 locale not available\n");
        return;
    }

    format = "%c";
    r = sprintf(buffer, format, 0xa082);
    ok(r==1, "r = %d\n", r);
    ok(!strcmp(buffer, "\x82"), "failed: \"%s\"\n", buffer);

    format = "%C";
    r = sprintf(buffer, format, 0x3042);
    ok(r==2, "r = %d\n", r);
    ok(!strcmp(buffer, "\x82\xa0"), "failed: \"%s\"\n", buffer);

    setlocale(LC_ALL, "C");
}