#pragma once
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
#include <curl/curl.h>
#include <istream>
#include <ostream>
#include <cstring>
#include <string>

namespace curl {
	enum class ssl_level {
		none = CURLUSESSL_NONE,
		try_use = CURLUSESSL_TRY,
		control = CURLUSESSL_CONTROL,
		all = CURLUSESSL_ALL
	};
	class session final {
		CURL *sptr = nullptr;
		std::istream* is = nullptr;
		std::ostream* os = nullptr;

		static void global_initialize()
		{
			static bool global_initialized = false;
			if (!global_initialized) {
				curl_global_init(CURL_GLOBAL_DEFAULT);
				global_initialized = true;
			}
		}
		static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
		{
			return reinterpret_cast<std::istream*>(stream)->readsome((char*)ptr, size * nmemb);
		}
		static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream)
		{
			reinterpret_cast<std::ostream*>(stream)->write((char*)ptr, size * nmemb);
			return size * nmemb;
		}
	public:
		session() = delete;
		explicit session(std::iostream& ios) : is(&ios), os(&ios)
		{
			global_initialize();
			sptr = curl_easy_init();
			curl_easy_setopt(sptr, CURLOPT_READDATA, is);
			curl_easy_setopt(sptr, CURLOPT_READFUNCTION, &read_callback);
			curl_easy_setopt(sptr, CURLOPT_WRITEDATA, os);
			curl_easy_setopt(sptr, CURLOPT_WRITEFUNCTION, &write_callback);
		}
		session(std::istream& iss, std::ostream& oss) : is(&iss), os(&oss)
		{
			global_initialize();
			sptr = curl_easy_init();
			curl_easy_setopt(sptr, CURLOPT_READDATA, is);
			curl_easy_setopt(sptr, CURLOPT_READFUNCTION, &read_callback);
			curl_easy_setopt(sptr, CURLOPT_WRITEDATA, os);
			curl_easy_setopt(sptr, CURLOPT_WRITEFUNCTION, &write_callback);
		}
		explicit session(std::istream& iss) : is(&iss)
		{
			global_initialize();
			sptr = curl_easy_init();
			curl_easy_setopt(sptr, CURLOPT_READDATA, is);
			curl_easy_setopt(sptr, CURLOPT_READFUNCTION, &read_callback);
		}
		explicit session(std::ostream& oss) : os(&oss)
		{
			global_initialize();
			sptr = curl_easy_init();
			curl_easy_setopt(sptr, CURLOPT_WRITEDATA, os);
			curl_easy_setopt(sptr, CURLOPT_WRITEFUNCTION, &write_callback);
		}
		~session()
		{
			curl_easy_cleanup(sptr);
		}
		// Connection
		void set_url(const std::string &url)
		{
			curl_easy_setopt(sptr, CURLOPT_URL, url.c_str());
		}
		// HTTP
		void set_tcp_keep_alive(long probe)
		{
			curl_easy_setopt(sptr, CURLOPT_TCP_KEEPALIVE, probe);
		}
		void set_http_post(bool value)
		{
			curl_easy_setopt(sptr, CURLOPT_POST, value);
		}
		// Proxy
		void set_proxy(const std::string &url)
		{
			curl_easy_setopt(sptr, CURLOPT_PROXY, url.c_str());
		}
		// SSL
		void use_ssl(ssl_level level)
		{
			curl_easy_setopt(sptr, CURLOPT_USE_SSL, static_cast<long>(level));
		}
		void set_ssl_verify_host(bool val)
		{
			curl_easy_setopt(sptr, CURLOPT_SSL_VERIFYHOST, val);
		}
		void set_ssl_verify_peer(bool val)
		{
			curl_easy_setopt(sptr, CURLOPT_SSL_VERIFYPEER, val);
		}
		void set_ssl_cert(const std::string &path)
		{
			curl_easy_setopt(sptr, CURLOPT_SSLCERT, path.c_str());
		}
		void set_ssl_key(const std::string &path)
		{
			curl_easy_setopt(sptr, CURLOPT_SSLKEY, path.c_str());
		}
		void set_ssl_passwd(const std::string &path)
		{
			curl_easy_setopt(sptr, CURLOPT_KEYPASSWD, path.c_str());
		}
		// Timeout
		void set_connect_timeout(long timeout)
		{
			curl_easy_setopt(sptr, CURLOPT_CONNECTTIMEOUT, timeout);
		}
		void set_connect_timeout_ms(long timeout)
		{
			curl_easy_setopt(sptr, CURLOPT_CONNECTTIMEOUT_MS, timeout);
		}
		void set_accept_timeout_ms(long timeout)
		{
			curl_easy_setopt(sptr, CURLOPT_ACCEPTTIMEOUT_MS, timeout);
		}
		void set_transmit_timeout(long timeout)
		{
			curl_easy_setopt(sptr, CURLOPT_TIMEOUT, timeout);
		}
		void set_transmit_timeout_ms(long timeout)
		{
			curl_easy_setopt(sptr, CURLOPT_TIMEOUT_MS, timeout);
		}
		// APIs
		bool perform()
		{
			return curl_easy_perform(sptr) == CURLE_OK;
		}
	};
}