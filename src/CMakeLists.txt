

# problem 5.1
add_executable(main
  main.cpp
)

target_link_libraries(main
  ${Boost_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  )

install(TARGETS main
  DESTINATION bin
)

