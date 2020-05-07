sfml-app: sfml.o
						g++ sfml.o handle_input.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
sfml.o: sfml.cpp
					g++ -c sfml.cpp
clean: rm -rf *.o