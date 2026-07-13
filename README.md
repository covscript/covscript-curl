# covscript-curl

cURL bindings for Covariant Script — HTTP/HTTPS client with full SSL support.

## Dependencies

- [Covariant Script](https://github.com/covscript/covscript)
- libcurl (system package)

## Build

```bash
# Ubuntu
sudo apt install libcurl4-openssl-dev

# macOS
brew install curl

# Then build
mkdir build && cd build
cmake ..
cmake --build .
```

## API

### ssl_level

| Constant | Description |
|----------|-------------|
| `none` | No SSL |
| `try_use` | Try SSL, fall back to plain |
| `control` | Require SSL, verify if possible |
| `all` | Require SSL with full verification |

### session

| Method | Description |
|--------|-------------|
| `set_url(url)` | Set request URL |
| `allow_redirect(bool)` | Enable/disable redirect following |
| `set_tcp_keep_alive(bool)` | Enable TCP keep-alive |
| `set_http_post(bool)` | Set POST method |
| `set_http_post_fields(data)` | Set POST body |
| `set_proxy(url)` | Set HTTP proxy |
| `use_ssl(level)` | Set SSL verification level |
| `set_ssl_verify_host(bool)` | Verify SSL hostname |
| `set_ssl_verify_peer(bool)` | Verify SSL peer certificate |
| `set_ssl_cert(path)` | Set client certificate |
| `set_ssl_key(path)` | Set client private key |
| `set_ssl_passwd(password)` | Set SSL password |
| `set_timeout(ms)` | Set request timeout in milliseconds |
| `perform()` | Execute the request |

## License

Apache License 2.0 — see [LICENSE](./LICENSE)
