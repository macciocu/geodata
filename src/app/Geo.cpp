#include "Geo.h"
#include "Csv.h"

#include <cmath>
#include <limits>
#include <vector>

using namespace std;

namespace geo {

//
// GeoNode
//

double GeoNode::distance(const GeoNode &node) const {
  const double pi = 3.14159265358979323846;
  const double earthRadiusInKm = 6371;
  // convert current node lat/long to radians
  const double latt2 = this->latitude * pi / 180;
  const double long2 = this->longitude * pi / 180;
  // convert given (to be subtracted) node lat/long to radians
  const double latt1 = node.latitude * pi / 180;
  const double long1 = node.longitude * pi / 180;
  // distance between latitudes and longitudes
  const double dLatt = latt2 - latt1;
  const double dLong = long2 - long1;
  // apply havershine formula
  const double a =
      pow(sin(dLatt / 2), 2) + pow(sin(dLong / 2), 2) * cos(latt1) * cos(latt2);
  const double c = 2 * asin(sqrt(a));
  return earthRadiusInKm * c;
}

//
// GeoDataCleaner
//

GeoDataCleaner::GeoDataCleaner(const int maxSpeed) : m_maxSpeed(maxSpeed) {}

void GeoDataCleaner::clean(const string &csvFileIn, const string &csvFileOut) {
  CsvReader csvReader(csvFileIn);
  CsvWriter csvWriter(csvFileOut);

  GeoNode prevNode;
  prevNode.timestamp = numeric_limits<int>::min();
  std::vector<std::string> row;

  while (csvReader.getNextRow(row)) {
    if (row.size() != 3)
      continue;

    GeoNode node;
    node.latitude = stod(row[0]);
    node.longitude = stod(row[1]);
    node.timestamp = stoi(row[2]);
    if (!checkCoord(node))
      continue;

    if (prevNode.timestamp == numeric_limits<int>::min()) {
      csvWriter.writeRow(row);
      prevNode = node;
    } else if (checkSpeed(node, prevNode)) {
      csvWriter.writeRow(row);
      prevNode = node;
    }
  }
}

bool GeoDataCleaner::checkCoord(const GeoNode &node) const {
  return (node.latitude > -90 && node.latitude < 90 && node.longitude > -180 &&
          node.longitude < 180);
}

bool GeoDataCleaner::checkSpeed(const GeoNode &node,
                                const GeoNode &prevNode) const {
  double timeDeltaInHr = (double)(node.timestamp - prevNode.timestamp) / 3600;
  double distanceInKm = node.distance(prevNode);
  double speed = distanceInKm / timeDeltaInHr;
  return (speed >= 0 && speed <= m_maxSpeed);
}

} // namespace geo
