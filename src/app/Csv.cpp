#include "Csv.h"

#include <sstream>
#include <stdexcept>
#include <string>

#include <iostream>

using namespace std;

namespace geo {

//
// CsvBase
//

CsvBase::CsvBase(const std::string &csvFile,
                 std::ios_base::openmode fileOpenMode, const char delimiter)
    : m_delimiter(delimiter) {
  m_fstream.open(csvFile.c_str(), fileOpenMode);
  if (m_fstream.fail()) {
    stringstream errorMessage;
    errorMessage << "Failed to open " << csvFile << " in mode " << fileOpenMode;
    throw std::runtime_error(errorMessage.str());
  }
}

//
// CsvReader
//

CsvReader::CsvReader(const string &csvFile, const char delimiter)
    : CsvBase(csvFile, ios_base::in, delimiter) {}

bool CsvReader::readNextRow(std::vector<std::string> &row) {
  row.clear();
  string line;
  if (getline(m_fstream, line)) {
    string col;
    stringstream lineStream(line);
    while (getline(lineStream, col, m_delimiter))
      row.push_back(col);
    return true;
  }
  return false;
}

//
// CsvWriter
//

CsvWriter::CsvWriter(const string &csvFile, const char delimiter)
    : CsvBase(csvFile, ios_base::out, delimiter) {}

void CsvWriter::writeNextRow(const std::vector<std::string> &row) {
  for (auto it = row.begin(); it != row.end(); ++it) {
    m_fstream << *it;
    if (next(it) != row.end())
      m_fstream << m_delimiter;
  }
  m_fstream << endl;
}

} // namespace geo
