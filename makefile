daemon = parentald
cli = parentalctl

target: ${daemon} ${cli}

${daemon}:
	@g++ -O2 -o ${daemon} main.cpp

${cli}:
	@g++ -O2 -o ${cli} ctl.cpp