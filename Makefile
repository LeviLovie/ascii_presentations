run:
	@mkdir -p ./build
	@cd ./build;\
		cmake -DCMAKE_BUILD_TYPE=Debug ..;\
		make && ./ASCII_Presentations --debug

deploy:
	@mkdir -p ./build
	@cd ./build;\
		cmake -DCMAKE_BUILD_TYPE=Release ..;\
		make && ./ASCII_Presentations
