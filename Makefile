JackAnalyzer: Main.cpp CompilationEngine.cpp JackAnalyzer.cpp JackTokenizer.cpp
	g++ -o JackAnalyzer -Wall -Wextra -pedantic -std=c++17 Main.cpp CompilationEngine.cpp JackAnalyzer.cpp JackTokenizer.cpp -lstdc++fs -Os

run:
	./JackAnalyzer project10/ArrayTest
	./JackAnalyzer project10/ExpressionLessSquare
	./JackAnalyzer project10/Square


testAll:
    # ArrayTest
	diff -w project10/ArrayTest/Main.xml project10/ArrayTest/Main.out_xml
	diff -w project10/ArrayTest/MainT.xml project10/ArrayTest/MainT.out_xml
    # ExpressionLessSquare
	diff -w project10/ExpressionLessSquare/Main.xml project10/ExpressionLessSquare/Main.out_xml
	diff -w project10/ExpressionLessSquare/MainT.xml project10/ExpressionLessSquare/MainT.out_xml

	diff -w project10/ExpressionLessSquare/Square.xml project10/ExpressionLessSquare/Square.out_xml
	diff -w project10/ExpressionLessSquare/SquareT.xml project10/ExpressionLessSquare/SquareT.out_xml

	diff -w project10/ExpressionLessSquare/SquareGame.xml project10/ExpressionLessSquare/SquareGame.out_xml
	diff -w project10/ExpressionLessSquare/SquareGameT.xml project10/ExpressionLessSquare/SquareGameT.out_xml


    # Square
	diff -w project10/Square/Main.xml project10/Square/Main.out_xml
	diff -w project10/Square/MainT.xml project10/Square/MainT.out_xml

	diff -w project10/Square/Square.xml project10/Square/Square.out_xml
	diff -w project10/Square/SquareT.xml project10/Square/SquareT.out_xml

	diff -w project10/Square/SquareGame.xml project10/Square/SquareGame.out_xml
	diff -w project10/Square/SquareGameT.xml project10/Square/SquareGameT.out_xml

clean:
	rm JackAnalyzer
	rm project10/ArrayTest/*.out_xml
	rm project10/ExpressionLessSquare/*.out_xml
	rm project10/Square/*.out_xml

