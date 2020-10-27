include_directories(${INCLUDE_DIR})

add_library(libasync SHARED
        include/async.h
        include/block_processor.h
        include/command_container.h
        include/command_processor.h
        include/observer.h
        include/stream.h
        src/async.cpp
        src/block_processor.cpp
        src/command_container.cpp
        src/command_processor.cpp
        src/observer.cpp
        src/stream.cpp
        )

add_executable(${PROJECT_NAME} src/main.cpp src/version.cpp include/version.h)
target_link_libraries(${PROJECT_NAME} libasync)
set_target_properties(${PROJECT_NAME} PROPERTIES ${TARGET_PROPERTIES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/async.h)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

install(TARGETS libasync
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

install(FILES include/async.h DESTINATION include)

