
file(GLOB BASE_ALGRITHM_SRC *.cpp *.h)

IncludeOpenCV()
add_definitions("-DBASE_ALGRITHM_EXPORT")
add_library(BaseAlgrithm SHARED ${BASE_ALGRITHM_SRC})
LinkOpencv(BaseAlgrithm)

AddTarget(BaseAlgrithm)