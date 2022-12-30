daemon = parentald
cli = parentalctl

target: ${daemon} ${cli}

${daemon}:
	@g++ -O2 -o ${daemon} daemon.cpp func.cpp

${cli}:
	@g++ -O2 -o ${cli} cli.cpp func.cpp