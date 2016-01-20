
exception Error of string

external convert: string -> string -> string -> string = "stub_iconv_convert"

let _ = Callback.register_exception "iconv_exn" (Error "")
