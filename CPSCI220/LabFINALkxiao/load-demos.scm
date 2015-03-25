;; These must be loaded to run in-class demo
;; Invoke (load-demo filename) to "run" a demo
;; Use (wfi string) from within the demo file to 
;; control scrolling

(define env system-global-environment)

(define (load-demo filename)
   (let ((p (open-input-file filename)))
      (demo p)))

(define (demo p)
   (let ((input (read p)))
    (if (eof-object? input)
          (close-input-port p)
        (let ((output (eval input env)))
          (announce-output input output)
          (demo p)))))

(define (announce-output instring outstring)
  (newline) (display instring) (display ":  ") (display outstring) (newline))


; "wfi" is "wait for it ..."
(define (wfi str)
     (newline)
     (display "**********************************")(newline)
     (display str)(newline)
     (display "**********************************")(newline)
     (read console-i/o-port)) ;; MUST HIT A NON-ENTER TO PROCEED

