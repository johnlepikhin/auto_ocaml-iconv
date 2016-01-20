
open Iconv

let () =
	print_string "'test' in russian cp1251 charset: ";
	convert "utf-8" "cp1251" "тест" |> print_endline
