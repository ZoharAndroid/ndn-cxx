/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Yingdi Yu <yingdi@cs.ucla.edu>
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#ifndef NDN_SECURITY_VALIDATOR_NULL_HPP
#define NDN_SECURITY_VALIDATOR_NULL_HPP

#include "validator.hpp"

namespace ndn {

class ValidatorNull : public Validator {
public:
  virtual
  ~ValidatorNull()
  {
  }

protected:
  virtual void
  checkPolicy(const Data& data,
              int nSteps,
              const OnDataValidated& onValidated,
              const OnDataValidationFailed& onValidationFailed,
              std::vector<shared_ptr<ValidationRequest> >& nextSteps)
  {
    onValidated(data.shared_from_this());
  }

  virtual void
  checkPolicy(const Interest& interest,
              int nSteps,
              const OnInterestValidated& onValidated,
              const OnInterestValidationFailed& onValidationFailed,
              std::vector<shared_ptr<ValidationRequest> >& nextSteps)
  {
    onValidated(interest.shared_from_this());
  }
};

} // namespace ndn

#endif //NDN_SECURITY_VALIDATOR_NULL_HPP
