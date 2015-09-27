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

#ifndef NFD_DAEMON_FACE_FACE_HPP
#define NFD_DAEMON_FACE_FACE_HPP

#include "common.hpp"
#include "core/logger.hpp"
#include "face-counters.hpp"

#include <ndn-cxx/management/nfd-face-status.hpp>

namespace nfd {

/** \class FaceId
 *  \brief identifies a face
 */
typedef int FaceId;

/// indicates an invalid FaceId
const FaceId INVALID_FACEID = -1;

/// identifies the InternalFace used in management
const FaceId FACEID_INTERNAL_FACE = 1;
/// identifies a packet comes from the ContentStore, in LocalControlHeader incomingFaceId
const FaceId FACEID_CONTENT_STORE = 254;
/// identifies the NullFace that drops every packet
const FaceId FACEID_NULL = 255;
/// upper bound of reserved FaceIds
const FaceId FACEID_RESERVED_MAX = 255;


/** \brief represents a face
 */
class Face : noncopyable, public enable_shared_from_this<Face>
{
public:
  /**
   * \brief Face-related error
   */
  class Error : public std::runtime_error
  {
  public:
    explicit
    Error(const std::string& what)
      : std::runtime_error(what)
    {
    }
  };

  Face(const FaceUri& remoteUri, const FaceUri& localUri,
       bool isLocal = false, bool isMultiAccess = false);

  virtual
  ~Face();

  /// fires when an Interest is received
  signal::Signal<Face, Interest> onReceiveInterest;

  /// fires when a Data is received
  signal::Signal<Face, Data> onReceiveData;

  /// fires when an Interest is sent out
  signal::Signal<Face, Interest> onSendInterest;

  /// fires when a Data is sent out
  signal::Signal<Face, Data> onSendData;

  /// fires when face disconnects or fails to perform properly
  signal::Signal<Face, std::string/*reason*/> onFail;

  /// send an Interest
  virtual void
  sendInterest(const Interest& interest) = 0;

  /// send a Data
  virtual void
  sendData(const Data& data) = 0;

  /** \brief Close the face
   *
   *  This terminates all communication on the face and cause
   *  onFail() method event to be invoked
   */
  virtual void
  close() = 0;

public: // attributes
  FaceId
  getId() const;

  /** \brief Get the description
   */
  const std::string&
  getDescription() const;

  /** \brief Set the face description
   *
   *  This is typically invoked by management on set description command
   */
  void
  setDescription(const std::string& description);

  void
  setMetric(uint64_t metric);

  uint64_t
  getMetric() const;

  /** \brief Get whether face is connected to a local app
   */
  bool
  isLocal() const;

  /** \brief Get the persistency setting
   */
  ndn::nfd::FacePersistency
  getPersistency() const;

  /** \brief Get whether packets sent by this face may reach multiple peers
   */
  bool
  isMultiAccess() const;

  /** \brief Get whether underlying communication is up
   *
   *  In this base class this property is always true.
   */
  virtual bool
  isUp() const;

  const FaceCounters&
  getCounters() const;

  /** \return a FaceUri that represents the remote endpoint
   */
  const FaceUri&
  getRemoteUri() const;

  /** \return a FaceUri that represents the local endpoint (NFD side)
   */
  const FaceUri&
  getLocalUri() const;

  /** \return FaceTraits data structure filled with the current FaceTraits status
   */
  template<typename FaceTraits>
  void
  copyStatusTo(FaceTraits& traits) const;

  /** \return FaceStatus data structure filled with the current Face status
   */
  virtual ndn::nfd::FaceStatus
  getFaceStatus() const;

PUBLIC_WITH_TESTS_ELSE_PROTECTED:
  void
  setPersistency(ndn::nfd::FacePersistency persistency);

protected:
  bool
  decodeAndDispatchInput(const Block& element);

  /** \brief fail the face and raise onFail event if it's UP; otherwise do nothing
   */
  void
  fail(const std::string& reason);

  FaceCounters&
  getMutableCounters();

  DECLARE_SIGNAL_EMIT(onReceiveInterest)
  DECLARE_SIGNAL_EMIT(onReceiveData)
  DECLARE_SIGNAL_EMIT(onSendInterest)
  DECLARE_SIGNAL_EMIT(onSendData)

private:
  // this method should be used only by the FaceTable
  void
  setId(FaceId faceId);

private:
  FaceId m_id;
  std::string m_description;
  FaceCounters m_counters;
  const FaceUri m_remoteUri;
  const FaceUri m_localUri;
  const bool m_isLocal;
  ndn::nfd::FacePersistency m_persistency;
  const bool m_isMultiAccess;
  bool m_isFailed;
  uint64_t m_metric;

  // allow setting FaceId
  friend class FaceTable;
};

inline FaceId
Face::getId() const
{
  return m_id;
}

inline void
Face::setId(FaceId faceId)
{
  m_id = faceId;
}

inline const std::string&
Face::getDescription() const
{
  return m_description;
}

inline void
Face::setDescription(const std::string& description)
{
  m_description = description;
}

inline bool
Face::isLocal() const
{
  return m_isLocal;
}

inline ndn::nfd::FacePersistency
Face::getPersistency() const
{
  return m_persistency;
}

inline void
Face::setPersistency(ndn::nfd::FacePersistency persistency)
{
  m_persistency = persistency;
}

inline bool
Face::isMultiAccess() const
{
  return m_isMultiAccess;
}

inline const FaceCounters&
Face::getCounters() const
{
  return m_counters;
}

inline FaceCounters&
Face::getMutableCounters()
{
  return m_counters;
}

inline const FaceUri&
Face::getRemoteUri() const
{
  return m_remoteUri;
}

inline const FaceUri&
Face::getLocalUri() const
{
  return m_localUri;
}


/** \defgroup FaceLogging Face logging macros
 *
 * These macros augment the log message with some face-specific information,
 * such as the face ID, that are useful to distinguish which face produced the
 * message. It is strongly recommended to use these macros instead of the
 * generic ones for all logging inside Face subclasses.
 * @{
 */

inline void
Face::setMetric(uint64_t metric)
{
  m_metric = metric;
}

inline uint64_t
Face::getMetric() const
{
  return m_metric;
}

#define NFD_LOG_FACE(level, msg)                        \
  NFD_LOG_##level("[id=" << this->getId() <<            \
                  ",local=" << this->getLocalUri() <<   \
                  ",remote=" << this->getRemoteUri() << \
                  "] " << msg)

/** \brief Log a message at TRACE level */
#define NFD_LOG_FACE_TRACE(msg) NFD_LOG_FACE(TRACE, msg)

/** \brief Log a message at DEBUG level */
#define NFD_LOG_FACE_DEBUG(msg) NFD_LOG_FACE(DEBUG, msg)

/** \brief Log a message at INFO level */
#define NFD_LOG_FACE_INFO(msg)  NFD_LOG_FACE(INFO,  msg)

/** \brief Log a message at WARN level */
#define NFD_LOG_FACE_WARN(msg)  NFD_LOG_FACE(WARN,  msg)

/** \brief Log a message at ERROR level */
#define NFD_LOG_FACE_ERROR(msg) NFD_LOG_FACE(ERROR, msg)

/** @} */

} // namespace nfd

#endif // NFD_DAEMON_FACE_FACE_HPP
