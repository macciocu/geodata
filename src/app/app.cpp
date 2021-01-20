#include "Geo.h"

#include <iostream>
#include <string>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

namespace geo {

void normalize(const string &csvFile);

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
    cout << "TODO: DESCRIPTION" << endl;
    break;
  case GEO_CLEAN: {
    std::cout << csvFileIn << endl;
    cout << csvFileOut << endl;
    GeoDataCleaner geoDataCleaner = GeoDataCleaner();
    geoDataCleaner.clean(csvFileIn, csvFileOut);
    break;
  }
  }

  return rc;
}

} // namespace geo
