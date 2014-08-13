#include <stdio.h>
#include <getopt.h>

#define VERSION_H                \
"#ifndef VERSION_H\n"            \
"#define VERSION_H\n"            \
"\n"                             \
"#define %s_MAJOR %d\n"          \
"#define %s_MINOR %d\n"          \
"#define %s_PATCH %d\n"          \
"#define %s_BUILD %d\n"          \
"#define %s_META \"%s\"\n"       \
"#define %s \"%d.%d.%d.%d%s\"\n" \
"\n"                             \
"#endif /* VERSION_H */\n"

#define USAGE                                            \
"Usage: %s [-hMmpbaP]\n"                                 \
"\n"                                                     \
"Options:\n"                                             \
"  -h, --help     Print this menu and exit.\n"           \
"  -M, --major    Major number.\n"                       \
"  -m, --minor    Minor number.\n"                       \
"  -p, --patch    Patch number.\n"                       \
"  -b, --build    Build number.\n"                       \
"  -a, --meta     Meta information.\n"                   \
"  -P, --prefix   The macro prefix [default: VERSION]\n" \
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
	};
	int major, minor, patch, build, c;
	char *meta, *prefix;

	major = minor = patch = build = 0;
	meta = "";
	prefix = "VERSION";

	while ((c = getopt_long(argc, argv, "hM:m:p:b:a:P:", long_options, 0)) != -1) {
		switch (c) {
		case 'h':
			printf(USAGE, argv[0]);
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
		}
	}

	printf(VERSION_H,
		prefix, major,
		prefix, minor,
		prefix, patch,
		prefix, build,
		prefix, meta,
		prefix, major, minor, patch, build, meta);

	return 0;
}
