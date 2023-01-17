build-run:
	@build.bat
	@echo "Build completed."
	@echo "Running..."
	@build/snayai.exe

run:
	@build/snayai.exe