/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#include "common.hpp"

#include "sec-public-info-memory.hpp"
#include "identity-certificate.hpp"

using namespace std;

namespace ndn {

SecPublicInfoMemory::~SecPublicInfoMemory()
{
}

bool
SecPublicInfoMemory::doesIdentityExist(const Name& identityName)
{
  string identityUri = identityName.toUri();
  return find(m_identityStore.begin(), m_identityStore.end(), identityUri) != m_identityStore.end();
}

void
SecPublicInfoMemory::addIdentity(const Name& identityName)
{
  string identityUri = identityName.toUri();
  if (find(m_identityStore.begin(), m_identityStore.end(), identityUri) != m_identityStore.end())
    return;

  m_identityStore.push_back(identityUri);
}

bool
SecPublicInfoMemory::revokeIdentity()
{
  throw Error("SecPublicInfoMemory::revokeIdentity not implemented");
}

bool
SecPublicInfoMemory::doesPublicKeyExist(const Name& keyName)
{
  return m_keyStore.find(keyName.toUri()) != m_keyStore.end();
}

void
SecPublicInfoMemory::addPublicKey(const Name& keyName, KeyType keyType, const PublicKey& publicKey)
{
  Name identityName = keyName.getPrefix(-1);

  addIdentity(identityName);

  m_keyStore[keyName.toUri()] = make_shared<KeyRecord>(keyType, boost::cref(publicKey));
}

shared_ptr<PublicKey>
SecPublicInfoMemory::getPublicKey(const Name& keyName)
{
  KeyStore::iterator record = m_keyStore.find(keyName.toUri());
  if (record == m_keyStore.end())
    throw Error("SecPublicInfoMemory::getPublicKey  " + keyName.toUri());

  return make_shared<PublicKey>(record->second->getKey());
}

bool
SecPublicInfoMemory::doesCertificateExist(const Name& certificateName)
{
  return m_certificateStore.find(certificateName.toUri()) != m_certificateStore.end();
}

void
SecPublicInfoMemory::addCertificate(const IdentityCertificate& certificate)
{
  const Name& certificateName = certificate.getName();
  const Name& keyName = certificate.getPublicKeyName();
  const Name& identity = keyName.getPrefix(-1);

  addIdentity(identity);
  addPublicKey(keyName, KEY_TYPE_RSA, certificate.getPublicKeyInfo());
  m_certificateStore[certificateName.toUri()] = make_shared<IdentityCertificate>(certificate);
}

shared_ptr<IdentityCertificate>
SecPublicInfoMemory::getCertificate(const Name& certificateName)
{
  CertificateStore::iterator record = m_certificateStore.find(certificateName.toUri());
  if (record == m_certificateStore.end())
    throw Error("SecPublicInfoMemory::getCertificate  " + certificateName.toUri());

  return record->second;
}

Name
SecPublicInfoMemory::getDefaultIdentity()
{
  return Name(m_defaultIdentity);
}

void
SecPublicInfoMemory::setDefaultIdentityInternal(const Name& identityName)
{
  string identityUri = identityName.toUri();
  if (find(m_identityStore.begin(), m_identityStore.end(), identityUri) != m_identityStore.end())
    m_defaultIdentity = identityUri;
  else
    // The identity doesn't exist, so clear the default.
    m_defaultIdentity.clear();
}

Name
SecPublicInfoMemory::getDefaultKeyNameForIdentity(const Name& identityName)
{
  return m_defaultKeyName;
}

void
SecPublicInfoMemory::setDefaultKeyNameForIdentityInternal(const Name& keyName)
{
  m_defaultKeyName = keyName;
}

Name
SecPublicInfoMemory::getDefaultCertificateNameForKey(const Name& keyName)
{
  return m_defaultCert;
}

void
SecPublicInfoMemory::setDefaultCertificateNameForKeyInternal(const Name& certificateName)
{
  m_defaultCert = certificateName;
}

void
SecPublicInfoMemory::getAllIdentities(std::vector<Name>& nameList, bool isDefault)
{
  throw Error("SecPublicInfoMemory::getAllIdentities not implemented");
}

void
SecPublicInfoMemory::getAllKeyNames(std::vector<Name>& nameList, bool isDefault)
{
  throw Error("SecPublicInfoMemory::getAllKeyNames not implemented");
}

void
SecPublicInfoMemory::getAllKeyNamesOfIdentity(const Name& identity,
                                              std::vector<Name>& nameList,
                                              bool isDefault)
{
  throw Error("SecPublicInfoMemory::getAllKeyNamesOfIdentity not implemented");
}

void
SecPublicInfoMemory::getAllCertificateNames(std::vector<Name>& nameList, bool isDefault)
{
  throw Error("SecPublicInfoMemory::getAllCertificateNames not implemented");
}

void
SecPublicInfoMemory::getAllCertificateNamesOfKey(const Name& keyName,
                                                 std::vector<Name>& nameList,
                                                 bool isDefault)
{
  throw Error("SecPublicInfoMemory::getAllCertificateNamesOfKey not implemented");
}

void
SecPublicInfoMemory::deleteCertificateInfo(const Name& certName)
{
  throw Error("SecPublicInfoMemory::deleteCertificateInfo not implemented");
}

void
SecPublicInfoMemory::deletePublicKeyInfo(const Name& keyName)
{
  throw Error("SecPublicInfoMemory::deletePublicKeyInfo not implemented");
}

void
SecPublicInfoMemory::deleteIdentityInfo(const Name& identityName)
{
  throw Error("SecPublicInfoMemory::deleteIdentityInfo not implemented");
}

} // namespace ndn
