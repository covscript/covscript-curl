import codec.json as json
import curl
var buff = new curl.buffer
var s = curl.make_session_os(buff.os())
s.set_url("http://csman.info/csman.json")
s.perform()
var info = json.to_var(json.from_string(buff.str()))
foreach it in info.Platform do system.out.println(it)