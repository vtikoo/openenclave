# libgcov

The source is copied from the profile library as part of [LLVM compiler-rt libraries](http://compiler-rt.llvm.org/).
The current version is based on 7.1.0.

## Modifications

Few changes are made to the source to accommodate TEE (See patches/ for more detail).
- Initialize the `hostfs` during the GCOV initialization (`llvm_gcov_init()`).
  - Ensure that the following filesystem operations work correctly.
- Replace `mmap` and `ummap` (in `map_file()` and `unmap_file()`)
  - `mmap` is not supported by OE. USe `fread()` instead.
  - Alternatively, OE can support `mmap` only for code coverage testing (if there is a performance gap). Note that `mmap` implies using the host memory.