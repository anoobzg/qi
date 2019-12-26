cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
include(ConfigureTarget)

project(lua C)

set(LUA_LIB_H
    lua.h
    ltable.h
    lfunc.h
    lgc.h
    lobject.h
    lstate.h
    luaconf.h
    lapi.h
    lauxlib.h
	lcode.h
	ldebug.h
	ldo.h
	llex.h
	llimits.h
	lmem.h
	lopcodes.h
	lparser.h
	lprefix.h
	lstring.h
	ltm.h
	lualib.h
	lundump.h
	lvm.h
	lzio.h
	lctype.h
	lua.hpp
)
set(LUA_LIB_SRC
    ltable.c
    lapi.c
    lgc.c
    ldebug.c
    lparser.c
    lbaselib.c
    lfunc.c
    lstate.c
    ltm.c
    lvm.c
    liolib.c
    lobject.c
    loslib.c
    lstrlib.c
    lutf8lib.c
	lauxlib.c
	lbitlib.c
	lcode.c
	lcorolib.c
	lctype.c
	ldblib.c
	ldo.c
	ldump.c
	linit.c
	llex.c
	lmathlib.c
	lmem.c
	loadlib.c
	lopcodes.c
	lstring.c
	ltablib.c
	lundump.c
	lzio.c
)

set(LUA_EXE
lua.c
)

set(LUAC_EXE
luac.c
)

add_library(liblua STATIC ${LUA_LIB_H} ${LUA_LIB_SRC})
add_executable(lua ${LUA_LIB_H} ${LUA_LIB_SRC} ${LUA_EXE})
add_executable(luac ${LUA_LIB_H} ${LUA_LIB_SRC} ${LUAC_EXE})

TopAddTarget(liblua)
TopAddTarget(lua)
TopAddTarget(luac)

ConfigureAll()