// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef THIRD_PARTY_STREETLEARN_METADATA_CACHE_H_
#define THIRD_PARTY_STREETLEARN_METADATA_CACHE_H_

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "streetlearn/engine/dataset.h"
#include "streetlearn/proto/streetlearn.pb.h"

namespace streetlearn {

// Metadata for an individual pano.
struct PanoMetadata {
  // The neighbors of the pano.
  std::vector<PanoIdAndGpsCoords> neighbors;

  // Metadata for the pano.
  Pano pano;

  // Depth of the connected graph.
  int graph_depth;
};

// Reads and caches metadata and pano connectivity information for a region.
// This data is provided by a panos_connectivity file generated by the pano
// download process.
class MetadataCache {
 public:
  // Create an instance of the cache using the dataset provided. Graphs below
  // the minimum depth will be excluded. Returns null if the metadata file is
  // invalid.
  static std::unique_ptr<MetadataCache> Create(const Dataset* dataset,
                                               int min_graph_depth);

  // Limits of the region.
  double min_lat() const { return min_lat_; }
  double max_lat() const { return max_lat_; }
  double min_lng() const { return min_lng_; }
  double max_lng() const { return max_lng_; }

  // Total number of panos in the region.
  std::size_t size() const { return pano_metadata_.size(); }

  // Returns the metadata for the given pano or null if it doesn't exist. The
  // object returned is only valid for the lifetime of the cache.
  const PanoMetadata* GetPanoMetadata(const std::string& pano_id) const;

  // Returns all panos in graphs of at least min_size.
  std::vector<std::string> PanosInGraphsOfSize(int min_size) const;

  // Returns a pano in the largest connected graph in the region.
  std::string PanoInLargestGraph() const;

 private:
  explicit MetadataCache(int min_graph_depth);

  // Reads metadata from the dataset provided, which must contain a
  // StreetLearnGraph proto and populates self. Returns false for non-existent
  // or invalid files.
  bool ReadData(const Dataset* dataset);

  // Add neighbor information to the metadata cache.
  void ProcessNeighbors(const StreetLearnGraph& streetLearnGraph,
                        const std::map<std::string, Pano>& panos);

  // Minimum lat/long of the region's bounds.
  double min_lat_;
  double min_lng_;

  // Maximum lat/long of the region's bounds.
  double max_lat_;
  double max_lng_;

  // Lookup of metadata indexed on pano ID.
  std::map<std::string, PanoMetadata> pano_metadata_;

  // The minimum graph depth loaded.
  int min_graph_depth_;
};

}  // namespace streetlearn

#endif  // STREETLEARN_METADATA_CACHE_H_
