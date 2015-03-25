(* Kevin Xiao - Feb 25th 2014 - Lab5 *)
(* ---- More ML ---- *)
(* This lab includes exercises/functions from Lab4 *)
(* This lab was finished with the help of Shirley, Harry, Ryan and Ben *)

datatype BoolExp = 
INPUT of string
| UnaryBE of (bool -> bool) * BoolExp
| BinaryBE of (bool * bool -> bool) * BoolExp * BoolExp;

type bindingList = (string * bool) list;
type TruthTable = (bindingList * bool) list;

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

(* Exercise 4 *)
(* returns boolean value associated with string in binding list *)
(* INPUT: lookup("A", [("A", true), ("B", false), ("C", false)]); *)
(* OUTPUT: true *)
fun lookup(string, nil) = false
  | lookup(string, (x, bool)::t) =
    if (string = x) then bool else lookup(string, t) 

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
fun NOT(a) = not(a);

(*STU'S ALLBOOLEANCOMBOS *)
fun splitList([]) = ([],[])
  | splitList([x]) = ([x], []) 
  | splitList(a::b::rest) = 
    let 
        val (listA, listB) = splitList(rest);
    in
        (a::listA, b::listB)
    end;

fun merge(cmp, [], x) = x
  | merge(cmp, x, []) = x
  | merge(cmp, xs as x::xrest, ys as y::yrest) =
    if cmp(x, y) then x::merge(cmp, xrest, ys)
    else y::merge(cmp, xs, yrest);

fun sort cmp [] = []
  | sort cmp [a] = [a]
  | sort cmp lst =
    let 
        val (halfA, halfB) = splitList(lst);
        val sortedA = sort cmp halfA;
        val sortedB = sort cmp halfB;
    in
        merge(cmp, sortedA, sortedB)
    end;

fun sortStr lst = sort (fn (x, y:string) => x < y) lst;

fun consAll (value, []) = []
  | consAll (value, x::xs) = (value::x)::consAll(value, xs);

fun allInputCombosHelper([]) = [[]:bindingList]
| allInputCombosHelper([name]) = [[(name, false)], [(name, true)]]
| allInputCombosHelper(name::names) = 
  let
      val restCombos = allInputCombosHelper(names);
  in
      consAll ((name, false), restCombos) @ consAll((name, true), restCombos)
  end;

fun allInputCombos(lst) =
    allInputCombosHelper(sortStr(lst));

(* MyEval() evaluates boolean expression with values in bindingList *)
fun myEval(INPUT(x), bl:bindingList) = lookup(x:string, bl:bindingList)
| myEval(UnaryBE(f, x), bl:bindingList) = f(myEval(x, bl:bindingList))
| myEval(BinaryBE(f, x, y), bl:bindingList) = 
  f(myEval(x, bl:bindingList), myEval(y, bl:bindingList));

(* equivalent() checks whether two boolean expressions are equal *)
fun listVar(INPUT(x)) = [x]
| listVar(UnaryBE(f, x)) = listVar(x)
| listVar(BinaryBE(f, x, y)) = listVar(x)@listVar(y);

(* printBool() prints booleans as strings *)
fun printBool(b) = 
 if b then "1" else "0";

(* printBools() helps printTable() *)
fun printBools(nil) = ""
| printBools((str, b:bool)::t) = printBool(b) ^ "  " ^ printBools(t);

(* printVars() executed before printTable(), handles top of table *)
fun printVars(nil) = ""
| printVars((str, b:bool)::t) = str ^ "  " ^ printVars(t);

(* printTable() prints out all counterexamples *)
fun printTable(x, y, nil) = ""
| printTable(x, y, h::t) =
  if myEval(x, h) = myEval(y, h) then printTable(x, y, t)
  else printBools(h) ^ "| " ^ printBool(myEval(x, h)) ^ "   | " ^ printBool(myEval(y, h)) ^"\n" ^ printTable(x, y, t);

(* tst() helps equivalent() explore all boolean combos to test equivalence *)
fun tst(x, y, nil) = (true, print( "The circuits are equivalent\n"))
| tst(x, y, h::t) =
  if myEval(x, h) = myEval(y, h) then tst(x, y, t)
  else (false, print( "The circuits are not equivalent\nHere are the counterexamples:\n" ^ printVars(h) ^ "| fn1 | fn2  \n" ^ printTable(x, y, h::t)));



(* equivalent() test whether two boolean expressions are equivalent *)
fun equivalent(x, y) = tst(x, y, allInputCombos(unique(listVar(x)@listVar(y))));


(* sample queries *)
val be1 = BinaryBE (AND, INPUT("A"), INPUT("B"));
val be2 = UnaryBE (NOT, be1);
myEval(be2, [("A", true), ("B", false)]);
val be3 = UnaryBE (NOT, INPUT("A"));
val be4 = UnaryBE (NOT, INPUT("B"));
val be5 = BinaryBE(OR, be3, be4);
equivalent(be2, be5);
equivalent(be1, be5);
