#include <openxr/openxr.h>
#include "jsmn.h"
#include "lox.h"

int main(int argc, char** argv) {
  XrInstance instance;

  XrInstanceCreateInfo info = {
    .type = XR_TYPE_INSTANCE_CREATE_INFO,
    .applicationInfo = {
      .applicationName = "test",
      .apiVersion = XR_CURRENT_API_VERSION
    }
  };

  XrResult result = xrCreateInstance(&info, &instance);
  if (XR_FAILED(result)) return 1;
  xrDestroyInstance(instance);
  return 0;
}
