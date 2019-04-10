#
# Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
#
# All rights reserved. This program and the accompanying materials are made available under the
# terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
# available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#

SET(CMAKE_MACOSX_RPATH 1)
SET(CMAKE_CXX_STANDARD 11)
PROJECT(TU C CXX)

IF(WIN32)
	ADD_COMPILE_OPTIONS(/wd4275 /wd4251 /wd4290)
ENDIF(WIN32)

CONFIGURE_FILE(CMakeLists.txt.in googletest-download/CMakeLists.txt)
EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)

IF(result)
    MESSAGE(FATAL_ERROR "CMake step for googletest failed: ${result}")
ENDIF()

EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)

IF(result)
    MESSAGE(FATAL_ERROR "Build step for googletest failed: ${result}")
ENDIF()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL
)


INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple
    ${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/plugin/stub 
    ${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/seproxy/exception
    ${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/seproxy/plugin
    ${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/seproxy/event

	# Example generic common
	${CMAKE_CURRENT_SOURCE_DIR}/../../../common/src/main/java/org/eclipse/keyple/example/generic/common

	# Common
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-common/src/main/java/org/eclipse/keyple/common

	# Core
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/command
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/event
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/exception
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/message
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/plugin
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/protocol
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/transaction
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/util

	# Calypso
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/transaction
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/command
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/command/po/parser

	# Plugin - stub
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../../component/keyple-plugin/stub/src/main/java/org/eclipse/keyple/plugin/stub

	# google test and mock
	${CMAKE_CURRENT_BINARY_DIR}/googletest-src
)

ADD_EXECUTABLE(TU_plugin_stub_test
	# TU Stub
	${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/plugin/stub/BaseStubTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/plugin/stub/StubPluginTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple/plugin/stub/StubReaderTest.cpp
)

SET(LINK_LIBS gtest gmock ${WINSCARD} )

TARGET_LINK_LIBRARIES(TU_plugin_stub_test ${LINK_LIBS})
