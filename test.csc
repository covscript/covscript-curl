import codec.json as json
import curl

function get_json(url)
    var buff = new iostream.char_buff
    var s = curl.make_session_os(buff.get_ostream())
    s.set_url(url)
    if !s.perform()
        throw runtime.exception("get_json: failed")
    end
    return json.to_var(json.from_string(buff.get_string()))
end

var source = "http://mirrors.covariant.cn/cspkg/"

var cspkg_info = get_json(source + "index.json")
system.out.println("CSPKG Source BaseUrl: " + cspkg_info.base_url)
var universal_info = get_json(cspkg_info.base_url + cspkg_info.universal)
foreach it in universal_info
    system.out.println(it.first)
end
