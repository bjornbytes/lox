#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include "jsmn.h"
#include "lox.h"
#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv) {
  XrResult result;

  uint32_t count;
  printf("Querying extension count...\n");
  result = xrEnumerateInstanceExtensionProperties(NULL, 0, &count, NULL);
  printf("Result %d, %d extensions\n", result, count);

  XrExtensionProperties extensions[32];
  for (size_t i = 0; i < sizeof(extensions) / sizeof(extensions[0]); i++) {
    extensions[i].type = XR_TYPE_EXTENSION_PROPERTIES;
    extensions[i].next = NULL;
  }

  printf("Querying extensions...\n");
  result = xrEnumerateInstanceExtensionProperties(NULL, count, &count, extensions);
  printf("Result %d, %d extensions\n", result, count);

  for (uint32_t i = 0; i < count; i++) {
    printf("  [%2d] (v%d) %s\n", i, extensions[i].extensionVersion, extensions[i].extensionName);
  }

  XrInstanceCreateInfo info = {
    .type = XR_TYPE_INSTANCE_CREATE_INFO,
    .applicationInfo = {
      .applicationName = "test",
      .apiVersion = XR_CURRENT_API_VERSION
    }
  };

  XrInstance instance;
  result = xrCreateInstance(&info, &instance);
  if (XR_FAILED(result)) {
    printf("Failed to create instance [%d]\n", result);
    return 1;
  } else {
    printf("Created instance\n");
  }

  xrDestroyInstance(instance);
  return 0;
}
