// -*- lsst-c++ -*-
#ifndef LSST_DAF_BASE_DATETIME_H
#define LSST_DAF_BASE_DATETIME_H

/** @file
  * @ingroup daf_base
  *
  * @brief Interface for DateTime class
  *
  * @author Kian-Tat Lim (ktl@slac.stanford.edu)
  * @version $Revision$
  * @date $Date$
  */

/** @class lsst::daf::base::DateTime
  * @brief Class for handling dates/times, including MJD, UTC, and TAI.
  *
  * Representation must be a 64-bit integer giving time in nanoseconds to
  * remain compatible with CORAL/SEAL.  Methods may convert to any other time
  * desired.
  *
  * Application must keep track of the time system and timezone, so this is
  * most useful for output to databases.
  *
  * @ingroup daf_base
  */

#include <ctime>
#include <sys/time.h>

// Forward declaration of the boost::serialization::access class.
namespace boost {
namespace serialization {
    class access;
}} // namespace boost::serialization

namespace lsst {
namespace daf {
namespace base {

class DateTime {
public:
    explicit DateTime(long long nsecs = 0LL); // Could be UTC, TAI, local
    explicit DateTime(double mjd); // Converts to UTC

    long long nsecs(void) const;
    DateTime utc2tai(void) const;
    DateTime tai2utc(void) const;
    double utc2mjd(void) const;
    double tai2mjd(void) const;
    struct tm utc2gmtime(void) const;
    struct timespec timespec(void) const;
    struct timeval timeval(void) const;

    friend class boost::serialization::access;
    /** Serialize DateTime to/from a Boost archive.
      * @param[in,out] ar   Archive to access.
      * @param[in] version  Version of class serializer.
      */
    template <class Archive> void serialize(Archive ar, int const version) {
        ar & _nsecs;
    };

private:
    long long _nsecs;
        ///< Nanoseconds since Unix epoch, but zone/scale are unspecified.
};

}}} // namespace lsst::daf::base

#endif