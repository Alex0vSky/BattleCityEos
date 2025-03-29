#pragma once // src\net\xerialization.h - to make compilation easier // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/type.h"
// basic: template <typename T> T* deserialize(cista::byte_buf const&);

cista::byte_buf serialize_(detail::Level const&);
void deserialize_(cista::byte_buf const&, detail::Level *);

namespace net { class NetPlayer; } // namespace net _
cista::byte_buf serialize_(net::NetPlayer const&);
void deserialize_(cista::byte_buf const&, net::NetPlayer *);

namespace net::tx { class Eventer; } // namespace net::tx _
cista::byte_buf serialize_(net::tx::Eventer::EventData::Shot const&);
void deserialize_(cista::byte_buf const&, net::tx::Eventer::EventData::Shot *);
cista::byte_buf serialize_(net::tx::Eventer::EventData::Movement const&);
void deserialize_(cista::byte_buf const&, net::tx::Eventer::EventData::Movement *);
