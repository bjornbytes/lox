#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#else
#error "Unsupported platform"
#endif

#ifdef LOX_STATIC
#define LOX_API static XRAPI_ATTR
#else
#define LOX_API XRAPI_ATTR
#endif

// OpenXR

// === 8< ===
#ifdef XR_USE_TIMESPEC
#define XR_FOREACH_TIMESPEC(X)\
  X(xrConvertTimespecTimeToTimeKHR)\
  X(xrConvertTimeToTimespecTimeKHR)
#else
#define XR_FOREACH_TIMESPEC(X)
#endif

#ifdef XR_USE_GRAPHICS_API_D3D11
#define XR_FOREACH_D3D11(X)\
  X(xrGetD3D11GraphicsRequirementsKHR)
#else
#define XR_FOREACH_D3D11(X)
#endif

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
#define XR_FOREACH_ES(X)\
  X(xrGetOpenGLESGraphicsRequirementsKHR)
#else
#define XR_FOREACH_ES(X)
#endif

#ifdef XR_USE_GRAPHICS_API_VULKAN
#define XR_FOREACH_VULKAN(X)\
  X(xrGetVulkanInstanceExtensionsKHR)\
  X(xrGetVulkanDeviceExtensionsKHR)\
  X(xrGetVulkanGraphicsDeviceKHR)\
  X(xrGetVulkanGraphicsRequirementsKHR)
#else
#define XR_FOREACH_VULKAN(X)
#endif

#ifdef XR_USE_GRAPHICS_API_D3D12
#define XR_FOREACH_D3D12(X)\
  X(xrGetD3D12GraphicsRequirementsKHR)
#else
#define XR_FOREACH_D3D12(X)
#endif

#ifdef XR_USE_GRAPHICS_API_OPENGL
#define XR_FOREACH_OPENGL(X)\
  X(xrGetOpenGLGraphicsRequirementsKHR)
#else
#define XR_FOREACH_OPENGL(X)
#endif

#define XR_FOREACH_BASE(X)\
  X(xrResultToString)\
  X(xrStructureTypeToString)\
  X(xrGetInstanceProperties)\
  X(xrGetSystem)\
  X(xrGetSystemProperties)\
  X(xrCreateSession)\
  X(xrDestroySession)\
  X(xrDestroySpace)\
  X(xrEnumerateSwapchainFormats)\
  X(xrCreateSwapchain)\
  X(xrDestroySwapchain)\
  X(xrEnumerateSwapchainImages)\
  X(xrAcquireSwapchainImage)\
  X(xrWaitSwapchainImage)\
  X(xrReleaseSwapchainImage)\
  X(xrBeginSession)\
  X(xrEndSession)\
  X(xrRequestExitSession)\
  X(xrEnumerateReferenceSpaces)\
  X(xrCreateReferenceSpace)\
  X(xrCreateActionSpace)\
  X(xrLocateSpace)\
  X(xrEnumerateViewConfigurations)\
  X(xrEnumerateEnvironmentBlendModes)\
  X(xrGetViewConfigurationProperties)\
  X(xrEnumerateViewConfigurationViews)\
  X(xrBeginFrame)\
  X(xrLocateViews)\
  X(xrEndFrame)\
  X(xrWaitFrame)\
  X(xrApplyHapticFeedback)\
  X(xrStopHapticFeedback)\
  X(xrPollEvent)\
  X(xrStringToPath)\
  X(xrPathToString)\
  X(xrGetReferenceSpaceBoundsRect)\
  X(xrGetActionStateBoolean)\
  X(xrGetActionStateFloat)\
  X(xrGetActionStateVector2f)\
  X(xrGetActionStatePose)\
  X(xrCreateActionSet)\
  X(xrDestroyActionSet)\
  X(xrCreateAction)\
  X(xrDestroyAction)\
  X(xrSuggestInteractionProfileBindings)\
  X(xrAttachSessionActionSets)\
  X(xrGetCurrentInteractionProfile)\
  X(xrSyncActions)\
  X(xrEnumerateBoundSourcesForAction)\
  X(xrGetInputSourceLocalizedName)\
  X(xrPerfSettingsSetPerformanceLevelEXT)\
  X(xrThermalGetTemperatureTrendEXT)\
  X(xrSetDebugUtilsObjectNameEXT)\
  X(xrCreateDebugUtilsMessengerEXT)\
  X(xrDestroyDebugUtilsMessengerEXT)\
  X(xrSubmitDebugUtilsMessageEXT)\
  X(xrSessionBeginDebugUtilsLabelRegionEXT)\
  X(xrSessionEndDebugUtilsLabelRegionEXT)\
  X(xrSessionInsertDebugUtilsLabelEXT)\
  X(xrGetVisibilityMaskKHR)\
  X(xrCreateSpatialAnchorMSFT)\
  X(xrCreateSpatialAnchorSpaceMSFT)\
  X(xrDestroySpatialAnchorMSFT)\
  X(xrSetInputDeviceActiveEXT)\
  X(xrSetInputDeviceStateBoolEXT)\
  X(xrSetInputDeviceStateFloatEXT)\
  X(xrSetInputDeviceStateVector2fEXT)\
  X(xrSetInputDeviceLocationEXT)\
  X(xrCreateSpatialGraphNodeSpaceMSFT)\
  X(xrCreateHandTrackerEXT)\
  X(xrDestroyHandTrackerEXT)\
  X(xrLocateHandJointsEXT)\
  X(xrCreateHandMeshSpaceMSFT)\
  X(xrUpdateHandMeshMSFT)

#ifdef XR_USE_PLATFORM_ANDROID
#define XR_FOREACH_ANDROID(X)\
  X(xrSetAndroidApplicationThreadKHR)\
  X(xrCreateSwapchainAndroidSurfaceKHR)
#else
#define XR_FOREACH_ANDROID(X)
#endif

#ifdef XR_USE_PLATFORM_WIN32
#define XR_FOREACH_WIN32(X)\
  X(xrConvertWin32PerformanceCounterToTimeKHR)\
  X(xrConvertTimeToWin32PerformanceCounterKHR)
#else
#define XR_FOREACH_WIN32(X)
#endif

#define XR_FOREACH(X)\
  XR_FOREACH_TIMESPEC(X)\
  XR_FOREACH_D3D11(X)\
  XR_FOREACH_ES(X)\
  XR_FOREACH_VULKAN(X)\
  XR_FOREACH_D3D12(X)\
  XR_FOREACH_OPENGL(X)\
  XR_FOREACH_BASE(X)\
  XR_FOREACH_ANDROID(X)\
  XR_FOREACH_WIN32(X)
// === >8 ===

#define XR_CURRENT_LOADER_API_LAYER_VERSION 1
#define XR_CURRENT_LOADER_RUNTIME_VERSION 1

typedef enum XrLoaderInterfaceStructs {
  XR_LOADER_INTERFACE_STRUCT_UNINITIALIZED = 0,
  XR_LOADER_INTERFACE_STRUCT_LOADER_INFO,
  XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST,
  XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST,
  XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO,
  XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO
} XrLoaderInterfaceStructs;

#define XR_LOADER_INFO_STRUCT_VERSION 1
typedef struct XrNegotiateLoaderInfo {
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  uint32_t minInterfaceVersion;
  uint32_t maxInterfaceVersion;
  XrVersion minApiVersion;
  XrVersion maxApiVersion;
} XrNegotiateLoaderInfo;

#define XR_RUNTIME_INFO_STRUCT_VERSION 1
typedef struct XrNegotiateRuntimeRequest {
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  uint32_t runtimeIntefaceVersion;
  XrVersion runtimeApiVersion;
  PFN_xrGetInstanceProcAddr getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

typedef XrResult FN_xrNegotiateLoaderRuntimeInterface(const XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeInfo);

// Helpers


static struct {
  void* library;
  XrNegotiateRuntimeRequest runtimeInfo;
  struct {
#define LOX_FN(fn) PFN_##fn fn;
    XR_FOREACH(LOX_FN)
#undef LOX_FN
  } dispatch;
} state;

static XrResult loadRuntime() {
  if (state.library) return XR_SUCCESS;

  char filename[1024];
  char buffer[4096];
  const char* leaf = "/openxr/1/active_runtime.json";

#if defined __linux__
  int fd = -1;

  if (fd < 0) {
    const char* path = getenv("XR_RUNTIME_JSON");
    if (path) fd = open(path, O_RDONLY);
  }

  if (fd < 0) {
    const char* home = getenv("XDG_CONFIG_HOME");

    if (home) {
      size_t length = strlen(home) + strlen(leaf);
      if (length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;
      stpcpy(stpcpy(filename, home), leaf);
      fd = open(filename, O_RDONLY);
    } else {
      const char* fallback = getenv("HOME");
      const char* config = "/.config";

      if (fallback) {
        size_t length = strlen(fallback) + strlen(config) + strlen(leaf);
        if (length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;
        stpcpy(stpcpy(stpcpy(filename, fallback), config), leaf);
        fd = open(filename, O_RDONLY);
      }
    }
  }

  if (fd < 0) {
    const char* dirs = getenv("XDG_CONFIG_DIRS");

    if (dirs) {
      while (1) {
        char* sep = strchr(dirs, ':');
        if (!sep) sep = strchr(dirs, '\0');

        if (sep == dirs) {
          dirs++;
          continue;
        }

        size_t dirLength = sep - dirs;
        size_t length = dirLength + strlen(leaf);
        if (length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;
        memcpy(filename, dirs, dirLength);
        strcpy(filename + dirLength, leaf);

        fd = open(filename, O_RDONLY);
        if (fd >= 0) break;

        if (*sep == '\0') {
          break;
        } else {
          dirs = sep + 1;
        }
      }
    } else {
      const char* fallback = "/etc/xdg";
      size_t length = strlen(fallback) + strlen(leaf);
      if (length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;
      stpcpy(stpcpy(filename, fallback), leaf);
      fd = open(filename, O_RDONLY);
    }
  }

  if (fd < 0) {
    const char* etc = "/etc";
    size_t length = strlen(etc) + strlen(leaf);
    if (length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;
    stpcpy(stpcpy(filename, etc), leaf);
    fd = open(filename, O_RDONLY);
  }

  if (fd < 0) {
    return XR_ERROR_FILE_ACCESS_ERROR;
  }

  struct stat st;
  if (fstat(fd, &st) < 0) {
    close(fd);
    return XR_ERROR_FILE_ACCESS_ERROR;
  }

  size_t size = st.st_size;
  if (size > sizeof(buffer)) {
    close(fd);
    return XR_ERROR_OUT_OF_MEMORY;
  }

  size_t n = 0;
  while (n < size) {
    ssize_t bytes = read(fd, buffer + n, size - n);
    if (bytes < 0) {
      close(fd);
      return XR_ERROR_FILE_ACCESS_ERROR;
    }
    n += bytes;
  }
  close(fd);
#else
#error "Unsupported platform"
#endif

  jsmntok_t tokens[256];
  jsmn_parser parser;
  jsmn_init(&parser);
  int tokenCount = jsmn_parse(&parser, buffer, size, tokens, sizeof(tokens) / sizeof(tokens[0]));
  switch (tokenCount) {
    case JSMN_ERROR_NOMEM: return XR_ERROR_OUT_OF_MEMORY;
    case JSMN_ERROR_INVAL: return XR_ERROR_FILE_CONTENTS_INVALID;
    case JSMN_ERROR_PART: return XR_ERROR_FILE_CONTENTS_INVALID;
    case 0: return XR_ERROR_FILE_CONTENTS_INVALID;
    default: break;
  }

  if (tokens[0].type != JSMN_OBJECT) {
    return XR_ERROR_FILE_CONTENTS_INVALID;
  }

  jsmntok_t* version = NULL;
  jsmntok_t* library = NULL;

  for (int i = 1; i < tokenCount; i++) {
    jsmntok_t* token = &tokens[i];
    const char* key = buffer + token->start;
    size_t length = token->end - token->start;
    token++;

    // TODO parse `instance_extensions` and `functions` keys
    if (length == strlen("file_format_version") && !strncmp(key, "file_format_version", length)) {
      if (token->type != JSMN_STRING) return XR_ERROR_FILE_CONTENTS_INVALID;
      version = token++;
    } else if (length == strlen("runtime") && !strncmp(key, "runtime", length)) {
      if (token->type != JSMN_OBJECT) return XR_ERROR_FILE_CONTENTS_INVALID;
      for (int j = (token++)->size; j > 0; j--) {
        const char* key = buffer + token->start;
        size_t length = token->end - token->start;
        token++;

        if (length == strlen("library_path") && !strncmp(key, "library_path", length)) {
          library = token++;
        } else {
          for (int n = 1; n > 0; n--, token++) {
            switch (token->type) {
              case JSMN_OBJECT: n += 2 * token->size; break;
              case JSMN_ARRAY: n += token->size; break;
              default: break;
            }
          }
        }
      }
    } else {
      for (int n = 1; n > 0; n--, token++) {
        switch (token->type) {
          case JSMN_OBJECT: n += 2 * token->size; break;
          case JSMN_ARRAY: n += token->size; break;
          default: break;
        }
      }
    }
  }

  if (!version || !library || strncmp(buffer + version->start, "1.0.0", version->end - version->start)) {
    return XR_ERROR_FILE_CONTENTS_INVALID;
  }

  FN_xrNegotiateLoaderRuntimeInterface* negotiate;

#ifdef __linux__
  size_t length = library->end - library->start;
  if (length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;

  if (buffer[library->start] == '/') {
    memcpy(filename, buffer + library->start, length);
    filename[length] = '\0';
  } else if (memchr(buffer + library->start, '/', length)) {
    char* slash = strrchr(filename, '/');
    slash = slash ? slash + 1 : filename;
    if (slash - filename + length >= sizeof(filename)) return XR_ERROR_OUT_OF_MEMORY;
    memcpy(slash, buffer + library->start, length);
    slash[length] = '\0';
  } else {
    memcpy(filename, buffer + library->start, length);
    filename[length] = '\0';
  }

  state.library = dlopen(filename, RTLD_LAZY | RTLD_LOCAL);
  if (!state.library) return XR_ERROR_INSTANCE_LOST;

  negotiate = dlsym(state.library, "xrNegotiateLoaderRuntimeInterface");
  if (!negotiate) return XR_ERROR_INSTANCE_LOST;
#else
#error "Unsupported platform"
#endif

  XrNegotiateLoaderInfo loaderInfo = {
    .structType = XR_LOADER_INTERFACE_STRUCT_LOADER_INFO,
    .structVersion = XR_LOADER_INFO_STRUCT_VERSION,
    .structSize = sizeof(XrNegotiateLoaderInfo),
    .minInterfaceVersion = XR_CURRENT_LOADER_RUNTIME_VERSION,
    .maxInterfaceVersion = XR_CURRENT_LOADER_RUNTIME_VERSION,
    .minApiVersion = XR_MAKE_VERSION(1, 0, 0),
    .maxApiVersion = XR_MAKE_VERSION(1, 0x3ff, 0xfff)
  };

  state.runtimeInfo = (XrNegotiateRuntimeRequest) {
    .structType = XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST,
    .structVersion = XR_RUNTIME_INFO_STRUCT_VERSION,
    .structSize = sizeof(XrNegotiateRuntimeRequest)
  };

  XrResult result = negotiate(&loaderInfo, &state.runtimeInfo);
  if (XR_FAILED(result)) return XR_ERROR_INSTANCE_LOST;
  if (!state.runtimeInfo.getInstanceProcAddr) return XR_ERROR_FILE_CONTENTS_INVALID;

  return XR_SUCCESS;
}

static XrResult unloadRuntime() {
  if (!state.library) return XR_SUCCESS;
#ifdef __linux__
  dlclose(state.library);
#else
#error "Unsupported platform"
#endif
  memset(&state, 0, sizeof(state));
  return XR_SUCCESS;
}

// Entry

LOX_API XrResult XRAPI_CALL xrEnumerateApiLayerProperties(uint32_t capacity, uint32_t* count, XrApiLayerProperties* properties) {
  return XR_SUCCESS;
}

LOX_API XrResult XRAPI_CALL xrEnumerateInstanceExtensionProperties(const char* layer, uint32_t capacity, uint32_t* count, XrExtensionProperties* properties) {
  return XR_SUCCESS;
}

LOX_API XrResult XRAPI_CALL xrCreateInstance(const XrInstanceCreateInfo* info, XrInstance* instance) {
  if (!info || !instance || info->type != XR_TYPE_INSTANCE_CREATE_INFO) {
    return XR_ERROR_VALIDATION_FAILURE;
  }

  if (info->applicationInfo.apiVersion > XR_CURRENT_API_VERSION) {
    return XR_ERROR_API_VERSION_UNSUPPORTED;
  }

  XrResult result = loadRuntime();
  if (XR_FAILED(result)) return result;

  // TODO check runtime version

  // TODO load api layers

  // TODO ensure enabled extensions are supported

  PFN_xrCreateInstance rt_xrCreateInstance;
  result = state.runtimeInfo.getInstanceProcAddr(XR_NULL_HANDLE, "xrCreateInstance", (PFN_xrVoidFunction*) &rt_xrCreateInstance);
  if (XR_FAILED(result)) return unloadRuntime(), result;

  result = rt_xrCreateInstance(info, instance);
  if (XR_FAILED(result)) return unloadRuntime(), *instance = XR_NULL_HANDLE, result;

  #define LOX_LOAD(fn)\
    result = state.runtimeInfo.getInstanceProcAddr(*instance, #fn, (PFN_xrVoidFunction*) &state.dispatch.fn);\
    if (XR_FAILED(result)) return unloadRuntime(), *instance = XR_NULL_HANDLE, result;

  XR_FOREACH(LOX_LOAD)

  return XR_SUCCESS;
}

LOX_API XrResult XRAPI_CALL xrDestroyInstance(XrInstance instance) {
  return unloadRuntime();
}

static uint64_t hash64(const void* data, size_t length) {
  const uint8_t* bytes = (const uint8_t*) data;
  uint64_t hash = 0xcbf29ce484222325;
  for (size_t i = 0; i < length; i++) {
    hash = (hash ^ bytes[i]) * 0x100000001b3;
  }
  return hash;
}

LOX_API XrResult XRAPI_CALL xrGetInstanceProcAddr(XrInstance instance, const char* name, PFN_xrVoidFunction* p) {
  if (!instance || !state.library) return XR_ERROR_HANDLE_INVALID;
  uint64_t hash = hash64(name, strlen(name));
  #define LOX_MATCH(fn) if (hash == hash64(#fn, strlen(#fn))) return *(PFN_##fn*) p = state.dispatch.fn, XR_SUCCESS;
  XR_FOREACH(LOX_MATCH)
  return XR_ERROR_FUNCTION_UNSUPPORTED;
}
