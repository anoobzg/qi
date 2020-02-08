
set(MINI_ZIP_SRC minizip.c unzip.h unzip.c zip.h zip.c ioapi.h ioapi.c crypt.h)
set(WIN_ZIP_SRC iowin32.h iowin32.c)
add_executable(zlib_minizip ${MINI_ZIP_SRC} ${WIN_ZIP_SRC})
target_link_libraries(zlib_minizip zlib)

AddTarget(zlib_minizip)