;; This file was used to generate 64bits numbers that represent every digimon's evolution

;; this table represents the position of every digimon in the array digimons
;; the array is in the C code
(defvar *digimon*
  '((Botamon 0) (Poyomon 1) (Punimon 2) (Yuramon 3)
    (Koromon 4) (Tokomon 5) (Tsunomon 6) (Tanemon 7)
    (Agumon 8) (Gabumon 9) (Patamon 10) (Elecmon 11) (Biyomon 12) (Kunemon 13) (Palmon 14) (Betamon 15) (Penguinmon 16)
    (Greymon 17) (Monochromon 18) (Ogremon 19) (Airdramon 20) (Kuwagamon 21) (Whamon 22) (Frigimon 23) (Nanimon 24)
    (Meramon 25) (Drimogemon 26) (Leomon 27) (Kokatorimon 28) (Vegiemon 29) (Shellmon 30) (Mojyamon 31)
    (Birdramon 32) (Tyrannomon 33) (Angemon 34) (Unimon 35) (Ninjamon 36) (Coelamon 37) (Numemon 38)
    (Centarumon 39) (Devimon 40) (Bakemon 41) (Kabuterimon 42) (Seadramon 43) (Garurumon 44) (Sukamon 45)
    (MetalGreymon 46) (SkullGreymon 47) (Giromon 48) (HKabuterimon 49) (Mamemon 50) (MegaSeadramon 51) (Vademon 52) (Etemon 53)
    (Andromon 54) (Megadramon 55) (Phoenixmon 56) (Piximon 57) (Metalmamemon 58) (Monzaemon 59) (Digitamamon 60)
    ))

;; because not all binary numbers will have six positions
;; we need to force them to have six positions
(defun to-six (n)
  (let ((size (length n)))
    (if (= size 6)
        n
        (concatenate 'string
                     (make-string (- 6 size)
                                  :initial-element #\0)
                     n))))

;; convert a list of digimons into their positions
(defun digi-to-number (x)
  (mapcar #'second
          (mapcar #'(lambda (n)
                      (assoc n *digimon*))
                    x)))

;; convert every position into a binary number
(defun digi-to-binary (x)
  (mapcar #'to-six
          (mapcar #'(lambda (n)
                      (write-to-string n :base 2))
                  (digi-to-number x))))

;; append all binary numbers into a "bigger binary number"
;; and then convert it to a decimal number again
(defun digi-to-evolution (x)
  (parse-integer (format nil "~{~A~}" (digi-to-binary x))
                 :radix 2))



;; Botamon evolution
(digi-to-evolution '(koromon))

;; Poyomon evolution
(digi-to-evolution '(tokomon))

;; Punimon evolution
(digi-to-evolution '(tsunomon))

;; Yuramon evolution
(digi-to-evolution '(tanemon))

;; Koromon evolution
(digi-to-evolution '(agumon gabumon kunemon))

;; Tokomon evolution
(digi-to-evolution '(patamon biyomon kunemon))

;; Tsunomon evolution
(digi-to-evolution '(elecmon penguinmon kunemon))

;; Tanemon evolution
(digi-to-evolution '(palmon betamon kunemon))

;; Agumon evolution
(digi-to-evolution '(birdramon meramon greymon tyrannomon monochromon centarumon sukamon numemon bakemon nanimon))

;; Gabumon evolution
(digi-to-evolution '(nanimon sukamon numemon bakemon drimogemon ogremon garurumon centarumon monochromon tyrannomon))

;; Patamon evolution
(digi-to-evolution '(nanimon sukamon numemon bakemon angemon leomon ogremon drimogemon tyrannomon unimon))

;; Elecmon evolution
(digi-to-evolution '(angemon leomon kokatorimon bakemon numemon sukamon nanimon))

;; Biyomon evolution
(digi-to-evolution '(nanimon sukamon numemon bakemon unimon birdramon airdramon kabuterimon kokatorimon))

;; Kunemon evolution
(digi-to-evolution '(nanimon sukamon numemon bakemon kabuterimon kuwagamon vegiemon))

;; Palmon evolution
(digi-to-evolution '(nanimon sukamon numemon bakemon whamon coelamon vegiemon kuwagamon ninjamon))

;; Betamon evolution
(digi-to-evolution '(nanimon sukamon numemon bakemon whamon coelamon shellmon seadramon))

;; Penguinmon evolution
(digi-to-evolution '(nanimon sukamon numemon garurumon mojyamon shellmon frigimon whamon bakemon))

;; Greymon evolution
(digi-to-evolution '(skullgreymon metalgreymon vademon sukamon))

;; Monochromon evolution
(digi-to-evolution '(metalmamemon metalgreymon vademon sukamon))

;; Ogremon evolution
(digi-to-evolution '(andromon giromon vademon sukamon))

;; Airdramon evolution
(digi-to-evolution '(phoenixmon megadramon vademon sukamon))

;; Kuwagamon evolution
(digi-to-evolution '(piximon hkabuterimon vademon sukamon))

;; Whamon evolution
(digi-to-evolution '(mamemon megaseadramon vademon sukamon))

;; Frigimon evolution
(digi-to-evolution '(metalmamemon mamemon vademon sukamon))

;; Nanimon evolution
(digi-to-evolution '(digitamamon sukamon vademon))

;; Meramon evolution
(digi-to-evolution '(metalgreymon andromon vademon sukamon))

;; Drimogemon evolution
(digi-to-evolution '(metalgreymon vademon sukamon))

;; Leomon evolution
(digi-to-evolution '(andromon mamemon vademon sukamon))

;; Kokatorimon evolution
(digi-to-evolution '(piximon phoenixmon vademon sukamon))

;; Vegiemon evolution
(digi-to-evolution '(piximon vademon sukamon))

;; Shellmon evolution
(digi-to-evolution '(hkabuterimon megaseadramon vademon sukamon))

;; Mojyamon evolution
(digi-to-evolution '(skullgreymon mamemon vademon sukamon))

;; Birdramon evolution
(digi-to-evolution '(phoenixmon vademon sukamon))

;; Tyrannomon evolution
(digi-to-evolution '(megadramon metalgreymon vademon sukamon))

;; Angemon evolution
(digi-to-evolution '(andromon devimon phoenixmon vademon sukamon))

;; Unimon evolution
(digi-to-evolution '(phoenixmon giromon vademon sukamon))

;; Ninjamon evolution
(digi-to-evolution '(metalmamemon mamemon vademon sukamon))

;; Coelamon evolution
(digi-to-evolution '(megaseadramon vademon sukamon))

;; Numemon evolution
(digi-to-evolution '(monzaemon vademon sukamon))

;; Centarumon evolution
(digi-to-evolution '(andromon giromon vademon sukamon))

;; Devimon evolution
(digi-to-evolution '(megadramon skullgreymon vademon sukamon))

;; Bakemon evolution
(digi-to-evolution '(giromon skullgreymon vademon sukamon))

;; Kabuterimon evolution
(digi-to-evolution '(hkabuterimon metalmamemon vademon sukamon))

;; Seadramon evolution
(digi-to-evolution '(megadramon megaseadramon vademon vademon sukamon))

;; Garurumon evolution
(digi-to-evolution '(skullgreymon megaseadramon vademon sukamon))

;; Sukamon evolution
(digi-to-evolution '(etemon vademon))

;; Metal Greymon evolution
(digi-to-evolution '(sukamon))

;; Skull Greymon evolution
(digi-to-evolution '(sukamon))

;; Giromon evolution
(digi-to-evolution '(sukamon))

;; H-Kabuterimon evolution
(digi-to-evolution '(sukamon))

;; Mamemon evolution
(digi-to-evolution '(sukamon))

;; Mega Seadramon evolution
(digi-to-evolution '(sukamon))

;; Vademon evolution
(digi-to-evolution '(sukamon))

;; Etemon evolution
(digi-to-evolution '(sukamon))

;; Andromon evolution
(digi-to-evolution '(sukamon))

;; Megadramon evolution
(digi-to-evolution '(sukamon))

;; Phoenixmon evolution
(digi-to-evolution '(sukamon))

;; Piximon evolution
(digi-to-evolution '(sukamon))

;; Metal Mamemon evoltuion
(digi-to-evolution '(sukamon))

;; Monzaemon evolution
(digi-to-evolution '(sukamon))

;; Digitamamon evolution
(digi-to-evolution '(sukamon))
