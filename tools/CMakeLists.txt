
add_executable(me 
    main.cpp)
target_link_libraries(me PRIVATE Boost::program_options METarget)
target_include_directories(me PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_executable(StrandedDeadlock 
    StrandedDeadlock.cpp)
target_link_libraries(StrandedDeadlock PRIVATE Boost::headers Threads::Threads)
