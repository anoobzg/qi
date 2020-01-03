include(LinkCLapack)
include(LinkOpencv)
 
IncludeCLapack()
IncludeOpencv()
add_executable(test_svd main.cpp)
LinkCLapack(test_svd)
LinkOpencv(test_svd)

AddTarget(test_svd)