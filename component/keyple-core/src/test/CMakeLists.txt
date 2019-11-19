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


INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
    #${CMAKE_CURRENT_SOURCE_DIR}/keyple
    #${CMAKE_CURRENT_SOURCE_DIR}/keyple/plugin/stub 
    #${CMAKE_CURRENT_SOURCE_DIR}/keyple/seproxy/exception
    #${CMAKE_CURRENT_SOURCE_DIR}/keyple/seproxy/plugin
	#${CMAKE_CURRENT_SOURCE_DIR}/keyple/seproxy/event
	#${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/seproxy/plugin
	${CMAKE_CURRENT_SOURCE_DIR}/util

	# common
	${CMAKE_CURRENT_SOURCE_DIR}/../../../keyple-common/src/main

	# TLV
	${CMAKE_CURRENT_SOURCE_DIR}/../main/util/bertlv

	# Core
	${CMAKE_CURRENT_SOURCE_DIR}/../main/util
	${CMAKE_CURRENT_SOURCE_DIR}/../main/seproxy/event
	${CMAKE_CURRENT_SOURCE_DIR}/../main/seproxy/message
	${CMAKE_CURRENT_SOURCE_DIR}/../main/seproxy/exception

	# google test and mock
	${GOOGLETEST_DIRECTORY}/googletest-src
	${GOOGLETEST_DIRECTORY}/googletest-src/googlemock/include
	${GOOGLETEST_DIRECTORY}/googletest-src/googletest/include
)

ADD_EXECUTABLE(TU_keyple_util_test
	# TU keyple util
	${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/TLVTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/TagTest.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/util/ConfigurableTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/ByteArrayUtilTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/CountDownLatchTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/ObservableTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/util/NameableTest.cpp
	#${CMAKE_CURRENT_SOURCE_DIR}/CoreBaseTest.cpp
)

SET(LINK_LIBS gtest gmock keyplecore ${WINSCARD} )

TARGET_LINK_LIBRARIES(TU_keyple_util_test ${LINK_LIBS})
