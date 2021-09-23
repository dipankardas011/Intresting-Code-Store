CC = gcc
CFLAGS = -g -w -Wall

main: ../ExpressionEvaluator/main.c
	$(CC) $(CFLAGS) -o ../ExpressionEvaluator/main ../ExpressionEvaluator/main.c -lm
	echo "Compiled main.c ✅"

polynomial: ../ExpressionEvaluator/polynomial.c
	$(CC) $(CFLAGS) -o ../ExpressionEvaluator/polynomial ../ExpressionEvaluator/polynomial.c
	echo "Compiled polynomial.c ✅"

clean:
	rm ../ExpressionEvaluator/main
	rm ../ExpressionEvaluator/polynomial
	echo "Cleaned 🧹"
