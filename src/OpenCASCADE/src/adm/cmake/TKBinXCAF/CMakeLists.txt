project(TKBinXCAF)

if (WIN32)
  list( APPEND TKBinXCAF_PRECOMPILED_DEFS "-D__BinXCAFDrivers_DLL" )
  list( APPEND TKBinXCAF_PRECOMPILED_DEFS "-D__BinMXCAFDoc_DLL" )
  string( REGEX REPLACE ";" " " TKBinXCAF_PRECOMPILED_DEFS "${TKBinXCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBinXCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBinXCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBinXCAF_COMPILER_DIRECTORIES "../../../drv/BinXCAFDrivers" )
  list( APPEND TKBinXCAF_COMPILER_DIRECTORIES "../../../src/BinXCAFDrivers" )
  list( APPEND TKBinXCAF_COMPILER_DIRECTORIES "../../../drv/BinMXCAFDoc" )
  list( APPEND TKBinXCAF_COMPILER_DIRECTORIES "../../../src/BinMXCAFDoc" )

if (WIN32)
else()
endif()

  list( APPEND TKBinXCAF_USED_LIBS TKBRep )
  list( APPEND TKBinXCAF_USED_LIBS TKXCAF )
  list( APPEND TKBinXCAF_USED_LIBS TKMath )
  list( APPEND TKBinXCAF_USED_LIBS TKernel )
  list( APPEND TKBinXCAF_USED_LIBS TKBinL )
  list( APPEND TKBinXCAF_USED_LIBS TKG2d )
  list( APPEND TKBinXCAF_USED_LIBS TKCAF )
  list( APPEND TKBinXCAF_USED_LIBS TKCDF )
  list( APPEND TKBinXCAF_USED_LIBS TKG3d )
  list( APPEND TKBinXCAF_USED_LIBS TKLCAF )
  list( APPEND TKBinXCAF_USED_LIBS TKBin )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinXCAFDrivers/BinXCAFDrivers.cxx" )
  SOURCE_GROUP (BinXCAFDrivers FILES "../../../src/BinXCAFDrivers/BinXCAFDrivers.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinXCAFDrivers/BinXCAFDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (BinXCAFDrivers FILES "../../../src/BinXCAFDrivers/BinXCAFDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinXCAFDrivers/BinXCAFDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (BinXCAFDrivers FILES "../../../src/BinXCAFDrivers/BinXCAFDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_AreaDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_AreaDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_CentroidDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_CentroidDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_ColorDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_ColorDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_ColorToolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_ColorToolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DatumDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DatumDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DimTolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DimTolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DimTolToolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DimTolToolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DocumentToolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_DocumentToolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_GraphNodeDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_GraphNodeDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_LayerToolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_LayerToolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_LocationDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_LocationDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_MaterialDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_MaterialDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_MaterialToolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_MaterialToolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_ShapeToolDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_ShapeToolDriver.cxx")

  list( APPEND TKBinXCAF_USED_SRCFILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_VolumeDriver.cxx" )
  SOURCE_GROUP (BinMXCAFDoc FILES "../../../src/BinMXCAFDoc/BinMXCAFDoc_VolumeDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBinXCAF)
 add_library( TKBinXCAF SHARED ${TKBinXCAF_USED_SRCFILES} )

 set_property(TARGET TKBinXCAF PROPERTY FOLDER DataExchange)

 install( TARGETS TKBinXCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBinXCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBinXCAF PROPERTIES COMPILE_FLAGS "${TKBinXCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKBinXCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBinXCAF ${TKBinXCAF_USED_LIBS} )
endif()
