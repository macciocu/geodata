#include <catch2.h>

#include <string>
#include <vector>

#include "app/Csv.h"

using namespace std;

TEST_CASE("CsvReader::writeNextRow, CSVWriter::readNextRow") {
  const int rows = 100000;
  const char delimiter = GENERATE(',', ' ');
  const string tmpCsvFile = "../data/tmp.csv";

  SECTION("test: write to csv") {
    geo::CsvWriter csvWriter(tmpCsvFile, delimiter);
    for (int i = 0; i < rows; ++i) {
      vector<string> row{to_string(i), to_string(i + 1), to_string(i + 2)};
      csvWriter.writeNextRow(row);
    }
  }

  SECTION("test: read from csv") {
    int rowCount = 0;
    geo::CsvReader csvReader(tmpCsvFile, delimiter);
    vector<string> row;
    while (csvReader.readNextRow(row)) {
      if (row.size() != 3)
        FAIL("row.size() != 3");
      REQUIRE(stoi(row[0]) == rowCount);
      REQUIRE(stoi(row[1]) == rowCount + 1);
      REQUIRE(stoi(row[2]) == rowCount + 2);
      ++rowCount;
    }

    REQUIRE(rowCount == rows);
  }

  SECTION("cleanup") { remove(tmpCsvFile.c_str()); }
}
