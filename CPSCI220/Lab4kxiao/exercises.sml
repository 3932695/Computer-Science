(* Kevin Xiao - Feb 20th 2014 - Lab4 *)
(* ---- ML exercises ---- *)

(* Exercise 1 *)
(* test for list membership *)
(* INPUT: member(20, [10, 20, 30]); *)
(* OUTPUT: true *)
fun member (x, nil) = false
  | member (x, h::t) = (x = h) orelse (member(x, t));



(* Exercise 2 *)
(* deleting all occurences of an element from a list *)
(* INPUT: unique([1, 2, 2, 4, 5, 5, 7]); *)
(* OUTPUT: [1, 2, 4, 5, 7] *)
fun delete (x, nil) = nil 
  | delete (x, h::t) = 
    if (x=h) then delete (x, t) else (h::(delete(x, t)));

(* remove duplicates from a list *)
fun unique (nil) = nil     	
  | unique (x::t) = (x::(unique (delete (x, t))));


(* Exercise 3 *)
(* inserts an element into a sorted list *)
(* INPUT: sortedListInsert(op<) 27[10, 20, 30]; *)
(* OUTPUT: [10, 20, 27, 30] *)
fun sortedListInsert (op o) x nil = [x]
  | sortedListInsert (op o) x (h::t) = 
    if x o h then x::(h::t)
    else h::(sortedListInsert (op o) x t);

(* Exercise 4 *)
(* returns boolean value associated with string in binding list *)
(* INPUT: lookup("A", [("A", true), ("B", false), ("C", false)]); *)
(* OUTPUT: true *)
fun lookup(string, nil) = false
  | lookup(string, (x, bool)::t) =
    if (string = x) then bool else lookup(string, t) 

(* Exercise 5 *)
(* returns all combinations of boolean and string bindings *)


fun interleave x [] = [[x]]
| interleave x (h::t) =
 (x::h::t)::(List.map(fn l => h::l) (interleave x t))

fun permute nil = [[]]
| permute (h::t) = List.concat( List.map (fn l => interleave h l) (permute t))
    


(* Exercise 6 *)
(* returns result of applying boolean function to boolean values *)
(* INPUT: boolEval(AND, true, false); *)
(* OUTPUT: false *)
fun boolEval(x, a, b) = x(a, b);

fun AND(a, b) = a andalso b;
fun OR(a, b) = a orelse b;
fun NOR(a, b) = not(a orelse b);
fun NAND(a, b) = not(a andalso b) ;
fun XOR(a, b) = (a orelse b) andalso not(a andalso b);
    
