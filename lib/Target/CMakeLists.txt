add_library(METarget STATIC 
    TargetInfo.cpp
)
target_include_directories(METarget PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(METarget PRIVATE Boost::headers)