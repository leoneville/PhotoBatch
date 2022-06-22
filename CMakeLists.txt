cmake_minimum_required(VERSION 3.12)
project(PhotoBatch CXX)

add_executable(PhotoBatch)

target_sources(
	PhotoBatch
	PRIVATE
		ArgumentParser.cpp
		ArgumentParser.hpp
		PhotoBatch.cpp
		Utils.cpp
		Utils.hpp
 "Unittests/TestArgumentParser.cpp")

set_target_properties(PhotoBatch PROPERTIES CXX_STANDARD 17)

add_subdirectory(Unittests)