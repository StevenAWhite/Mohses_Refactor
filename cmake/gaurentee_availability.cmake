cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)

option(BUILD_THIRDPARTY_TEST "Enables Sample Projects for ThirdParty Packages" ON)

include(gaurentee_boost)
include(gaurentee_fastcdr)
include(gaurentee_fastddr)
include(gaurentee_TinyXML2)
include(gaurentee_foonathan_memory)
