#include "Geo.h"

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

namespace geo {

int app(int argc, char *argv[]) {
  // return code
  int rc = 0;
  // Modes in which the program can be executed.
  enum Mode {
    UNKNOWN,
    HELP,
    GEO_CLEAN,
  };
  // Determined in function of given CLI args.
  Mode mode = UNKNOWN;
  // in/out *.csv filepath with journey data points.
  string csvFileIn, csvFileOut;
  // CLI parsing helper variables
  bool csvInAtNextCycle = false, csvOutAtNextCycle = false;

  // Skip the program name.
  argc--;
  argv++;

  // Parse CLI args.
  while (argc) {
    if (csvInAtNextCycle) {
      csvFileIn = string(*argv);
      csvInAtNextCycle = false;
    } else if (csvOutAtNextCycle) {
      csvFileOut = string(*argv);
      csvOutAtNextCycle = false;
    } else {
      if (strcmp(*argv, "-h") == 0) {
        mode = HELP;
        break;
      } else if (strcmp(*argv, "-i") == 0) {
        csvInAtNextCycle = true;
      } else if (strcmp(*argv, "-o") == 0) {
        csvOutAtNextCycle = true;
      }
    }
    argc--;
    argv++;
  }

  if (mode != HELP && csvFileIn.size() && csvFileOut.size())
    mode = GEO_CLEAN;

  switch (mode) {
  case UNKNOWN:
    rc = 1;
    cout << "[ERROR] Invalid CLI usage." << endl;
    cout << "Execute with \"-h\" to display help." << endl;
    break;
  case HELP:
    // clang-format off
    cout << "=================================================================" << endl
         << "DESCRIPTION:" << endl
         << "This CLI application cleans up a given *.csv dataset of" << endl
         << "car journey geo-location points. It outputs the cleaned "  << endl
         << "dataset to a new *.csv file." << endl
         << "-----------------------------------------------------------------" << endl
         << "USAGE:" << endl
         << "$ geodata -i './in.csv' -o './out.csv'" << endl
         << "-----------------------------------------------------------------" << endl
         << "KNOWN LIMITATIONS:" << endl
         << " - It is assumed that given data is sorted by ascending time." << endl
         << " - Current validation takes into account car speed and latitude / "<< endl
         << "   longitude boundaries. It does not take into account if a " << endl
         << "   given geo-location data-point is actually located on a road" << endl
         << "   (this would require access to either a roads geo-location " << endl
         << "    database, or by making use of an external service (e.g. Google's" << endl
         << "    GeoCoding API web service)." << endl
         << "-----------------------------------------------------------------" << endl
         << "FILE FORMAT:" << endl
         << "File I/O formats are *.csv, comma seperated (although the code can" << endl
         << "easily be adjusted to support other delimiters, see Csv.h)." << endl
         << "Each *.csv line is formatted as follows:" << endl
         << "<latitude_degrees>,<longitude_degrees>,<timestap_sec>" << endl
         << "=================================================================" << endl;
    // clang-format on
    break;
  case GEO_CLEAN: {
    GeoDataCleaner geoDataCleaner = GeoDataCleaner();
    geoDataCleaner.clean(csvFileIn, csvFileOut);
    break;
  }
  }

  return rc;
}

} // namespace geo
