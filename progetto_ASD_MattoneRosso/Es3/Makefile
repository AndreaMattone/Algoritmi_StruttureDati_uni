all: compile_app compile_test

app: compile_app
	
test:compile_test

remove:
	rm app
	rm test

compile_test:
	gcc ./Resources/C/Unity/unity.c hash.c hash_tests.c -o test

compile_app: 
	gcc ./hash.c app.c -o app

run_test:
	./test

run_app:
	./app dataset/hashes.csv