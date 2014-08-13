#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#define VERSION_H                        \
"#ifndef %s_VERSION_H\n"                 \
"#define %s_VERSION_H\n"                 \
"\n"                                     \
"#define %s_VERSION_MAJOR %d\n"          \
"#define %s_VERSION_MINOR %d\n"          \
"#define %s_VERSION_PATCH %d\n"          \
"#define %s_VERSION_BUILD %d\n"          \
"#define %s_VERSION_META \"%s\"\n"       \
"#define %s_VERSION \"%d.%d.%d.%d%s\"\n" \
"#define %s_COMPILE_DATE \"%s\"\n"       \
"#define %s_COMPILE_TIME \"%s\"\n"       \
"\n"                                     \
"#endif /* %s_VERSION_H */\n"

#define USAGE                                           \
"Usage: %s [-hMmpbaP]\n"                                \
"\n"                                                    \
"Options:\n"                                            \
"  -h, --help     Print this menu and exit.\n"          \
"  -M, --major    Major number.\n"                      \
"  -m, --minor    Minor number.\n"                      \
"  -p, --patch    Patch number.\n"                      \
"  -b, --build    Build number.\n"                      \
"  -a, --meta     Meta information.\n"                  \
"  -P, --prefix   The macro prefix [default: EXAMPLE]\n"\
"  -D, --date     Date format [default: \"%s\"]\n"      \
"  -T, --time     Time format [default: \"%s\"]\n"      \
"\n"

int main(int argc, char **argv)
{
	struct option long_options[] = {
		{"help",   required_argument, NULL, 'h'},
		{"major",  required_argument, NULL, 'M'},
		{"minor",  required_argument, NULL, 'm'},
		{"patch",  required_argument, NULL, 'p'},
		{"build",  required_argument, NULL, 'b'},
		{"meta",   required_argument, NULL, 'a'},
		{"prefix", required_argument, NULL, 'P'},
		{"date",   required_argument, NULL, 'D'},
		{"time",   required_argument, NULL, 'T'},
	};
	int major, minor, patch, build, c;
	char *meta, *prefix, *datefmt, *timefmt;
	time_t timer;
	struct tm *tm_info;
	char datestr[32];
	char timestr[32];

	memset(datestr, 0, sizeof(datestr));
	memset(timestr, 0, sizeof(timestr));

	major = minor = patch = build = 0;
	meta = "";
	prefix = "EXAMPLE";
	datefmt = "%Y-%m-%d";
	timefmt = "%H:%M:%S";

	while ((c = getopt_long(argc, argv, "hM:m:p:b:a:P:D:T:", long_options, 0)) != -1) {
		switch (c) {
		case 'h':
			printf(USAGE, argv[0], datefmt, timefmt);
			return 0;
		case 'M':
			major = atoi(optarg);
			break;
		case 'm':
			minor = atoi(optarg);
			break;
		case 'p':
			patch = atoi(optarg);
			break;
		case 'b':
			build = atoi(optarg);
			break;
		case 'a':
			meta = optarg;
			break;
		case 'P':
			prefix = optarg;
			break;
		case 'D':
			datefmt = optarg;
			break;
		case 'T':
			timefmt = optarg;
			break;
		}
	}

	time(&timer);
	tm_info = localtime(&timer);

	strftime(datestr, sizeof(datestr), datefmt, tm_info);
	strftime(timestr, sizeof(timestr), timefmt, tm_info);

	printf(VERSION_H,
		prefix,
		prefix,
		prefix, major,
		prefix, minor,
		prefix, patch,
		prefix, build,
		prefix, meta,
		prefix, major, minor, patch, build, meta,
		prefix, datestr,
		prefix, timestr,
		prefix);

	return 0;
}
