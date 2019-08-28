add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer
        raytracer.cpp
        ../framework/shapes/sphere.cpp
        ../framework/shapes/box.cpp
        ../framework/shapes/shape.cpp
        ../framework/material.cpp
        ../framework/read_sdf.cpp
        ../framework/scene.cpp
        ../framework/shapes/cylinder.cpp
        ../framework/shapes/cone.cpp
        ../framework/shapes/triangle.cpp
        ../framework/shapes/composite.cpp
        ../framework/shapes/composite.hpp ../framework/ray.cpp ../framework/shapes/plane.cpp ../framework/shapes/plane.hpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build tests
add_executable(tests
        tests.cpp
        ../framework/shapes/sphere.cpp
        ../framework/shapes/box.cpp
        ../framework/shapes/shape.cpp
        ../framework/material.cpp
        ../framework/read_sdf.cpp
        ../framework/scene.cpp
        ../framework/shapes/cylinder.cpp
        ../framework/shapes/cone.cpp
        ../framework/shapes/triangle.cpp ../framework/shapes/composite.cpp ../framework/shapes/composite.hpp ../framework/ray.cpp ../framework/shapes/plane.cpp ../framework/shapes/plane.hpp)


target_link_libraries(tests
  ${GLFW_LIBRARIES}
  )

