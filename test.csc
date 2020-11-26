import codec.json as json
import curl

function get_json(url)
    var buff = new curl.buffer
    var s = curl.make_session_os(buff.os())
    s.set_url(url)
    if !s.perform()
        throw runtime.exception("get_json: failed")
    end
    return json.to_var(json.from_string(buff.str()))
end

var source = "http://csman.info/"

var csman_info = get_json(source + "csman.json")
system.out.println("CSMAN Source Version: " + csman_info.Version)
system.out.println("CSMAN Source BaseUrl: " + csman_info.BaseUrl)
var info_generic = get_json(csman_info.BaseUrl + "Generic.json")
var info_platform = null
if system.is_platform_windows()
    info_platform = get_json(csman_info.BaseUrl + "Win32_MinGW-w64_AMD64.json")
end
if system.is_platform_linux()
    info_platform = get_json(csman_info.BaseUrl + "Linux_GCC_AMD64.json")
end
if system.is_platform_darwin()
    info_platform = get_json(csman_info.BaseUrl + "macOS_clang_AMD64.json")
end
foreach it in info_platform
    if info_generic.exist(it.first)
        foreach pac in it.second
            info_generic[it.first].insert(pac.first, pac.second)
        end
    else
        info_generic.insert(it.first, it.second)
    end
end
var out = iostream.fstream("./sources.json", iostream.openmode.out)
out.print(json.to_string(json.from_var(info_generic)))
system.out.println("CSMAN Source Updated: " + runtime.get_current_dir() + system.path.separator + "source.json")