# Copyright (C) 2020-2021 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

set(NATIVE_TEST_SRC main.cpp
)

if (HEXL_EXPERIMENTAL)
    list(APPEND NATIVE_TEST_SRC
        experimental/seal/test-ckks-switch-key.cpp
    )
endif()

set(AVX512_TEST_SRC
)

set(TEST_SRC "${NATIVE_TEST_SRC};${AVX512_TEST_SRC}")

add_executable(unit-test ${TEST_SRC})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(unit-test PRIVATE -Wall -Wextra -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Disable inline, due to incorrect optimization in ExtractValues, causing failing tests in Windows AVX512 in Release mode with HEXL_DEBUG=OFF
    target_compile_options(unit-test PRIVATE /Wall /W4 /Ob0
        /wd4127 # warning C4127: conditional expression is constant; C++11 doesn't support if constexpr
        /wd4389 # warning C4389: signed/unsigned mismatch from gtest
        /wd5105 # warning C5105: macro expansion producing 'defined' has undefined behavior
    )
    target_compile_definitions(unit-test PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(unit-test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${HEXL_SRC_ROOT_DIR} # Private headers
)

# Link to cpu_features to allow selectively disabling AVX512 support for CI
target_link_libraries(unit-test PRIVATE hexl cpu_features gtest Threads::Threads)
if (HEXL_DEBUG)
    target_link_libraries(unit-test PRIVATE easyloggingpp)
endif()

# Make sure that public include folder doesn't use private headers
# and that public headers are self-contained
# TODO(fboemer): Re-enable when coverage build integration works
# add_executable(test-public-api test-public-api.cpp)
# add_dependencies(test-public-api hexl)
# if (HEXL_DEBUG)
#     target_link_libraries(test-public-api PUBLIC easyloggingpp)
# endif()
# target_include_directories(test-public-api PRIVATE ${HEXL_INC_ROOT_DIR})
# target_include_directories(test-public-api
#       PRIVATE $<TARGET_PROPERTY:cpu_features,INTERFACE_INCLUDE_DIRECTORIES>)
