#include <cstdint>
#include <optional>

#include <safetyhook.hpp>
#include <windows.h>

SafetyHookInline g_sum_hook{};

std::optional<int> hook_sum(int a, int b) noexcept {
  return g_sum_hook.call<std::optional<int>>(2, 2);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID) {
  switch (reason) {
  case DLL_PROCESS_ATTACH: {
    // replace it to actual RVA.
    constexpr std::uintptr_t sum_rva = 0x0000000000001240;

    HMODULE exe = GetModuleHandleW(nullptr);
    if (!exe) {
      return FALSE;
    }

    auto base = reinterpret_cast<std::uintptr_t>(exe);
    auto target = reinterpret_cast<void *>(base + sum_rva);

    g_sum_hook =
        safetyhook::create_inline(target, reinterpret_cast<void *>(&hook_sum));

    if (!g_sum_hook) {
      OutputDebugStringA("hook: failed to create inline hook\n");
      return FALSE;
    }

    OutputDebugStringA("hook: sum hooked\n");
    break;
  }

  case DLL_PROCESS_DETACH:
    g_sum_hook.reset();
    break;
  }

  return TRUE;
}
