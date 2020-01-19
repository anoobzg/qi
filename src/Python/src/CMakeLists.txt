cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(python C)

include_directories("${CMAKE_SOURCE_DIR}/include/")
include_directories("${CMAKE_SOURCE_DIR}/include/internal/")
include_directories("${CMAKE_SOURCE_DIR}/PC/")
include_directories("${CMAKE_SOURCE_DIR}/Python/")

add_definitions("-DPy_BUILD_CORE")
add_executable(python "./Programs/python.c")

add_definitions("-DPy_BUILD_CORE_BUILTIN")
add_definitions("-DPy_ENABLE_SHARED")

file(GLOB PARSER_SRC Parser/*.c)

macro(expand dst src folder)
foreach(file_name ${src})
list(APPEND ${dst} ${CMAKE_SOURCE_DIR}/${folder}/${file_name}) 
endforeach()
endmacro()

set(PYTHON_FILES _warnings.c asdl.c ast.c ast_opt.c ast_unparse.c
				 bltinmodule.c bootstrap_hash.c ceval.c codecs.c
				 compile.c context.c dtoa.c dynamic_annotations.c dynload_win.c
				 errors.c fileutils.c formatter_unicode.c frozen.c future.c
				 getargs.c getcompiler.c getcopyright.c getopt.c getplatform.c
				 getversion.c graminit.c hamt.c import.c importdl.c initconfig.c marshal.c
				 modsupport.c mysnprintf.c mystrtoul.c pathconfig.c peephole.c preconfig.c
				 pyarena.c pyctype.c pyfpe.c pyhash.c pylifecycle.c pymath.c pystate.c 
				 pystrcmp.c pystrhex.c pystrtod.c Python-ast.c pythonrun.c pytime.c
				 structmember.c symtable.c sysmodule.c thread.c traceback.c)
set(PYTHON_SRC)
expand(PYTHON_SRC "${PYTHON_FILES}" Python)

set(PC_FILES config.c dl_nt.c getpathp.c invalid_parameter_handler.c msvcrtmodule.c winreg.c)
set(PC_SRC)
expand(PC_SRC "${PC_FILES}" PC)

set(OBJECTS_FILES abstract.c accu.c boolobject.c bytearrayobject.c bytes_methods.c bytesobject.c
					call.c capsule.c cellobject.c classobject.c codeobject.c complexobject.c
					descrobject.c dictobject.c enumobject.c exceptions.c fileobject.c floatobject.c
					frameobject.c funcobject.c genobject.c interpreteridobject.c iterobject.c listobject.c
					longobject.c memoryobject.c methodobject.c moduleobject.c namespaceobject.c object.c obmalloc.c 
					odictobject.c picklebufobject.c rangeobject.c setobject.c setobject.c setobject.c sliceobject.c structseq.c
					tupleobject.c typeobject.c unicodectype.c unicodeobject.c weakrefobject.c)
set(OBJECTS_SRC)
expand(OBJECTS_SRC "${OBJECTS_FILES}" Objects)

set(MODULES_FILES _winapi.c _abc.c _bisectmodule.c _codecsmodule.c _collectionsmodule.c _contextvarsmodule.c
					_csv.c _datetimemodule.c _functoolsmodule.c _heapqmodule.c _json.c _localemodule.c
					_lsprof.c _math.c _opcode.c _operator.c _pickle.c _randommodule.c _sre.c _stat.c
					_statisticsmodule.c _struct.c _threadmodule.c _tracemalloc.c _weakref.c arraymodule.c
					atexitmodule.c audioop.c binascii.c _blake2/blake2b_impl.c _blake2/blake2module.c _blake2/blake2s_impl.c cmathmodule.c
					errnomodule.c faulthandler.c gcmodule.c hashtable.c itertoolsmodule.c main.c mathmodule.c
					md5module.c mmapmodule.c parsermodule.c posixmodule.c rotatingtree.c sha1module.c _sha3/sha3module.c
					sha256module.c sha512module.c signalmodule.c symtablemodule.c timemodule.c xxsubtype.c
					_io/_iomodule.c _io/bufferedio.c _io/bytesio.c _io/fileio.c _io/iobase.c _io/stringio.c _io/textio.c
					_io/winconsoleio.c getbuildinfo.c _xxsubinterpretersmodule.c
					cjkcodecs/_codecs_cn.c cjkcodecs/_codecs_hk.c cjkcodecs/_codecs_iso2022.c cjkcodecs/_codecs_jp.c cjkcodecs/_codecs_kr.c
					cjkcodecs/_codecs_tw.c cjkcodecs/multibytecodec.c )
set(MODULES_SRC)
expand(MODULES_SRC "${MODULES_FILES}" Modules)

add_library(pythoncore SHARED ${PARSER_SRC} ${PYTHON_SRC} ${PC_SRC} ${OBJECTS_SRC} ${MODULES_SRC})

target_link_libraries(pythoncore version.lib shlwapi.lib ws2_32.lib)
target_link_libraries(python pythoncore)

TopAddTarget(python)
TopAddTarget(pythoncore)
ConfigureAll()