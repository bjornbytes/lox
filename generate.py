import urllib.request
import xml.etree.ElementTree as etree
import re

#with urllib.request.urlopen('https://raw.githubusercontent.com/KhronosGroup/OpenXR-SDK-Source/master/specification/registry/xr.xml') as response:
#with open('/home/bjorn/Documents/dev/openxr-sdk-source/specification/registry/xr.xml', 'r') as spec:
tree = etree.parse('/home/bjorn/Documents/dev/openxr-sdk-source/specification/registry/xr.xml')

groups = {}
exclude = [
    'xrCreateInstance',
    'xrDestroyInstance',
    'xrGetInstanceProcAddr',
    'xrEnumerateApiLayerProperties',
    'xrEnumerateInstanceExtensionProperties'
]

for command in tree.findall('commands/command'):
    if command.get('alias'):
        continue

    name = command.findtext('proto/name')

    if name in exclude:
        continue

    extension = tree.find('.//extension[@protect]/require/command[@name="{}"]/../..'.format(name))
    group = extension.get('protect') if extension else 'base'
    if group not in groups:
        groups[group] = []
    groups[group].append('  X({})\\\n'.format(name))

filename = 'lox.h'

X = ''.join(groups['base'])[:-2] + '\n'

with open(filename, 'r') as f:
    contents = f.read()

contents = re.sub(r'(  X\(.+\)\\?\n)+', X, contents)

with open(filename, 'w') as f:
    f.write(contents)
