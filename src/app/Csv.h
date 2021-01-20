#pragma once

#include <fstream>
#include <vector>

namespace geo {

class CsvBase {
public:
  CsvBase(const std::string &csvFile, std::ios_base::openmode fileOpenMode,
          const char delimiter);
  virtual ~CsvBase() {}

protected:
  std::fstream m_fstream;
  const char m_delimiter;
};

class CsvReader : CsvBase {
public:
  ~CsvReader() override{};

  CsvReader(const std::string &csvFile, const char delimiter = ',');
  bool readNextRow(std::vector<std::string> &row);
};

class CsvWriter : CsvBase {
public:
  ~CsvWriter() override{};

  CsvWriter(const std::string &csvFile, const char delimiter = ',');
  void writeNextRow(const std::vector<std::string> &row);
};

} // namespace geo
