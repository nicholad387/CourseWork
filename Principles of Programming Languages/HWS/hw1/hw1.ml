(*
I pledge my honor that i have abided by the Steven's honor pledge
*)


(*
Encoding Instruction
0 Pen down
1 Pen up
2 Move North
3 Move East
4 Move South
5 Move West
*)

type program = int list

let square : program = [0; 2; 2; 3; 3; 4; 4; 5; 5; 1]
let letter_e : program = [0;2;2;3;3;5;5;4;3;5;4;3;3;5;5;1]



(*int list = [0; 4; 4; 5; 5; 3; 3; 2; 5; 3; 2; 5; 5; 3; 3; 1]*)

let mirror_image : int list -> int list = 
	List.map(fun x -> if(x<2)then x (*if its 0 or 1 then you dont change it*)
			else if(x<4) then (x+2) (*2 becomes 4 and 3 becomes 5(add two)*)
			else (x-2)) (*opsite is true for 4 and 5(minus 2)*)

(*int list = [0; 3; 3; 4; 4; 2; 2; 5; 4; 2; 5; 4; 4; 2; 2; 1]*)

let rotate_90_letter : int list -> int list =
	List.map(fun x -> if(x<2)then x (*check if 0||1 do nothing*)
					else if(x!=5) then (x+1)(*if not 5, add 1*)
					else (x-3))(*if 5 then make it 2*)
		
(*
int list list =
	 [[0; 3; 3; 4; 4; 2; 2; 5; 4; 2; 5; 4; 4; 2; 2; 1];
	 [0; 3; 3; 4; 4; 2; 2; 5; 4; 2; 5; 4; 4; 2; 2; 1]]
*)
	
let rotate_90_word : int list list -> int list list =
	List.map(fun l -> rotate_90_letter l) (*pass each list through rotate_90_letter*)
	
(*string list = ["hello"; "hello"; "hello"]*)
	
let rec repeat : int -> 'a -> 'a list =
	fun n x ->
	match n with
	| 0 -> []
	| m -> x :: repeat (m-1) x
	
(* 
int list =[0; 2; 2; 2; 2; 3; 3; 3; 3; 5; 5; 5; 5; 4; 4; 3; 3; 5; 5; 4; 4; 3; 3; 3; 3; 5; 5; 5; 5; 1]
*)

		
let helper : 'a -> 'a -> 'a list -> 'a list =
	fun x y lst ->
		let rec aux lst acc = 
			match lst with
			| [] -> List.rev acc
			| h::t when h = x || h = y ->
				if List.mem h acc then aux t acc else aux t (h::acc)
			| h::t -> aux t (h::acc)
		in aux lst []
	
(*pantograph 2 letter_e;; - : int list =	[0; 2; 2; 2; 2; 3; 3; 3; 3; 5; 5; 5; 5; 4; 4; 3; 3; 5; 5; 4; 4; 3; 3; 3; 3; 5; 5; 5; 5; 1]
*)
let rec pantograph : int -> int list -> int list =
	fun n p ->
		(helper 0 1 (List.flatten (List.map (fun x -> repeat n x) p)))
				
let rec pantograph_nm : int -> int list -> int list =
	fun n p ->
		match p with
		| [] -> []
		| h::t -> (helper 0 1 (repeat n h)) @ (pantograph_nm n t)
		
let pantograph_f : int -> int list -> int list =
	 fun n p ->
	List.fold_right (fun h acc -> (helper 0 1 (repeat n h)) @ acc) p []
	
(*
	coverage (0,0) letter_e;;	- : (int * int) list =
	[(0, 0); (0, 0); (0, 1); (0, 2); (1, 2); (2, 2); (1, 2); (0, 2); (0, 1);	(1, 1); (0, 1); (0, 0); (1, 0); (2, 0); (1, 0); (0, 0); (0, 0)]
*)
	
let rec coverage : int*int -> int list -> (int*int) list =
	fun (x, y) -> function
		| [] -> [(x, y)]
		| 0 :: t -> (x, y) :: coverage (x, y) t
		| 1 :: t -> (x, y) :: coverage (x, y) t
		| 2 :: t -> (x, y) :: coverage (x, y+1) t
		| 3 :: t -> (x, y) :: coverage (x+1, y) t
		| 4 :: t -> (x, y) :: coverage (x, y-1) t
		| 5 :: t -> (x, y) :: coverage (x-1, y) t
		| _ :: _ -> failwith "Unknown option"
		
(*
		coverage (0,0) letter_e;;		- : (int * int) list =
		[(0, 0); (0, 0); (0, 1); (0, 2); (1, 2); (2, 2); (1, 2); (0, 2); (0, 1);		(1, 1); (0, 1); (0, 0); (1, 0); (2, 0); (1, 0); (0, 0); (0, 0)]
*)
	
(*
	compress letter_e;;	- : (int * int) list =
	[(0, 1); (2, 2); (3, 2); (5, 2); (4, 1); (3, 1); (5, 1); (4, 1); (3, 2)	􏰀→ ;(5, 2); (1, 1)]
*)
	
let rec compress : int list -> (int*int) list =
	fun l ->
		let rec aux acc count = function
			| [] -> acc
			| [x] -> (x, count) :: acc
			| h1 :: (h2 :: _ as t) ->
				if h1 = h2 then aux acc (count + 1) t
				else aux ((h1, count) :: acc) 1 t
		in List.rev (aux [] 1 l)

(*
uncompress (compress letter_e);;
- : int list = [0; 2; 2; 3; 3; 5; 5; 4; 3; 5; 4; 3; 3; 5; 5; 1]
*)
	
let uncompress : (int * int) list -> int list =
	fun l ->
	let rec aux acc = function
		| [] -> List.rev acc
		| (m, n) :: tl -> aux (List.rev_append (List.init n (fun _ -> m)) acc) tl
	in aux [] l
	
let uncompress_f : (int * int) list -> int list =
	fun l ->
	List.fold_left (fun acc (m, n) -> acc @ (List.init n (fun _ -> m))) [] l
	
let uncompress_m : (int * int) list -> int list =
	fun l ->
	List.concat (List.map (fun (m, n) -> List.init n (fun _ -> m)) l)
	
(*
	# optimize [1];; - : int list = []	# optimize [1;1;1;1];; - : int list = []	# optimize [1;1;1;1;0];; - : int list = [0]	# optimize [1;1;1;1;0;1;0;1];; - : int list = [0; 1; 0; 1]	# optimize [1;1;1;1;0;1;0;1;1;1;1];; - : int list = [0; 1; 0; 1]	# optimize [0;1;0;1];;
	- : int list = [0; 1; 0; 1]	# optimize [2;3;4;5];;
	- : int list = [2; 3; 4; 5]
*)

let rec optimize : program -> program =
	fun l ->
	let rec helper s acc = function
		| [] -> List.rev acc
		| h::t when (h = 0 && s = 1) || (h = 1 && s = 0) || (h > 1 && h <= 5) ->
				helper h (h::acc) t
		| _::t -> helper s acc t
	in helper 1 [] l
	

		
		
		