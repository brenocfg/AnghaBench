#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_font_t ;
typedef  int /*<<< orphan*/  hb_bool_t ;
struct TYPE_4__ {int nfont; int /*<<< orphan*/ * fonts; } ;
typedef  int /*<<< orphan*/  FcPattern ;
typedef  int /*<<< orphan*/  FcObjectSet ;
typedef  TYPE_1__ FcFontSet ;
typedef  char FcChar8 ;

/* Variables and functions */
 char* FC_CHARSET ; 
 int /*<<< orphan*/  FC_FAMILY ; 
 int /*<<< orphan*/  FC_FILE ; 
 int FC_MAJOR ; 
 int FC_MINOR ; 
 int FC_REVISION ; 
 int /*<<< orphan*/  FC_STYLE ; 
 int /*<<< orphan*/  FcFini () ; 
 TYPE_1__* FcFontList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcFontSetDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/ * FcNameParse (char*) ; 
 int /*<<< orphan*/  FcObjectSetAdd (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * FcObjectSetBuild (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * FcObjectSetCreate () ; 
 int /*<<< orphan*/  FcObjectSetDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FcPatternCreate () ; 
 int /*<<< orphan*/  FcPatternDel (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FcPatternDestroy (int /*<<< orphan*/ *) ; 
 char* FcPatternFormat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  FcPatternPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FcStrFree (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_fc_can_render (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * hb_fc_font_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_font_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longopts ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*,int) ; 

int
main (int argc, char **argv)
{
    int			verbose = 0;
    int			quiet = 0;
    const FcChar8	*format = NULL;
    int			nfont = 0;
    int			i;
    FcObjectSet		*os = 0;
    FcFontSet		*fs;
    FcPattern		*pat;
    const char		*text;
#if HAVE_GETOPT_LONG || HAVE_GETOPT
    int			c;

#if HAVE_GETOPT_LONG
    while ((c = getopt_long (argc, argv, "vf:qVh", longopts, NULL)) != -1)
#else
    while ((c = getopt (argc, argv, "vf:qVh")) != -1)
#endif
    {
	switch (c) {
	case 'v':
	    verbose = 1;
	    break;
	case 'f':
	    format = (FcChar8 *) strdup (optarg);
	    break;
	case 'q':
	    quiet = 1;
	    break;
	case 'V':
	    fprintf (stderr, "fontconfig version %d.%d.%d\n",
		     FC_MAJOR, FC_MINOR, FC_REVISION);
	    exit (0);
	case 'h':
	    usage (argv[0], 0);
	default:
	    usage (argv[0], 1);
	}
    }
    i = optind;
#else
    i = 1;
#endif

    if (!argv[i])
	usage (argv[0], 1);

    text = argv[i];
    i++;

    if (argv[i])
    {
	pat = FcNameParse ((FcChar8 *) argv[i]);
	if (!pat)
	{
	    fputs ("Unable to parse the pattern\n", stderr);
	    return 1;
	}
	while (argv[++i])
	{
	    if (!os)
		os = FcObjectSetCreate ();
	    FcObjectSetAdd (os, argv[i]);
	}
    }
    else
	pat = FcPatternCreate ();
    if (quiet && !os)
	os = FcObjectSetCreate ();
    if (!verbose && !format && !os)
	os = FcObjectSetBuild (FC_FAMILY, FC_STYLE, FC_FILE, (char *) 0);
    FcObjectSetAdd (os, FC_CHARSET);
    if (!format)
        format = (const FcChar8 *) "%{=fclist}\n";
    fs = FcFontList (0, pat, os);
    if (os)
	FcObjectSetDestroy (os);
    if (pat)
	FcPatternDestroy (pat);

    if (!quiet && fs)
    {
	int	j;

	for (j = 0; j < fs->nfont; j++)
	{
	    hb_font_t *font = hb_fc_font_create (fs->fonts[j]);
	    hb_bool_t can_render = hb_fc_can_render (font, text);
	    hb_font_destroy (font);

	    if (!can_render)
		continue;

	    FcPatternDel (fs->fonts[j], FC_CHARSET);

	    if (verbose)
	    {
		FcPatternPrint (fs->fonts[j]);
	    }
	    else
	    {
	        FcChar8 *s;

		s = FcPatternFormat (fs->fonts[j], format);
		if (s)
		{
		    printf ("%s", s);
		    FcStrFree (s);
		}
	    }
	}
    }

    if (fs) {
	nfont = fs->nfont;
	FcFontSetDestroy (fs);
    }

    FcFini ();

    return quiet ? (nfont == 0 ? 1 : 0) : 0;
}