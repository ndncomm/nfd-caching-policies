/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2015,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fw/strategy.hpp"
#include "dummy-strategy.hpp"
#include "tests/daemon/face/dummy-face.hpp"
#include <boost/range/adaptor/filtered.hpp>

#include "tests/test-common.hpp"

namespace nfd {
namespace fw {
namespace tests {

using namespace nfd::tests;

BOOST_FIXTURE_TEST_SUITE(FwStrategy, BaseFixture)

class FaceTableAccessTestStrategy : public DummyStrategy
{
public:
  explicit
  FaceTableAccessTestStrategy(Forwarder& forwarder)
    : DummyStrategy(forwarder, Name("ndn:/strategy"))
  {
    this->afterAddFace.connect([this] (shared_ptr<Face> face) {
      this->addedFaces.push_back(face->getId());
    });
    this->beforeRemoveFace.connect([this] (shared_ptr<Face> face) {
      this->removedFaces.push_back(face->getId());
    });
  }

  std::vector<FaceId>
  getLocalFaces()
  {
    auto enumerable = this->getFaceTable() |
                      boost::adaptors::filtered([] (shared_ptr<Face> face) {
                        return face->isLocal();
                      });

    std::vector<FaceId> results;
    for (shared_ptr<Face> face : enumerable) {
      results.push_back(face->getId());
    }
    return results;
  }

public:
  std::vector<FaceId> addedFaces;
  std::vector<FaceId> removedFaces;
};

BOOST_AUTO_TEST_CASE(FaceTableAccess)
{
  Forwarder forwarder;
  FaceTableAccessTestStrategy strategy(forwarder);

  auto face1 = make_shared<DummyFace>();
  auto face2 = make_shared<DummyLocalFace>();
  forwarder.addFace(face1);
  forwarder.addFace(face2);
  FaceId id1 = face1->getId();
  FaceId id2 = face2->getId();

  BOOST_CHECK(strategy.getLocalFaces() == std::vector<FaceId>{id2});

  face2->close();
  face1->close();

  BOOST_CHECK((strategy.addedFaces   == std::vector<FaceId>{id1, id2}));
  BOOST_CHECK((strategy.removedFaces == std::vector<FaceId>{id2, id1}));
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace tests
} // namespace fw
} // namespace nfd
