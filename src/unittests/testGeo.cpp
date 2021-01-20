#include <catch2.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "app/Geo.h"

using namespace std;

TEST_CASE("GeoNode::distance") {
  const vector<pair<double, double>> latLong1 = {{51.49871943, -0.1601177991},
                                                 {80.0, 170.0}};
  const vector<pair<double, double>> latLong2 = {{51.49840586, -0.1604068824},
                                                 {51.49840586, -0.1604068824}};
  // test-set ref. values can be computed at:
  // https://www.movable-type.co.uk/scripts/latlong.html
  const vector<double> expectedDistanceInKm = {0.0402, 5380};
  // We allow some margin (0.1%) for detected (calculated) vs expected
  // (test-data reference) distance.
  const double marginRatio = 0.001;

  for (size_t i = 0; i < latLong1.size(); ++i) {
    geo::GeoNode node1, node2;
    node1.latitude = latLong1[i].first;
    node1.longitude = latLong1[i].second;
    node2.latitude = latLong2[i].first;
    node2.longitude = latLong2[i].second;
    double detectedDistanceInKm = node1.distance(node2);
    const double marginInKm = marginRatio * expectedDistanceInKm[i];
    REQUIRE(detectedDistanceInKm < expectedDistanceInKm[i] + marginInKm);
    REQUIRE(detectedDistanceInKm > expectedDistanceInKm[i] - marginInKm);
  }
}

TEST_CASE("GeoDataCleaner::clean") {
  const string tmpCsvFile = "../data/tmp.csv";

  SECTION("test") {
    // clang-format off
    const vector<string> csvTestFiles = {
        "../data/data_points.csv",
        "../data/test_detectSingleValidPair.css",
        "../data/test_detectZeroValidPair.css",
        "../data/test_detectNoMovement.css",
        "../data/test_detectInvalidCoord.css"};
    const vector<string> csvTestFilesClean = {
        "../data/data_points_clean.csv",
        "../data/test_detectSingleValidPair_clean.css",
        "../data/test_detectZeroValidPair_clean.css",
        "../data/test_detectNoMovement_clean.css",
        "../data/test_detectInvalidCoord_clean.css"};
    // clang-format on

    for (size_t i = 0; i < csvTestFiles.size(); ++i) {
      INFO("parametrization use-case: " + to_string(i + 1));
      geo::GeoDataCleaner gdc = geo::GeoDataCleaner();
      gdc.clean(csvTestFiles[i], tmpCsvFile);

      fstream fsExpected(csvTestFilesClean[i].c_str());
      fstream fsDetected(tmpCsvFile.c_str());
      int expLinesCount = 0, detLinesCount = 0, prevLinesCount = 0;

      do {
        prevLinesCount = expLinesCount;
        string expected, detected;
        if (getline(fsExpected, expected))
          ++expLinesCount;
        if (getline(fsDetected, detected))
          ++detLinesCount;
        if (expLinesCount != detLinesCount) {
          INFO("expLinesCount: " + to_string(expLinesCount));
          INFO("detLinesCount: " + to_string(detLinesCount));
          FAIL("expLinesCount != detLinesCount");
        }
        REQUIRE(expected == detected);
      } while (prevLinesCount < expLinesCount);
    }
  }

  SECTION("cleanup") { remove(tmpCsvFile.c_str()); }
}
