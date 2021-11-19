import codec.json as json
import curl as net

function get_wxacode(path, appid, secret, page, scene, is_hyaline)
    var access_token = null
    block
        var buff = new iostream.char_buff
        var session = net.make_session_os(buff.get_ostream())
        session.set_url("https://api.weixin.qq.com/cgi-bin/token?grant_type=client_credential&appid=" + appid + "&secret=" + secret)
        session.set_ssl_verify_host(false)
        session.set_ssl_verify_peer(false)
        if session.perform()
            access_token = json.to_var(json.from_string(buff.get_string())).access_token
        else
            return false
        end
    end
    block
        var post_fields = "{\"page\":\"" + page + "\",\"scene\":\"" + scene + "\",\"check_path\":true,\"width\":1280, \"is_hyaline\":" + (is_hyaline ? "true" : "false") + "}"
        var ofs = iostream.fstream(path, iostream.openmode.bin_out)
        if !ofs.good()
            return false
        end
        var session = net.make_session_os(ofs)
        session.set_url("https://api.weixin.qq.com/wxa/getwxacodeunlimit?access_token=" + access_token)
        session.set_http_post(true)
        session.set_http_post_fields(post_fields)
        session.set_ssl_verify_host(false)
        session.set_ssl_verify_peer(false)
        return session.perform()
    end
end

@begin
get_wxacode(
    # Path to the code
    "./wxacode.png",
    # AppID and AppSecret for getting AccessToken
    "",
    "",
    # Page
    "pages/index/index",
    # Scene(Arguments)
    "text=hello",
    # Is Hyaline(Transparency of Background)
    false
)
@end