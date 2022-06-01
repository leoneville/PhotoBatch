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
)