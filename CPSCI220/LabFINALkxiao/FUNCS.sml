(* Stu's FUNCTION Defs Demo *)


(* SEE "FUNCS.txt" FOR COMMENTS ON OUTPUT *)

(* Let "AND(x, y)" be a function that accepts variables 'x' and 'y', *)
(* and returns the result of "x andalso y". *)
fun AND(x,y) = x andalso y;


(* Same as above, with different formatting. AND must use brackets, *)
(* ANDc does not use brackets. This is advantageous if you need to *)
(* treat the function and its variables as separate tokens. *)
fun ANDc x y = x andalso y;

(* Same as AND, a more primitive way to create a function. AND is a shortcut *)
val andF = fn (x, y) => x andalso y;


(* Calls function "AND" with 'x=true' and 'y=false' *)
AND(true,false);

(* Calls function "ANDc" with 'x=true' and 'y=false' *)
ANDc true false;

(* Assigns "andCtrue" the value of "ANDc true"; this is the same as calling *)
(* "ANDc" with the assumption that 'x=true'*)
val andCtrue = ANDc true;

(* andCtrue in action; you can read this as "ANDc true false" *)
andCtrue false;

(* andCtrue in action; you can read this as "ANDc true true" *)
andCtrue true;


