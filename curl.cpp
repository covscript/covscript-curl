/*
* Covariant Script cURL Bindings
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Copyright (C) 2017-2021 Michael Lee(李登淳)
*
* Email:   lee@covariant.cn, mikecovlee@163.com
* Github:  https://github.com/mikecovlee
* Website: http://covscript.org.cn
*/
#include "curl.hpp"

#include <covscript/dll.hpp>
#include <covscript/cni.hpp>
#include <sstream>

using session_t = std::shared_ptr<curl::session>;

namespace cs_impl {
	template<>
	struct type_conversion_cs<curl::session&> {
		using source_type=session_t;
	};

	template<>
	struct type_convertor<session_t, curl::session&> {
		static curl::session& convert(const session_t &s)
		{
			return *s;
		}
	};
}

CNI_ROOT_NAMESPACE {
	using namespace cs;

	session_t make_session_is(cs::istream& is)
	{
		return std::make_shared<curl::session>(*is);
	}

	CNI(make_session_is)

	session_t make_session_os(cs::ostream& os)
	{
		return std::make_shared<curl::session>(*os);
	}

	CNI(make_session_os)

	session_t make_session_ios(cs::istream& is, cs::ostream& os)
	{
		return std::make_shared<curl::session>(*is, *os);
	}

	CNI(make_session_ios)

	CNI_NAMESPACE(ssl_level)
	{
		CNI_VALUE(none,    curl::ssl_level::none)
		CNI_VALUE(try_use, curl::ssl_level::try_use)
		CNI_VALUE(control, curl::ssl_level::control)
		CNI_VALUE(all,     curl::ssl_level::all)
	}

	CNI_NAMESPACE(session)
	{
		CNI_V(set_url,                 &curl::session::set_url)
		CNI_V(set_tcp_keep_alive,      &curl::session::set_tcp_keep_alive)
		CNI_V(set_http_post,           &curl::session::set_http_post)
		CNI_V(set_proxy,               &curl::session::set_proxy)
		CNI_V(use_ssl,                 &curl::session::use_ssl)
		CNI_V(set_ssl_verify_host,     &curl::session::set_ssl_verify_host)
		CNI_V(set_ssl_verify_peer,     &curl::session::set_ssl_verify_peer)
		CNI_V(set_ssl_cert,            &curl::session::set_ssl_cert)
		CNI_V(set_ssl_key,             &curl::session::set_ssl_key)
		CNI_V(set_ssl_passwd,          &curl::session::set_ssl_passwd)
		CNI_V(set_timeout,             &curl::session::set_timeout)
		CNI_V(set_timeout_ms,          &curl::session::set_timeout_ms)
		CNI_V(set_connect_timeout,     &curl::session::set_connect_timeout)
		CNI_V(set_connect_timeout_ms,  &curl::session::set_connect_timeout_ms)
		CNI_V(set_accept_timeout_ms,   &curl::session::set_accept_timeout_ms)
		CNI_V(set_transmit_timeout,    &curl::session::set_transmit_timeout)
		CNI_V(set_transmit_timeout_ms, &curl::session::set_transmit_timeout_ms)
		CNI_V(set_low_speed_time,      &curl::session::set_low_speed_time)
		CNI_V(set_low_speed_limit,     &curl::session::set_low_speed_limit)
		CNI_V(perform,                 &curl::session::perform)
	}
}

CNI_ENABLE_TYPE_EXT_V(session, session_t, cs::curl::session)