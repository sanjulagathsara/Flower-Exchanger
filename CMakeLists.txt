cmake_minimum_required(VERSION 4.1)
project(Flower_Exchanger)

set(CMAKE_CXX_STANDARD 20)

add_executable(Flower_Exchanger src/main.cpp
        src/OrderBook.cpp
        src/OrderBook.cpp
        include/OrderBook.h
        include/Order.h
        include/ExecutionReport.h
        include/Validator.h
        src/Validator.cpp
        include/CsvReader.h
        src/CsvReader.cpp)
