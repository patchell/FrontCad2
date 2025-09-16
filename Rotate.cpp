#include <iostream>
#include <cmath>
#include <array>

struct Point {
	double x, y;
};

Point rotatePoint(const Point& p, const Point& pivot, double angleRad) {
	double s = std::sin(angleRad);
	double c = std::cos(angleRad);

	// Translate point to origin
	double xShifted = p.x - pivot.x;
	double yShifted = p.y - pivot.y;

	// Rotate
	double xNew = xShifted * c - yShifted * s;
	double yNew = xShifted * s + yShifted * c;

	// Translate back
	return { xNew + pivot.x, yNew + pivot.y };
}

#include <iostream>
#include <vector>

struct Point {
	double x, y;
};

// Returns true if point p is inside polygon poly[]
bool isPointInPolygon(const std::vector<Point>& poly, const Point& p) {
	bool inside = false;
	size_t n = poly.size();

	for (size_t i = 0, j = n - 1; i < n; j = i++) {
		// Check if the edge (poly[i], poly[j]) crosses the horizontal ray to the right of p
		bool intersect = ((poly[i].y > p.y) != (poly[j].y > p.y)) &&
			(p.x < (poly[j].x - poly[i].x) *
				(p.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x);
		if (intersect)
			inside = !inside;
	}
	return inside;
}

int main() {
	// Example polygon (square)
	std::vector<Point> polygon = {
		{0, 0}, {10, 0}, {10, 10}, {0, 10}
	};

	Point testPoint{ 5, 5 };

	if (isPointInPolygon(polygon, testPoint))
		std::cout << "Inside\n";
	else
		std::cout << "Outside\n";

	return 0;
}