geometry:
	touch geometry.h
	
	cat Point.h Line.h Shape.h Ellipse.h Circle.h Polygon.h Rectangle.h Square.h Triangle.h > geometry.h
	cat Point.cpp Line.cpp Ellipse.cpp Circle.cpp Polygon.cpp Rectangle.cpp Square.cpp Triangle.cpp >> geometry.h
	sed "s/#include \"\w*.\w*\"//g" -i geometry.h
	sed "s/#include <\w*\.\w*>//g" -i geometry.h
	clang-format -i geometry.h