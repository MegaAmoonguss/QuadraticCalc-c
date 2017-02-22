IF NOT EXIST build (
	mkdir build
}
gcc -o build/QuadraticCalc-c src/* -lm
