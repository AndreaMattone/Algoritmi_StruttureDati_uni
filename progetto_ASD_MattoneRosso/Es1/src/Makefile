all: compile_test compile_app

remove:
		rm app test
compile_test:
		gcc ../Resources/C/Unity/unity.c sorted_structure_tests.c sorted_structure.c generic_sorting.c -o test
compile_app:
		gcc ../Resources/C/Unity/unity.c main_app.c sorted_structure.c generic_sorting.c -o app
run_test:
	./test
run_app:
	./app dataset/records.csv