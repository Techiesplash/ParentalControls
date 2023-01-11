daemon = parentald
cli = parentalctl

shared_src = reusable/reusable.cpp

target: ${daemon} ${cli}

clean:
	@rm parentald
	@rm parentalctl

${daemon}:
	@g++ -O2 -o ${daemon} daemon/daemon.cpp ${shared_src}

${cli}:
	@g++ -O2 -o ${cli} cli/cli.cpp ${shared_src}