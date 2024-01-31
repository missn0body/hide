# hide

A simple Blowfish scramble schtick.
First written by anson in late 2023-early 2024.

This terminal uses the Blowfish block cipher
originally written by Bruce Schneier in 1993.
Although most of the code is written by anson,
the specific C implementation of the Blowfish
cipher used here was originally written by Paul
Kocher in 1997.

Command-line arguments are as follows:
> hide (plain/ciphertext) (key) -a (--ansi) -u (--unhide) -h (--help)

These arguments can be put in any order, alternated
between their long and short forms, and their short
forms can be globbed, such as "-au" which instructs
hide to decrypt the following ciphertext with the
given key, and produce ANSI colored output.

Hide will detect any non-argument string passed to
the function as plain/ciphertext, with the second
non-argument string detected read as the key. Any
additional input is ignored. As such, the arguments
and input strings can be sent by the user in any
arbitrary order.

For more information regarding the Blowfish block
cipher, see:
www.schneier.com/academic/blowfish/

For the original C implementation that this program
was interpolated from, see:
www.schneier.com/wp-content/uploads/2015/12/bfsh-koc.zip

## Warning!

I am not a cryptologist, only average enthusiast.
I put together this program because I thought it
would be fun to make, and although it uses a well-
respected block cipher, I would only trust this
program for trivial and low-stake matters. *I would
not trust this program with sensitive information.*
Please use this program with sensible input for
sensible purposes.

As of this program's current version (v.1.0.0, Jan 2024),
the notice above still stands. I may consider improving
this program to where it becomes more trustable, but
as for now, use caution.

### v.1.0.0 (First release)

(Jan 2024)
A simple Blowfish scramble schtick by anson.
Be warned: the only cipher mode supported as of now is EBC.
Use this application with the right data for the right purpose.
