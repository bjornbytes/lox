url = arg[1] or 'https://raw.githubusercontent.com/KhronosGroup/OpenXR-SDK-Source/master/specification/registry/xr.xml'

if url:match('^http') then
  cmd = io.popen('curl -s ' .. url)
  xml = cmd:read('*a'), cmd:close()
else
  file = assert(io.open(url))
  xml = file:read('*a'), file:close()
end

ignore = {
  xrCreateInstance = true,
  xrDestroyInstance = true,
  xrGetInstanceProcAddr = true,
  xrEnumerateApiLayerProperties = true,
  xrEnumerateInstanceExtensionProperties = true
}

groups = {}

for group, body in xml:gmatch('<extension[^\n]+protect="([%w_]+)"[^\n]*>(.-)</extension>') do
  for fn in body:gmatch('<command name="(%w+)"/>') do
    groups[group] = groups[group] or {}
    table.insert(groups[group], fn)
    ignore[fn] = true
  end
end

groups.BASE = {}
for command in xml:gmatch('<command.-</command>') do
  local fn = command:match('<proto.-<name>(%w+)')
  if not ignore[fn] and not command:match('alias') then
    table.insert(groups.BASE, fn)
  end
end

out = '// === 8< ===\n'
for group, t in pairs(groups) do
  if next(t) then
    local name = group:match('[^_]+$')
    local macro = { ('#define XR_FOREACH_%s(X)\\\n'):format(name) }
    for i, fn in ipairs(t) do
      table.insert(macro, ('  X(%s)\\\n'):format(fn))
    end
    macro = table.concat(macro, ''):sub(1, -3) .. '\n'

    if group ~= 'BASE' then
      macro = ('#ifdef %s\n%s#else\n#define XR_FOREACH_%s(X)\n#endif\n'):format(group, macro, name)
    end

    out = out .. macro .. '\n'
  end
end

out = out .. '#define XR_FOREACH(X)\\\n'
for group in pairs(groups) do
  local name = group:match('[^_]+$')
  out = out .. '  XR_FOREACH_' .. name .. '(X)\\\n'
end
out = out:sub(1, -3) .. '\n// === >8 ==='

file = assert(io.open('lox.h', 'r'))
header = file:read('*a')
file:close()

header = header:gsub('// === 8< ===.+// === >8 ===', out)

file = assert(io.open('lox.h', 'w'))
file:write(header)
file:close()
