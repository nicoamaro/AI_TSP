import os
import sys
import glob
import subprocess

from cffi import FFI

ffi = FFI()

THIS_FILE_PATH = os.path.abspath(os.path.dirname(__file__))
C_SRC_PATH = os.path.join(THIS_FILE_PATH, ".")

headers, c_sources = [os.path.join(C_SRC_PATH, "list_node.h")], [os.path.join(C_SRC_PATH, "list_node.c")]
preprocessed_headers = subprocess.Popen(['cc', '-E', '-DLIST_NODE_NOINCLUDE'] + headers,
                                        stdout=subprocess.PIPE).communicate()[0]
ffi.cdef(preprocessed_headers.decode("utf-8"))

sources = map(lambda x: open(x).read(), c_sources)
extra_compile_args = ["-std=c99", "-Wno-unused-variable", '-UNDEBUG']


if "LIST_NODE_NOINCLUDE_DEBUG" in os.environ:
    extra_compile_args.append("-DLIST_NODE_NOINCLUDE_DEBUG")

ffi.set_source("_lib_list_node", "\n".join(sources), extra_compile_args=extra_compile_args, include_dirs=[C_SRC_PATH])

if not "FFI_NOBUILD" in os.environ:
    ffi.compile(tmpdir=THIS_FILE_PATH)
    from _lib_list_node import lib, ffi
