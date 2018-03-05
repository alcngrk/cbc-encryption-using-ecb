This project belongs to Mehmet Alican Gork

Initialization Vector (IV) is not used. Since we can assume it
to be 0, and anything XOR'ed with 0 is itself. Therefore it 
makes no relevant difference, and was not used.

Makefile uses the test main.cc given on the assignment explanation
on mycourses. Also keep in mind the last 2 strings which are the
ones used in assertion are deleted in main.cc, don't forget
to delete those in your own main.cc to make sure there are no
memory leaks.
