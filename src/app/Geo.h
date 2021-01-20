#pragma once

#include <string>

namespace geo {

/// Holds data for one node (data-point) along a journey path.
struct GeoNode {
  double latitude;  ///< Latitude coordinate (-90..90 degr).
  double longitude; ///< Longitude coordinate (-180..180 degr).
  int timestamp;    ///< Timestap at given coordinates measurement (sec).

  /// Computes the distance in km, from @a node according to the havershine
  /// formula, i.e. the great-circle distance between two points (ignoring any
  /// possible height differences, and assuming the earth is a perfect sphere.
  double distance(const GeoNode &node) const;
};

/// Cleans up car journey geo-location data.
class GeoDataCleaner {
public:
  /// @param maxSpeed Maximum speed (km/hr); A datapoint is considered invalid
  /// if the speed difference exceeds this value.
  GeoDataCleaner(const int maxSpeed = 300);
  /// Cleans up a given set of geo location data-points which are given in
  /// @a csvFileIn *.csv file, the cleaned up dataset is written to @a csvFileOut.
  void clean(const std::string &csvFileIn, const std::string &csvFileOut);

private:
  /// Maximum speed (km/hr) between 2 datapoints.
  const int m_maxSpeed;

  /// @return true if @a node contains valid latitutude / longitude values.
  bool checkCoord(const GeoNode &node) const;
  /// @return true if time delta between @a node and @a prevNode is possible
  /// given the configured `m_maxSpeed` value.
  bool checkSpeed(const GeoNode &node, const GeoNode &prevNode) const;
};

} // namespace geo
