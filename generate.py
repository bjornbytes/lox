import urllib.request
import xml.etree.ElementTree as etree
import re

with urllib.request.urlopen('https://raw.githubusercontent.com/KhronosGroup/OpenXR-SDK-Source/master/specification/registry/xr.xml') as response:
    tree = etree.parse(response)

    X = ''
    filename = 'lox.h'

    for command in tree.findall('commands/command'):
        if not command.get('alias'):
            name = command.findtext('proto/name')
            X += '  X({})\\\n'.format(name)

    with open(filename, 'r') as f:
        contents = f.read()

    contents = re.sub('(  X\(.+\)\\n)+', X[:-2] + '\n', contents)

    with open(filename, 'w') as f:
        f.write(contents)
