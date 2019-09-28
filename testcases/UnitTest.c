// Sean Szumlanski
// COP 3502, Fall 2017

// =======================
// ListyString: UnitTest.c
// =======================
// This code simply calls the unit_test() function in whatever test case is
// compiled with the program. This only works if ListyString.h is set to
// re-define main() as __goodbye_main_lol(). Otherwise, compiling this with
// ListyString.c will result in two definitions of the main() function: one
// in ListyString.c, and one in this file.


int unit_test(int argc, char **argv);

int main(int argc, char **argv)
{
	unit_test(argc, argv);
	return 0;
}
