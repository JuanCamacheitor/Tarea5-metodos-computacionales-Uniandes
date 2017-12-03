Results_hw5.pdf: CurvaRotacion.c
	gcc CurvaRotacion.c -lm
	./a.out

	python Plots.py

	pdflatex Results_hw5.tex
	pdflatex Results_hw5.tex