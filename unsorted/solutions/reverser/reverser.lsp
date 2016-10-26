;; Solution to the Word Order Reverser Problem
;;
;; File:	reverser.lsp
;; Authors:	Bob Walton (walton@seas.harvard.edu)
;; Date:	Wed Feb 13 06:38:03 EST 2013
;;
;; The authors have placed this program in the public
;; domain; they make no warranty and accept no liability
;; for this program.

(defvar *debug* (rest *posix-argv*))

(defun dformat (&rest args)
  (if *debug* (apply #'format t args)))

(defvar *line*)

; Function to find and print the first word BEFORE q,
; where q indexes a character in *line*.  It is a
; program error if there is no such word.  Returns
; index of the first character of the word printed.
;
(defun print-substitute-word ( q )
 
  ; Move q backward to point just after word.
  ;
  (loop do (assert (< 0 q))
	until (alpha-char-p (char *line* (1- q)))
	do (decf q))

  ; Move q to point at 1st character of word and
  ; print the word.
  ;
  (loop with p = q
	until (<= q 0)
	until (not (alpha-char-p (char *line* (1- q))))
	do (decf q)
	finally (format t "~A" (subseq *line* q p)))

  q)

; Main loop
;
(loop while (setf *line* (read-line nil nil)) do

  (dformat "~A~%" *line*)

  ;
  ; Print line substituting for words.
  ;
  (loop with end = (length *line*)
	with p = 0
	  ; p moves forward printing non-word characters
	  ; while finding and skipping words
	with q = end
	  ; q moves backward finding and printing words
        while (< p end)
	when (alpha-char-p (char *line* p)) do
	     ; word found; skip and use q to print
	     (loop while (and (< p end)
			      (alpha-char-p
				(char *line* p)))
	           do (incf p)
		   finally
	             (setf q (print-substitute-word q)))
	else do ; non-word character found
	        ; skip and print
	        (format t "~A" (char *line* p))
	        (incf p)
        finally ; print line end
	        (format t "~%")))
