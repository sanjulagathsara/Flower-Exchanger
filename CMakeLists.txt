cmake_minimum_required(VERSION 4.1)
project(Flower_Exchanger)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Flower_Exchanger
        src/main.cpp
        src/CsvReader.cpp
        src/CsvWriter.cpp
        src/Validator.cpp
        src/OrderBook.cpp
)