'''
USAGE:
  generate.py [-o <dir>] <config>

OPTIONS:
  -v, --version                            Print the version
  -h, --help                               Print this help menu
  -o, --output <dir>                       Write output files to this directory
'''
import os
import sys
import json
from textwrap import dedent
from datetime import datetime
from docopt import docopt

class CppGenerator:
    def __init__(self, version):
        self.decorated = version

    def header(self):
        now = datetime.now()
        return dedent('''\
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

            const char * hello_world();

            #endif /* {prefix}VERSION_H */
            '''.format(
                prefix = self.decorated['prefix'] if 'prefix' in self.decorated else '',
                major = self.decorated['major'] if 'major' in self.decorated else 0,
                minor = self.decorated['minor'] if 'minor' in self.decorated else 0,
                patch = self.decorated['patch'] if 'patch' in self.decorated else 0,
                build = self.decorated['build'] if 'build' in self.decorated else 0,
                meta = self.decorated['meta'] if 'meta' in self.decorated else '',
                date = now.strftime('%d/%m/%Y'),
                time = now.strftime('%H:%M:%S')
            ))

    def source(self):
        return dedent('''\
            #include "version.h"

            const char * hello_world()
            {
                return "Hello World";
            } 
            ''')

def main():
    argv = docopt(__doc__, version="1.0")

    if argv['<config>'] is not None:
        with open(argv['<config>']) as config_file:
            config = json.load(config_file)
            gen = CppGenerator(config)
            if argv['--output']:
                header_file = os.path.join(argv['--output'], 'version.h')
                source_file = os.path.join(argv['--output'], 'version.c')
                with open(header_file, 'w') as out:
                    out.write(gen.header())
                with open(source_file, 'w') as out:
                    out.write(gen.source())
            else:
                print(gen.header())
                print(gen.source())

if __name__ == "__main__":
    main()
