'''
USAGE:
  generate.py [-o <file>] <config>

OPTIONS:
  -v, --version                            Print the version
  -h, --help                               Print this help menu
  -o, --output <file>                      Write output to this file
'''
import sys
import json
from textwrap import dedent
from datetime import datetime
from docopt import docopt

def write_version_header(out, config):
    now = datetime.now()
    out.write(dedent('''\
    #ifndef {prefix}VERSION_H
    #define {prefix}VERSION_H

    #define {prefix}VERSION_MAJOR {major}
    #define {prefix}VERSION_MINOR {minor}
    #define {prefix}VERSION_PATCH {patch}
    #define {prefix}VERSION_BUILD {build}
    #define {prefix}VERSION_META "{meta}"
    #define {prefix}VERSION "{major}.{minor}.{patch}.{build}{meta}"
    #define {prefix}COMPILE_DATE "{date}"
    #define {prefix}COMPILE_TIME "{time}"

    #endif /* {prefix}VERSION_H */
    ''').format(
        prefix = config['prefix'] if 'prefix' in config else '',
        major = config['major'] if 'major' in config else 0,
        minor = config['minor'] if 'minor' in config else 0,
        patch = config['patch'] if 'patch' in config else 0,
        build = config['build'] if 'build' in config else 0,
        meta = config['meta'] if 'meta' in config else '',
        date = now.strftime('%d/%m/%Y'),
        time = now.strftime('%H:%M:%S')
    ))

def main():
    argv = docopt(__doc__, version="1.0")

    if argv['<config>'] is not None:
        with open(argv['<config>']) as config_file:
            config = json.load(config_file)
            if argv['--output']:
                with open(argv['--output'], 'w') as out:
                    write_version_header(out, config)
            else:
                write_version_header(sys.stdout, config)

if __name__ == "__main__":
    main()
