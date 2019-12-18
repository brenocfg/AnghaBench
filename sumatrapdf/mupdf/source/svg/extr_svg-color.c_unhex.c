__attribute__((used)) static int unhex(int chr)
{
	const char *hextable = "0123456789abcdef";
	return strchr(hextable, (chr|32)) - hextable;
}