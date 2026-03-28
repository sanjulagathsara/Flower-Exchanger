# Flower Exchanger

A simple C++ flower exchange matching engine that reads orders from a CSV file, validates them, processes matches using price-time priority, and generates execution reports in CSV format.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Supported Instruments](#supported-instruments)
- [Project Structure](#project-structure)

---

## Overview

**Flower Exchanger** is a basic exchange simulation implemented in **C++**.

The program:

1. Reads flower orders from an input CSV file
2. Validates each order
3. Routes each order to the correct flower-specific order book
4. Matches buy and sell orders using **price priority** and **FIFO**
5. Generates execution reports
6. Writes all execution reports to an output CSV file

This project is designed as a small matching engine for flowers such as **Rose**, **Tulip**, **Lotus**, **Lavender**, and **Orchid**.

---

## Features

- Reads orders from CSV
- Supports multiple flower instruments
- Maintains **separate order books per flower**
- Validates malformed and invalid input orders
- Generates execution reports for:
  - `New`
  - `Rejected`
  - `Fill`
  - `Pfill`
- Uses:
  - **Best price first**
  - **FIFO within the same price**
- Writes execution reports to `execution_reports.csv`

---

## Supported Instruments

The following flower instruments are supported:

- Rose
- Lavender
- Lotus
- Tulip
- Orchid

---

## Project Structure

```text
Flower-Exchanger/
├── CMakeLists.txt
├── README.md
├── data/
│   └── order.csv
├── output/
│   └── exeReports.csv
├── include/
│   ├── CsvReader.h
│   ├── CsvWriter.h
│   ├── ExecutionReport.h
│   ├── Order.h
│   ├── OrderBook.h
│   └── Validator.h
└── src/
    ├── CsvReader.cpp
    ├── CsvWriter.cpp
    ├── main.cpp
    ├── OrderBook.cpp
    └── Validator.cpp



