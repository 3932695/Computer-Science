;; Lab 7 - Kevin Xiao
;; I don't think I was ready for this lab. I could barely get basic arithmetic expressions working even when working with a reference. Am I the only one who feels this way?

(define (mc-eval exp env)
  (cond ((self-evaluating? exp) (eval-self-evaluating exp))
	((variable? exp) (eval-variable exp env))
	((quoted? exp) (eval-quotation exp))
	((assignment? exp) (eval-assignment exp env))
	((definition? exp) (eval-definition exp env))
	((if? exp) (eval-if exp env))
	((lambda? exp) (eval-lambda exp env))
	((begin? exp) (eval-begin exp env))
	((cond? exp) (eval-cond exp env))
	((application? exp) (eval-application exp env))
	(else (error "Unknown expression type -- EVAL" exp))))

(define true #T)
(define false #F)

(define (mc-number? exp) (number? exp))
(define (mc-boolean? exp) (or (eq? exp true) (eq? exp false)))
(define (mc-string? exp) (string? exp))

(define (self-evaluating? exp)
  (cond ((mc-number? exp) #T) ; Numbers are self-evaluating
	((mc-boolean? exp) #T) ; Boolean are self-evaluating
	((mc-string? exp) #T) ; Strings are self-evaluat ing
	(else #F)))

(define (variable? exp)
  (symbol? exp)) ; A variable is just a symbol being evaluated.

(define (exp-tag? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #F))

(define (quoted? exp)
  (exp-tag? exp 'quote)) ; This starts with the symbol quote.
(define (assignment? exp)
  (exp-tag? exp 'set!)) ; This starts with the symbol set!.
(define (definition? exp)
  (exp-tag? exp 'define)) ; This starts with the symbol define.
(define (if? exp)
  (exp-tag? exp 'if)) ; This starts with the symbol if.
(define (lambda? exp)
  (exp-tag? exp 'lambda)) ; This starts with the symbol lambda.
(define (begin? exp)
  (exp-tag? exp 'begin)) ; This starts with the symbol begin.
(define (cond? exp)
  (exp-tag? exp 'cond)) ; This starts with the symbol cond

(define (application? exp)
  (pair? exp)) ; Make sure this is a list...

(define (eval-self-evaluating exp) exp)

(define (eval-variable exp env) (env-lookup-symbol env exp))

(define (eval-quotation exp) (cadr exp))

(define (eval-assignment exp env)
  (let ((symbol (cadr exp))
	(value (mc-eval (caddr exp) env)))
    (env-mutate-symbol! env symbol value))
  'OK)

(define (normal-define? exp)
  (symbol? (cadr exp)))

(define (definition-symbol exp)
  (if (normal-define? exp)
      (cadr exp) ; (define <symbol> <expression>)
      (caadr exp))) ; (define (<symbol> <p1> ... <pn>) <e1> ... <em>)

(define (make-lambda formal-params body)
  (cons 'lambda ; (lambda
	(cons formal-params ; (<symbol> <p1> ... <pn>)
	      body))) ; <e1> ... <em>)

(define (definition-value exp)
  (if (normal-define? exp)
      (caddr exp)
      (make-lambda (cdadr exp) ; Formal parameters
		   (cddr exp)))) ; Body (list of expressions)

(define (eval-definition exp env)
  (let ((symbol (definition-symbol exp))
	(value (mc-eval (definition-value exp) env)))
    (env-define-symbol! env symbol value))
  'OK)

(define (false? value) (eq? false value))
(define (true? valu e) (not (false? value) ))

(define (if-predicate exp) (cadr exp))

(define (if-consequent exp) (caddr exp))

(define (if-alternate exp)
  (if (not (null? (cdddr exp)))
      (cadddr exp)
      #F))
(define (eval-if exp env)
  (let ((predicate (if-predicate exp))
	(consequent (if-consequent exp))
	(alternate (if-alternate exp)))
    (if (true? (mc-eval predicate env))
	(mc-eval consequent env)
	(if alternate (mc-eval alternate env)))))


; The Constructor.
(define (make-procedure parameters body env)
  (list 'procedure parameters body env))
; The Predicate.
(define (compound-procedure? procedure)
  (and (pair? procedure) (eq? (car procedure) 'procedure)))
; The Selectors.
(define (procedure-parameters procedure) (cadr procedure))

(define (procedure-body procedure) (caddr procedure))

(define (procedure-environment procedure) (cadddr procedure))



(define (eval-lambda exp env)
  (let ((parameters (cadr exp))
	(body (cddr exp)))
    (make-procedure parameters body env)))

(define (expression-list-eval exp-list env)
  (let ((exp (car exp-list))
	(rest (cdr exp-list)))
    (let ((value (mc-eval exp env)))
      (if (null? rest)
	  value
	  (expression-list-eval rest env)))))

(define (eval-begin exp env)
  (expression-list-eval (cdr exp) env))

(define (make-if predicate consequent alternate)
  (list 'if predicate consequent alternate))

(define (make-begin exp-list)
  (cons 'begin exp-list))

(define (cond-clauses exp) (cdr exp))

(define (cond-else-caluse? clause)
  (eq? (cond-predicate clause) 'else))
(define (cond-predicate clause) (car clause))

(define (cond-actions clause) (cdr clause))

(define (cond->if exp)
  (expand-clauses (cond-clauses exp)))

(define (expand-clauses clauses)
  (if (null? clauses)
      false
      (let ((first (car clauses))
	    (rest (cdr clauses)))
	(if (cond-else-clause? first)
	    (if (null? rest)
		(make-begin (cond-actions first))
		(error "ELSE clause isn't last -- COND->IF"
		       clauses))
	    (make-if (cond-predicate first)
		     (make-begin (cond-actions first))
		     (expand-clauses rest))))))

(define (eval-cond exp env)
  (mc-eval (cond->if exp) env))


(define (primitive-procedure? procedure)
  (contains? procedure primitive-procedure-names))

(define (contains? i list)
  (if (null? list) #f
      (or (eq? (car list) i) (contains? i (cdr list)))))

(define (mc-apply procedure actual-params)
  (cond ((primitive-procedure? procedure)
	 (apply-primitive-procedure procedure actual-params))
	((compound-procedure? procedure)
	 (let ((exp-list (procedure-body procedure))
	       (formal-params (procedure-parameters procedure)))
	   (let ((new-env (env-extend env
				      formal-params
				      actual-params)))
	     (expression-list-eval exp-list new-env))))
	(else
	 (error "Unknown procedure type -- APPLY" procedure))))

(define (apply-primitive-procedure procedure actual-params)
  (cond ((eq? procedure '+)(apply + actual-params))
	((eq? procedure '-)(apply - actual-params))
	((eq? procedure '/)(apply / actual-params))
	((eq? procedure '*)(apply * actual-params))
	((eq? procedure 'cons)(apply cons actual-params))
	((eq? procedure 'car)(apply car actual-params))
	((eq? procedure 'cdr)(apply cdr actual-params))
	((eq? procedure 'eq?)(apply eq? actual-params))
	((eq? procedure 'eqv?)(apply eqv? actual-params))
	((eq? procedure 'equal?)(apply equal? actual-params))
	((eq? procedure 'list)(apply list actual-params))
	((eq? procedure '>)(apply > actual-params))
	((eq? procedure '<)(apply < actual-params))
	((eq? procedure '=)(apply = actual-params))
	((eq? procedure 'null?)(apply null? actual-params))))
  

(define (eval-application exp env)
  (let ((evaled-list (map (lambda (exp) (mc-eval exp env)) exp)))
    (let ((operator (car exp))
	  (operands (cdr exp)))
      (mc-apply operator operands))))

; The Constructor.
(define (make-environment frame old-environment)
  (cons frame old-environment))
; The Constant.
(define the-empty-environment '())
; The Predicate.
(define (empty-env? environment)
  (eq? the-empty-environment environment))
; The Selectors.
(define (enclosing-environment env) (cdr env))

(define (first-frame env) (car env))

(define (env-mutate-symbol! env symbol value)
  (if (empty-env? env)
      (error "Unbound variable" symbol)
      (let ((frame (first-frame env))
	    (rest (enclosing-environment env)))
	(if (frame-mutate-symbol! frame symbol value)
	    #T
	    (env-mutate-symbol! rest symbol value)))))

(define (env-define-symbol! env symbol value)
  (if (empty-env? env)
      (error "Empty environment" env)
      (let ((frame (first-frame env)))
	(if (not (frame-mutate-symbol! frame symbol value))
	    (frame-add-binding! frame symbol value)))))

(define (env-extend env symbol-list value-list)
  (make-environment (make-frame symbol-list value-list)
		    env))

(define (env-lookup-symbol env exp)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
	     (env-loop (enclosing-environment env)))
	    ((eq? exp (car vars))
	     (car vals))
	    (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
	(error "Unbound variable" exp)
	(let ((frame (first-frame env)))
	  (scan (frame-variables frame)
		(frame-values frame)))))
  (env-loop env))
	   

; The Constructor.
(define (make-frame symbols values)
  (if (= (length symbols) (length values))
      (cons symbols values)
      (error "Frame Construction Error" (cons symbols values))))
; The Selectors.
(define (frame-variables frame) (car frame))
(define (frame-values frame) (cdr frame))

; The Mutators.
(define (frame-add-binding! frame symbol value)
  (set-car! frame (cons symbol (car frame)))
  (set-cdr! frame (cons value (cdr frame))))
(define (frame-mutate-symbol! frame symbol value)
  (define (mutate-loop! symbols values symbol new-value)
    (cond ((null? symbols) #F)
	  ((eq? (car symbols) symbol)
	   (set-car! values new-value))
	  (else
	   (mutate-loop! (cdr symbols)
			 (cdr values)
			 symbol
			 value))))
  (mutate-loop! (frame-variables frame)
		(frame-values frame)
		symbol
		value))

(define primitive-procedure-names
  '(+ - / * cons car cdr eq? eqv? equal? list null? > < =))

(define primitive-procedure-objects
  (list + - / * cons car cdr eq? eqv? equal? list null? > < =))

(define (setup-environment)
  (let ((initial-env
	 (env-extend the-empty-environment
		     primitive-procedure-names
		     primitive-procedure-objects)))
    initial-env))
(define the-global-environment (setup-environment))

(define input-prompt ";;; MC-Eval input:")
(define output-prompt ";;; MC-Eval output:")
(define (prompt-for-input string)
  (newline) (newline) (display string) (newline))
(define (prompt-for-output string)
  (newline) (display string) (newline))
(define (driver-loop)
  (prompt-for-input input-prompt)
  (let ((output (mc-eval (read) the-global-environment)))
    (prompt-for-output output-prompt)
    (prompt-for-output output))
  (driver-loop))

(define (mce)
  (set! the-global-environment (setup-environment))
  (driver-loop))
