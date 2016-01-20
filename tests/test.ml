
open Iconv

let () =
	print_string "'test' in russian cp1251 charset: ";
	convert ~src:"utf-8" ~dst:"cp1251" "тест" |> print_endline
