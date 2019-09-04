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
 int /*<<< orphan*/  printf (char*) ; 

void usage(void) {
    printf("\n");
    printf("Usage: ag [FILE-TYPE] [OPTIONS] PATTERN [PATH]\n\n");

    printf("  Recursively search for PATTERN in PATH.\n");
    printf("  Like grep or ack, but faster.\n\n");

    printf("Example:\n  ag -i foo /bar/\n\n");

    printf("\
Output Options:\n\
     --ackmate            Print results in AckMate-parseable format\n\
  -A --after [LINES]      Print lines after match (Default: 2)\n\
  -B --before [LINES]     Print lines before match (Default: 2)\n\
     --[no]break          Print newlines between matches in different files\n\
                          (Enabled by default)\n\
  -c --count              Only print the number of matches in each file.\n\
                          (This often differs from the number of matching lines)\n\
     --[no]color          Print color codes in results (Enabled by default)\n\
     --color-line-number  Color codes for line numbers (Default: 1;33)\n\
     --color-match        Color codes for result match numbers (Default: 30;43)\n\
     --color-path         Color codes for path names (Default: 1;32)\n\
");
#ifdef _WIN32
    printf("\
     --color-win-ansi     Use ansi colors on Windows even where we can use native\n\
                          (pager/pipe colors are ansi regardless) (Default: off)\n\
");
#endif
    printf("\
     --column             Print column numbers in results\n\
     --[no]filename       Print file names (Enabled unless searching a single file)\n\
  -H --[no]heading        Print file names before each file's matches\n\
                          (Enabled by default)\n\
  -C --context [LINES]    Print lines before and after matches (Default: 2)\n\
     --[no]group          Same as --[no]break --[no]heading\n\
  -g --filename-pattern PATTERN\n\
                          Print filenames matching PATTERN\n\
  -l --files-with-matches Only print filenames that contain matches\n\
                          (don't print the matching lines)\n\
  -L --files-without-matches\n\
                          Only print filenames that don't contain matches\n\
     --print-all-files    Print headings for all files searched, even those that\n\
                          don't contain matches\n\
     --[no]numbers        Print line numbers. Default is to omit line numbers\n\
                          when searching streams\n\
  -o --only-matching      Prints only the matching part of the lines\n\
     --print-long-lines   Print matches on very long lines (Default: >2k characters)\n\
     --passthrough        When searching a stream, print all lines even if they\n\
                          don't match\n\
     --silent             Suppress all log messages, including errors\n\
     --stats              Print stats (files scanned, time taken, etc.)\n\
     --stats-only         Print stats and nothing else.\n\
                          (Same as --count when searching a single file)\n\
     --vimgrep            Print results like vim's :vimgrep /pattern/g would\n\
                          (it reports every match on the line)\n\
  -0 --null --print0      Separate filenames with null (for 'xargs -0')\n\
\n\
Search Options:\n\
  -a --all-types          Search all files (doesn't include hidden files\n\
                          or patterns from ignore files)\n\
  -D --debug              Ridiculous debugging (probably not useful)\n\
     --depth NUM          Search up to NUM directories deep (Default: 25)\n\
  -f --follow             Follow symlinks\n\
  -F --fixed-strings      Alias for --literal for compatibility with grep\n\
  -G --file-search-regex  PATTERN Limit search to filenames matching PATTERN\n\
     --hidden             Search hidden files (obeys .*ignore files)\n\
  -i --ignore-case        Match case insensitively\n\
     --ignore PATTERN     Ignore files/directories matching PATTERN\n\
                          (literal file/directory names also allowed)\n\
     --ignore-dir NAME    Alias for --ignore for compatibility with ack.\n\
  -m --max-count NUM      Skip the rest of a file after NUM matches (Default: 10,000)\n\
     --one-device         Don't follow links to other devices.\n\
  -p --path-to-ignore STRING\n\
                          Use .ignore file at STRING\n\
  -Q --literal            Don't parse PATTERN as a regular expression\n\
  -s --case-sensitive     Match case sensitively\n\
  -S --smart-case         Match case insensitively unless PATTERN contains\n\
                          uppercase characters (Enabled by default)\n\
     --search-binary      Search binary files for matches\n\
  -t --all-text           Search all text files (doesn't include hidden files)\n\
  -u --unrestricted       Search all files (ignore .ignore, .gitignore, etc.;\n\
                          searches binary and hidden files as well)\n\
  -U --skip-vcs-ignores   Ignore VCS ignore files\n\
                          (.gitignore, .hgignore; still obey .ignore)\n\
  -v --invert-match\n\
  -w --word-regexp        Only match whole words\n\
  -W --width NUM          Truncate match lines after NUM characters\n\
  -z --search-zip         Search contents of compressed (e.g., gzip) files\n\
\n");
    printf("File Types:\n\
The search can be restricted to certain types of files. Example:\n\
  ag --html needle\n\
  - Searches for 'needle' in files with suffix .htm, .html, .shtml or .xhtml.\n\
\n\
For a list of supported file types run:\n\
  ag --list-file-types\n\n\
ag was originally created by Geoff Greer. More information (and the latest release)\n\
can be found at http://geoff.greer.fm/ag\n");
}