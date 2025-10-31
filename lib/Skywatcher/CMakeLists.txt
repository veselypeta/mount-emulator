
add_library(MESkywatcher STATIC 
    SkywatcherMount.cpp
)
target_include_directories(MESkywatcher PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(MESkywatcher PRIVATE Boost::headers)
