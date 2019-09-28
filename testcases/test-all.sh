#!/bin/bash


# Sean Szumlanski
# COP 3502, Fall 2017

# ========================
# ListyString: test-all.sh
# ========================
# You can run this script at the command line like so:
#
#   bash test-all.sh
#
# For more details, see the assignment PDF.


################################################################################
# Initialization.
################################################################################

PASS_CNT=0
NUM_TEST_CASES=5
NUM_UNIT_TESTS=26
TOTAL_TEST_CNT=`expr $NUM_TEST_CASES + $NUM_UNIT_TESTS`

if [ ! -f ListyString.c ]; then
	echo ""
	echo " Error: You must place ListyString.c in this directory"
	echo "        before we can proceed. Aborting test script."
	echo ""
	exit
fi

if [ ! -f ListyString.h ]; then
	echo ""
	echo " Error: You must place ListyString.h in this directory"
	echo "        before we can proceed. Aborting test script."
	echo ""
	exit
fi

if [ ! -d sample_output ]; then
	echo ""
	echo " Error: You must place the sample_output folder in this"
	echo "        this directory before we can proceed. Aborting"
	echo "        test script."
	echo ""
	exit
fi

################################################################################
# Run test cases with input specified at command line.
################################################################################

echo ""
echo "================================================================"
echo "Running test cases..."
echo "================================================================"
echo ""

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	echo -n "  [Test Case] Checking input$i.txt .... "

	# Ensure that ListyString.h is in non-unit test case mode.
	perl -p -i -e 's/main ___goodbye_main_lol/main main/' ListyString.h

	# Attempt to compile.
	gcc ListyString.c 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		continue
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out input$i.txt > myoutput$i.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		continue
	fi

	# Run diff and capture its return value.
	diff myoutput$i.txt sample_output/output$i.txt > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
done


################################################################################
# Run unit tests.
################################################################################

FIRST_UNIT_TEST=`expr $NUM_TEST_CASES + 1`
FINAL_UNIT_TEST=`expr $NUM_TEST_CASES + $NUM_UNIT_TESTS`

for i in `seq -f "%02g" $FIRST_UNIT_TEST $FINAL_UNIT_TEST`;
do
	echo -n "  [Unit Case] Checking testcase$i.c ... "

	# Ensure that ListyString.h is in unit test case mode.
	perl -p -i -e 's/main main/main ___goodbye_main_lol/' ListyString.h

	# Attempt to compile.
	gcc ListyString.c UnitTest.c testcase$i.c 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		continue
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out > myoutput$i.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		continue
	fi

	# Run diff and capture its return value.
	diff myoutput$i.txt sample_output/output$i.txt > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
done


################################################################################
# Cleanup phase.
################################################################################

# Restore ListyString.h to non-unit test case mode.
perl -p -i -e 's/main ___goodbye_main_lol/main main/' ListyString.h

# Clean up the executable file.
rm -f a.out

# Clean up the output files generated by this script.
for i in `seq -f "%02g" 1 $TOTAL_TEST_CNT`;
do
	rm -f myoutput$i.txt
done


################################################################################
# Final thoughts.
################################################################################

echo ""
echo "================================================================"
echo "Final Report"
echo "================================================================"

if [ $PASS_CNT -eq $TOTAL_TEST_CNT ]; then
	echo ""
	echo "  CONGRATULATIONS! You appear to be passing all the test cases!"
	echo "  (Now, don't forget to create some of your own. Mine are not"
	echo "  comprehensive.)"
	echo ""
else
	echo "                           ."
	echo "                          \":\""
	echo "                        ___:____     |\"\\/\"|"
	echo "                      ,'        \`.    \\  /"
	echo "                      |  o        \\___/  |"
	echo "                    ~^~^~^~^~^~^~^~^~^~^~^~^~"
	echo ""
	echo "                           (fail whale)"
	echo ""
	echo "Note: The fail whale is friendly and adorable! He is not here to"
	echo "      demoralize you, but rather, to bring you comfort and joy"
	echo "      in your time of need. \"Keep plugging away,\" he says! \"You"
	echo "      can do this!\""
	echo ""
fi
