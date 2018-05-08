file=Project
newLine=\\\\\\

all: manualNoBib

rubber:	
	rubber --unsafe --force --pdf $(file).tex
	pdftotext -f 2 $(file).pdf - | wc -w
	
word:
	pdftotext -f 8 $(file).pdf - | wc -w

once: ver
	pdflatex --shell-escape --draftmode $(file).tex
	pdflatex --shell-escape             $(file).tex

final:
	echo "" > version.tex
	rubber --force --pdf $(file).tex
	pdftotext -f 8 $(file).pdf - | wc -w
	
manual: ver
	pdflatex --shell-escape $(file).tex
	bibtex $(file)
	pdflatex --shell-escape $(file).tex
	pdflatex --shell-escape $(file).tex
	pdftotext -f 8 $(file).pdf - | wc -w

manualNoBib: ver
	pdflatex --shell-escape $(file).tex
	#bibtex $(file)
	pdflatex --shell-escape $(file).tex
	pdflatex --shell-escape $(file).tex
	pdftotext -f 1 $(file).pdf - | wc -w

ver:
	echo "`git show | head -1` $(newLine)" > version.tex
	echo "`git show | head -3 | tail -1 | sed 's/Date:   //g'` $(newLine)" >> version.tex
	echo -n "branch: `git branch | grep '*' | sed 's:\* ::g'` $(newLine)" >> version.tex
	-git describe --tags 2>/dev/null >> version.tex

clean:
	rm -f $(file).dvi $(file).aux $(file).log $(file).toc $(file).lof $(file).lot $(file).out *.log $(file).bbl $(file).blg $(file).ilg $(file).nlo $(file).nls $(file).synctex.gz

scrub:
	git clean -xn
	#git clean -xf
