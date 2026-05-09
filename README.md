# TeleQuick Core (C++ FFI)

The C++23 core that backs every language SDK in the TeleQuick family. Exposes a
stable C ABI (`ffi_bridge.cc`) and a WebAssembly build (`apm_wasm.cc`) so
language wrappers — Python, TypeScript, Go, Rust, Java, .NET — share one
serde, one APM (audio processing), and one media pipeline.

## What lives here

- `serde_lite.h` / `serde_test.cc` — zero-allocation wire codec used by every SDK.
- `apm_pipeline.{hh,cc}` — audio processing chain (resample / VAD / denoise hooks).
- `ffi_bridge.cc` — C ABI exported as `libtelequick_core_ffi.so` (and `.dll` / `.dylib`).
- `apm_wasm.cc` / `wasm_bridge.cc` — WASM build for `typescript-sdk` browser usage.
- `apm_ffi.cc` — FFI binding for the audio processing module.
- `g711_lite.h` — PCMU/PCMA codec helpers.

## Build

The canonical build is via Bazel from the TeleQuick workspace; the `BUILD.bazel`
target is `:telequick_core_ffi` (shared library) and `:telequick_core_wasm`
(emscripten WASM module).

```bash
bazel build //:telequick_core_ffi
bazel build //:telequick_core_wasm --config=wasm
```

The resulting artefacts are consumed at runtime by the per-language SDKs —
typically via `TELEQUICK_LIB_PATH` (native) or the bundled `.wasm` (browser).

## Versioning

Method IDs are mirrored across every language SDK. See `serde_lite.h` and the
generated `method_id.*` files in each language repo.
