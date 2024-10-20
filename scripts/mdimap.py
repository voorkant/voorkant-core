#!/usr/bin/env python3
import re
import sys

infile = open(sys.argv[1])
outfile = open(sys.argv[2], 'w')  # FIXME tempfile+rename

# skip until $mdi-icons
for line in infile:
    if line.startswith("$mdi-icons"):
        break

icons = dict()

# now handle all icons
for line in infile:
    if not line.startswith(" "):
        break
    #   "ab-testing": F01C9,\n
    line = line.strip()

    # "ab-testing": F01C9,
    if line.endswith(","):
        line = line[:-1]

    #  "ab-testing": F01C9
    k, v = line.split(":")

    # k = "ab-testing" (INCLUDING quotes)
    # v =  F01C9 (no quotes, leading space)
    v = v.strip()

    # k = "ab-testing" (INCLUDING quotes)
    # v =  F01C9 (no quotes, no leading space)
    v = repr(chr(int(v, 16)).encode('utf-8'))[2:-1]

    # k = "ab-testing" (INCLUDING quotes)
    # v = \\xf3\\xb0\\x87\\x89 (no quotes)

    icons[k] = v

outfile.write(f"""#include "uicomponents/mdimap.hpp"

static std::map<std::string, std::string> map_name2id = {{
""")


for k, v in icons.items():
    outfile.write(f'  {{{k}, "{v}"}},\n')

outfile.write("""
};

// making _name a ref is tempting but currently some code tries to pass simple static "foo" (char array) in
std::string voorkant::mdi::name2id(std::string _name) {
    return map_name2id.at(_name);
}

\n""")
