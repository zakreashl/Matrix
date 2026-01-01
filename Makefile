

clean: # Removes all builds in builds file
	rm builds/*

all: Matrix.c # Builds matrix 
	clang Matrix.c -o builds/matrix

run: # Runs matrix
	./builds/matrix

pushAll: 
	git add .
	git status
	git commit -m "$MSG"
	git push