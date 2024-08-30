test.sh: 
	printf "Try running one of the following commands: "
	printf "intro, "
	printf "penname, "
	printf "tax, "
	printf "\n"

intro:
	./.filecheck.sh intro
	mkdir -p ./student/intro
	cp ./labs/intro/intro.cpp ./student/intro/intro.cpp

penname:
	./.filecheck.sh penname
	mkdir -p ./student/penname
	cp ./labs/penname/penname.cpp ./student/penname/penname.cpp

tax:
	./.filecheck.sh tax
	mkdir -p ./student/tax
	cp ./labs/tax/tax.cpp ./student/tax/tax.cpp

