open ReM
open Dst
open Parser_plaf.Ast
open Parser_plaf.Parser
       
let rec chk_expr : expr -> texpr tea_result =
  fun e ->
  match e with
  | Int _n -> return IntType
  | Var id -> apply_tenv id
  | IsZero(e) ->
    chk_expr e >>= fun t ->
    if t=IntType
    then return BoolType
    else error "isZero: expected argument of type int"
  | Add(e1,e2) | Sub(e1,e2) | Mul(e1,e2)| Div(e1,e2) ->
    chk_expr e1 >>= fun t1 ->
    chk_expr e2 >>= fun t2 ->
    if (t1=IntType && t2=IntType)
    then return IntType
    else error "arith: arguments must be ints"
  | ITE(e1,e2,e3) ->
    chk_expr e1 >>= fun t1 ->
    chk_expr e2 >>= fun t2 ->
    chk_expr e3 >>= fun t3 ->
    if (t1=BoolType && t2=t3)
    then return t2
    else error "ITE: condition not boolean or types of then and else do not match"
  | Let(id,e,body) ->
    chk_expr e >>= fun t ->
    extend_tenv id t >>+
    chk_expr body
  | Proc(var,Some t1,e) ->
    extend_tenv var t1 >>+
    chk_expr e >>= fun t2 ->
    return @@ FuncType(t1,t2)
  | Proc(_var,None,_e) ->
    error "proc: type declaration missing"
  | App(e1,e2) ->
    chk_expr e1 >>=
    pair_of_funcType "app: " >>= fun (t1,t2) ->
    chk_expr e2 >>= fun t3 ->
    if t1=t3
    then return t2
    else error "app: type of argument incorrect"
  | Letrec([(_id,_param,None,_,_body)],_target) | Letrec([(_id,_param,_,None,_body)],_target) ->
    error "letrec: type declaration missing"
  | Letrec([(id,param,Some tParam,Some tRes,body)],target) ->
    extend_tenv id (FuncType(tParam,tRes)) >>+
    (extend_tenv param tParam >>+
     chk_expr body >>= fun t ->
     if t=tRes 
     then chk_expr target
     else error "LetRec: Type of recursive function does not match
declaration")
   | Pair(e1,e2) ->
    chk_expr e1 >>= fun t1 ->
    chk_expr e2 >>= fun t2 ->
    return @@ PairType(t1,t2)
  | Unpair(id1,id2,e1,e2) ->
    chk_expr e1 >>= fun t ->
    (match t with
     | PairType(t1,t2) ->
    extend_tenv id1 t1 >>+
    extend_tenv id2 t2 >>+
    chk_expr e2
     | _ -> error "unpair: expected a pair")
      
  (* EXPLICIT-REFS *)
  
  | BeginEnd([]) ->
    return UnitType
  | BeginEnd(es) ->
    chk_exprs es >>= fun ts ->
      return (List.hd (List.rev ts))
  | NewRef(e) ->
    chk_expr e >>= fun t -> 
      return (RefType t)
  | DeRef(e) ->
    chk_expr e >>= fun t ->
      (match t with
      | RefType t' -> return t'
      | _ -> error "deRef: expected a reference")
  | SetRef(e1,e2) ->
    chk_expr e1 >>= fun t1 ->
      chk_expr e2 >>= fun t2 ->
      (match t1 with
      | RefType t1' ->
        if t1' = t2
        then return UnitType
        else error "setRef: type of value does not match reference type"
      | _ -> error "setRef: expected a reference type")

  (* list *)
  | EmptyList(None) ->
    error ("EmptyList")
  | EmptyList(Some t) ->
    return @@ ListType(t)   
  | Cons(h, t) ->
    chk_expr h >>= fun l ->
    chk_expr t >>= fun g -> 
    (match g with 
      |ListType x ->             if l=x then return (ListType (x)) 
      else error ("cons: type of head and tail do not match")
      | _ -> error "expected ListType"
    )
  | IsEmpty(e) ->
    chk_expr e >>= fun l ->
      (match l with 
      |ListType(_) -> return @@ BoolType 
      |TreeType _ -> return BoolType
      |_ -> error "empty? : expected a list type") 
  | Hd(e) ->
    chk_expr e >>= fun t ->
      (match t with
      | ListType lt -> return lt
      | _ -> error "hd: expected a list")
  | Tl(e) ->
    chk_expr e >>= fun t ->
      (match t with
      | ListType _ -> return t
      | _ -> error "tl: expected a list")

  (* tree *)
  | EmptyTree(None) ->
    error "emptyTree: type annotation missing"
  | EmptyTree(Some t) ->
    return (TreeType t)
  | Node(de, le, re) ->
    chk_expr de >>= fun de_type ->
      chk_expr le >>= fun le_type ->
      chk_expr re >>= fun re_type ->
      (match (le_type, re_type) with
      | (TreeType lt, TreeType rt) when lt = rt && lt = de_type ->
        return (TreeType lt)
      | _ -> error "node: data and subtree types do not match or subtrees are not trees")
  | CaseT(target,emptycase,id1,id2,id3,nodecase) ->
    chk_expr target >>= fun target_type ->
      (match target_type with
      | TreeType t ->
        extend_tenv id1 t >>+
        extend_tenv id2 (TreeType t) >>+
        extend_tenv id3 (TreeType t) >>+
        chk_expr nodecase >>= fun node_case_type ->
        chk_expr emptycase >>= fun empty_case_type ->
        if node_case_type = empty_case_type
        then return node_case_type
        else error "caseT: empty and node case types do not match"
      | _ -> error "caseT: expected a tree")
  | Debug(_e) ->
    string_of_tenv >>= fun str ->
    print_endline str;
    error "Debug: reached breakpoint"
  | _ -> failwith "chk_expr: implement"
and
  chk_exprs =
  fun es ->
  match es with
  | [] -> return []
  | h::tl -> chk_expr h >>= fun t ->
    chk_exprs tl >>= fun ts ->
    return (t::ts)
and
  chk_prog (AProg(_,e)) =
  chk_expr e

(* Type-check an expression *)
let chk (e:string) : texpr result =
  let c = e |> parse |> chk_prog
  in run_teac c

let chkpp (e:string) : string result =
  let c = e |> parse |> chk_prog
  in run_teac (c >>= fun t -> return @@ string_of_texpr t)



