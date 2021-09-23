CC = gcc
CP = g++
CFLAGS = -g -w -Wall

main: ../ExpressionEvaluator/main.c
	$(CC) $(CFLAGS) -o ../ExpressionEvaluator/main.out ../ExpressionEvaluator/main.c -lm
	echo "Compiled main.c ✅"

polynomial: ../ExpressionEvaluator/polynomial.c
	$(CC) $(CFLAGS) -o ../ExpressionEvaluator/polynomial.out ../ExpressionEvaluator/polynomial.c
	echo "Compiled polynomial.c ✅"

sparseMatrix:
	$(CP) $(CFLAGS) -o ../ExpressionEvaluator/sparseMatrix.out ../ExpressionEvaluator/sparseMatrix.cpp
	echo "Compiled polynomial.c ✅"

clean:
	rm *.out
	echo "Cleaned 🧹"
