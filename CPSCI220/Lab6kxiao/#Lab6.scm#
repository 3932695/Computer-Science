; Kevin Xiao - March 6th 2014 - Lab6
; ---- Intro to Scheme ---- 
; "prime?" was based on the public example in ML folder 
; This lab was completed during lab session with Ryan, Ben, Harry, Shirley and Adam.  

; Takes integer as parameter, and returns #t if it's prime, #f otherwise.
; Example usage: (prime? 2)
; Value: #t
(define (prime? n) 
  (if (< n 2) 
      #f 
      (prime-help n 2)
  )
)

(define (prime-help n h)
  (if (> h (/ n 2))
      #t
      (if (= (modulo n h) 0)
	  #f
	  (prime-help n (+ h 1))
      )
  )
)

; Takes row and column as parameter, and returns element value at that position in triangle.
; Example usage: (pascal 3 2)
; Value: 2
(define (pascal row col)
  (if (< row col)
      "Error: 'col' cannot exceed 'row' on '(pascal row col)'"
      (if (or (= col 1) (= row col) )
	   1
	   (+ (pascal (- row 1) (- col 1)) (pascal (- row 1) col))
      )
  )
)

; Takes two functions as parameters, and returns composite function.
; Example usage: (apply (compose prime? pascal) '(3 2))
; Value: #t
(define (compose ff fg) 
  (lambda args (ff(apply fg args))
  )
)

; Takes list of symbols, list of values, and association list as parameters.
; Makes pairs out of symbols and values, and appends list of pairs to association list.
; Example usage: (bind-parms '(x y) '("hi" 3) '((a . 2) (x . 3) (y . 22)))
; Value: ((x . "hi") (y . 3) (a . 2) (x . 3) (y . 22))
(define (bind-parms symbols values currentlist)
  (if(= (length symbols) (length values))
     (append (build-head symbols values) currentlist)
     "Error: no. of symbols must equal no. of values"
  )
)

(define (build-head symbols values)
  (if(= (length symbols) 0)
     '()
     (append (list (cons (car symbols) (car values))) (build-head (cdr symbols) (cdr values)))
  )
)

; Takes a symbol, value and association list as parameters, and returns modified list.
; All elements with a matching symbol will be updated with the new value in modified list.
; Example usage: (define binds '((a . 2)(b . 3)))
;                (change-binding! 'b 4 binds)
; Value: ((a . 2) (b . 4))
(define (change-binding! symbol value currentlist)
  (if (null? currentlist)
      '()
      (if (eq? (car (car currentlist)) symbol)
	  (append (list (cons symbol value)) (change-binding! symbol value (cdr currentlist)))
	  (append (list (car currentlist)) (change-binding! symbol value (cdr currentlist)))
      )
  )

)

; Prompts the user to input an expression. Displays the expression, and its evaluation.
; Type "exit" to discontinue repl.
(define repl
  (lambda() 
    (display "\nEnter an expression: ")(define expr (read))
    (if (eq? 'exit expr) 
        "Quitting repl......"
	(evaluate expr)
    )
  )
)

(define (evaluate expr)
  (display "Expr: ") (display expr)
  (display "\nValue: ") (display (eval expr user-initial-environment))
  (repl)
)
