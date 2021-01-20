#include "app/app.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <catch2.h>

using namespace std;

TEST_CASE("Invalid CLI usage: unknown argument") {
  int argc = 2;
  const char *argv[2] = {"app.cpp", "-x"};
  int rc = geo::app(argc, (char **)argv);
  REQUIRE(rc != 0);
}

TEST_CASE("Invalid CLI usage: missing file argument") {
  string arg = GENERATE(string("-i ifile"), string("-o ofile"));
  int argc = 2;
  const char *argv[2] = {"app.cpp", arg.c_str()};
  int rc = geo::app(argc, (char **)argv);
  REQUIRE(rc != 0);
}

TEST_CASE("Valid CLI argument: display help") {
  int argc = 2;
  const char *argv[2] = {"app.cpp", "-h"};
  int rc = geo::app(argc, (char **)argv);
  REQUIRE(rc == 0);
}

TEST_CASE("Invalid CLI usage: file i/o error") {
  vector<const char *> p1 = {"app.cpp", "-i", "invalid.csv", "-o",
                             "/tmp/valid.csv"};
  vector<const char *> p2 = {"app.cpp", "-i", "../data/data_points.csv", "-o",
                             "invalid_dir/x.csv"};

  vector<vector<const char *>> params = {p1, p2};
  vector<string> expectedErrorMessage = {
      "Failed to open invalid.csv in mode 8",
      "Failed to open invalid_dir/x.csv in mode 16"};

  int i = 0;
  for (auto p : params) {
    INFO("parametrization use-case: " + to_string(i + 1));

    int argc = p.size();
    const char **argv = p.data();
    string detectedErrorMessage;

    try {
      geo::app(argc, (char **)argv);
    } catch (const runtime_error &e) {
      detectedErrorMessage = e.what();
    }

    REQUIRE(detectedErrorMessage == expectedErrorMessage[i++]);
  }
}

// NB: This test case only validates one geo "clean data" use-case, simply to
// validate with our e2e that the application behaves correct from start to
// finish, to validate specific corner cases we use unit testing.
TEST_CASE("Valid CLI usage: clean data") {
  string tmpCsvOut = "../data/data_points_clean_temp.cvs";

  SECTION("test") {
    int argc = 5;
    string csvIn = "../data/data_points.csv";
    const char *argv[5] = {"app.cpp", "-i", csvIn.c_str(), "-o", tmpCsvOut.c_str()};

    int rc = geo::app(argc, (char **)argv);
    REQUIRE(rc == 0);

    fstream fsExpected("../data/data_points_clean.csv"), fsDetected(tmpCsvOut.c_str());
    int expLinesCount = 0, detLinesCount = 0, prevLinesCount = 0;

    do {
      prevLinesCount = expLinesCount;
      string expected, detected;
      if (getline(fsExpected, expected))
        ++expLinesCount;
      if (getline(fsDetected, detected))
        ++detLinesCount;
      if (expLinesCount != detLinesCount)
        FAIL("expLinesCount != detLinesCount");
      REQUIRE(expected == detected);
    } while (prevLinesCount < expLinesCount);
  }

  SECTION("cleanup") {
    remove(tmpCsvOut.c_str());
  }
}
