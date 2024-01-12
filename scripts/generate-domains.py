#!/usr/bin/env python3
import json
import sys


def getSourceData():
    # right now this reads docs/domain.json, it could also parse
    # homeassistant/components/*/services.yaml from the HA source tree
    source = json.load(open("docs/domains.json", "r"))

    domains = {}

    for domain, content in source["result"].items():
        domains[domain] = content

    return domains


def generateHeader(domain, methods):
    impls = []
    for method, desc in methods.items():
        impl = []
        args = desc["fields"].keys()

        # should wrap description to X columns
        impl.append(f"""    // {desc.pop('name')} -- {desc.pop('description')}
    void {method}({', '.join(args)}) {{}}""")
        impls.append('\n\n'.join(impl))

    print(f"""// START HEADER FOR {domain}

namespace HAEntity {{
  class {domain.title()} {{
{(chr(10)+chr(10)).join(impls)}
  }}
}}""")


def main():
    data = getSourceData()
    generateHeader("light", data["light"])


if __name__ == '__main__':
    sys.exit(main())
