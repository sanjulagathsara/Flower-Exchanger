#ifndef FLOWER_EXCHANGER_CSVWRITER_H
#define FLOWER_EXCHANGER_CSVWRITER_H

#include <string>
#include <vector>
#include "ExecutionReport.h"

class CsvWriter {
public:
    static void writeExecutionReports(const std::string& filename,
                                      const std::vector<ExecutionReport>& reports);
};

#endif // FLOWER_EXCHANGER_CSVWRITER_H