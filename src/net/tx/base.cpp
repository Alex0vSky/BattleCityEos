#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/base.h"
namespace net::tx {
Base::Base(boost::asio::io_context *ioContext) :
	m_ioContextPtr( ioContext )
{}
} // namespace net::tx
