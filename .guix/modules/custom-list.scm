(define-module (custom-list)
    #:use-module (guix)
    #:use-module (guix packages)
    #:use-module (guix download)
    #:use-module ((guix licenses) #:prefix license:)
    #:use-module (guix git-download)
    #:use-module (guix build-system gnu)
    #:use-module (guix build-system cmake)
    #:use-module (gnu packages gcc)
    #:use-module (gnu packages pkg-config)
    )

(define-public custom-list
  (package
    (name "custom-list")
    (version "1.0")
    (home-page "https://github.com/AntoineJkl/custom-list")
    (synopsis "Custom implementation of the 'ls' Unix command")
    (description "Implementation of the 'ls' Unix command customized with arrows and colors.")
    (license license:gpl3+) 
    (source (origin
              (method git-fetch)
              (uri (git-reference
                    (url "https://github.com/AntoineJkl/custom-list")
                    (commit "main")))
              (sha256
               (base32
                "14gvnyvyrlgnpgc217y1930jp8jgwxfcjzwbainxwqv6sdayga5c"))))
    (build-system cmake-build-system)
    (arguments
        '(#:configure-flags '("-DCMAKE_BUILD_TYPE=Release"
                              "-DCustomLS_USE_ARROW=ON"
                              "-DCustomLS_USE_COLOR_BLUE=ON"
                              "-DCustomLS_USE_COLOR_GREEN=ON"
                              "-DCustomLS_USE_COLOR_YELLOW=ON") 
          #:tests? #f))
    (inputs '()) 
    (native-inputs (list pkg-config)))) 

;; Return the package object defined above at the end of the module
custom-list